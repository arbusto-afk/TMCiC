//
// Created by Ignacio on 28/9/2024.
//

#define TYPELONG_BITCOUNT 64

#include "chunkData.h"
#include "../../Defs/ErrorCodes.h"

TChunk * getChunk(int x, int z, client *c) {
    // Calculate the hash key for the given chunk coordinates
    int hashKey = hash2d(x, z);

    // Traverse the hash list for the given hash key
    TChunkHashNode *current = c->chunkHashVec[hashKey];

    // Loop through the linked list to find the correct chunk
    while (current != NULL) {
        // Assuming the chunk structure has chunkX and chunkZ as the coordinates
        if (current->chunk->x == x && current->chunk->x == z) {
            return current->chunk;  // Found the chunk, return it
        }
        current = current->tail;  // Move to the next node in the list
    }

    // If no chunk was found, return NULL
    return NULL;
}

int public_getBlockAtCoords(int x, int y, int z, struct client * c)
{
    int chunkX = x / 16;
    int chunkZ = z / 16;
    int sectionIndex = y / 16;
    TChunk * chunk = getChunk(chunkX, chunkZ, c);
    if(chunk == NULL)
        return ERR_FINDBLOCK_AT_UNLOADED_CHUNK;
    if(sectionIndex >= chunk->sectionArrDim)
        return ERR_FINDBLOCK_HEIGHT_BEYOND_CHUNKHEIGHT;
    TBlockId block = chunk->sectionArr[sectionIndex].blockMatrix[y - sectionIndex * 16][z - chunkZ * 16][x - chunkX * 16];
    return block.globalId;
}


void internal_v1_12_2_chunkData(const uint8_t *data, int dataLen, struct client *c) {

    int sectionsPerChunk = 16;
    TChunk * chunkToLoad = malloc(sizeof(TChunk));
    chunkToLoad->sectionArr = malloc(sectionsPerChunk * sizeof(TChunkSection));
    chunkToLoad->sectionArrDim = sectionsPerChunk;

    chunkToLoad->x = read_int32fromNetworkEndian(data);
    chunkToLoad->z = read_int32fromNetworkEndian(data + 4);

    int groundUpContinous = read_boolean(data + 8);

    TVarInt primaryBitMask = sharedMain_readVarInt(data + 9, VARINTMAXLEN);
    TVarInt sectionDataLen = sharedMain_readVarInt(primaryBitMask.byteAfterEnd, VARINTMAXLEN);

    const uint8_t * dataStartPtr = sectionDataLen.byteAfterEnd;
    int index = 0;
    while (primaryBitMask.value > 0) {
        if (primaryBitMask.value & 1) {
            // Do sections calculations here
            int bitsPerBlock = read_uint8fromNetworkEndian(dataStartPtr);
            bitsPerBlock = bitsPerBlock < 4 ? 4 : bitsPerBlock;

            if (bitsPerBlock <= 8) {
                TVarInt paletteLen = sharedMain_readVarInt(dataStartPtr + 1, VARINTMAXLEN);
                TVarInt * palette = malloc(paletteLen.value * sizeof(TVarInt));
                palette[0] = sharedMain_readVarInt(dataStartPtr + 2, VARINTMAXLEN);
                for (int i = 1; i < paletteLen.value; i++)
                    palette[i] = sharedMain_readVarInt(palette[i - 1].byteAfterEnd, VARINTMAXLEN);

                // read the compacted long sectionArr
                const long * byteAfterPalette = (long*)palette[paletteLen.value - 1].byteAfterEnd;
                int blocksPerLong = 64 / bitsPerBlock;
                int longIndex = 0, bitIndex = 0;

                for (int i = 0; i < CHUNKSECTION_BLOCKCOUNT; i++) {
                    int y = i / CHUNKSECTION_DIM / CHUNKSECTION_DIM;
                    int z = (i / CHUNKSECTION_DIM) % CHUNKSECTION_DIM;
                    int x = i % CHUNKSECTION_DIM;

                    // block to assign fits, no split
                    if (bitIndex + bitsPerBlock <= TYPELONG_BITCOUNT) {
                        long currentLong = read_int64fromNetworkEndian(byteAfterPalette + longIndex);
                        int paletteIndex = (currentLong >> bitIndex) & ((1LL << bitsPerBlock) - 1);

                        chunkToLoad->sectionArr[index].blockMatrix[y][z][x].globalId = palette[paletteIndex].value;

                        bitIndex += bitsPerBlock;
                        if (bitIndex >= TYPELONG_BITCOUNT) {
                            bitIndex = 0;
                            longIndex++;
                        }
                    } else {
                        long currentLong = read_int64fromNetworkEndian(byteAfterPalette + longIndex);
                        long nextLong = read_int64fromNetworkEndian(byteAfterPalette + longIndex + 1);

                        int bitsRemainingInCurrentLong = TYPELONG_BITCOUNT - bitIndex;
                        int lowerPart = (currentLong >> bitIndex) & ((1LL << bitsRemainingInCurrentLong) - 1);

                        // Extract the remaining part from the next long
                        int upperPart = nextLong & ((1LL << (bitsPerBlock - bitsRemainingInCurrentLong)) - 1);

                        // Combine the parts to get the palette index
                        int paletteIndex = (upperPart << bitsRemainingInCurrentLong) | lowerPart;

                        chunkToLoad->sectionArr[index].blockMatrix[y][z][x].globalId = palette[paletteIndex].value;

                        longIndex++;
                        bitIndex = bitsPerBlock - bitsRemainingInCurrentLong;
                    }
                }
            } else {
                // Dummy palette case
                TVarInt paletteLen = sharedMain_readVarInt(dataStartPtr + 1, VARINTMAXLEN);
                const long * byteAfterPalette = (const long*)paletteLen.byteAfterEnd;

                int blocksPerLong = TYPELONG_BITCOUNT / bitsPerBlock;
                int longIndex = 0, bitIndex = 0;

                for (int i = 0; i < CHUNKSECTION_BLOCKCOUNT; i++) {
                    int y = i / (CHUNKSECTION_DIM * CHUNKSECTION_DIM);
                    int z = (i / CHUNKSECTION_DIM) % CHUNKSECTION_DIM;
                    int x = i % CHUNKSECTION_DIM;

                    // Reading global block state ID from the long array
                    if (bitIndex + bitsPerBlock <= 64) {
                        long currentLong = read_int64fromNetworkEndian(byteAfterPalette + longIndex);
                        int globalBlockStateId = (currentLong >> bitIndex) & ((1LL << bitsPerBlock) - 1);

                        chunkToLoad->sectionArr[index].blockMatrix[y][z][x].globalId = globalBlockStateId;

                        bitIndex += bitsPerBlock;
                        if (bitIndex >= 64) {
                            bitIndex = 0;
                            longIndex++;
                        }
                    } else {
                        long currentLong = read_int64fromNetworkEndian(byteAfterPalette + longIndex);
                        long nextLong = read_int64fromNetworkEndian(byteAfterPalette + longIndex + 1);

                        int bitsInCurrentLong = 64 - bitIndex;
                        int lowerPart = (currentLong >> bitIndex) & ((1LL << bitsInCurrentLong) - 1);

                        int upperPart = nextLong & ((1LL << (bitsPerBlock - bitsInCurrentLong)) - 1);

                        int globalBlockStateId = (upperPart << bitsInCurrentLong) | lowerPart;

                        chunkToLoad->sectionArr[index].blockMatrix[y][z][x].globalId = globalBlockStateId;

                        longIndex++;
                        bitIndex = bitsPerBlock - bitsInCurrentLong;
                    }
                }
            }
        }
        index++;
        primaryBitMask.value >>= 1;
    }

    int hashKey = hash2d(chunkToLoad->x, chunkToLoad->z) % CHUNK_HASHVEC_DIM;
    if (groundUpContinous) {
        TChunkHashNode *newNode = malloc(sizeof(TChunkHashNode));
        newNode->chunk = chunkToLoad;
        newNode->tail = c->chunkHashVec[hashKey];
        printf("Successfully loaded chunk X: %d, Z: %d, at index %d\n", chunkToLoad->x, chunkToLoad->z, hashKey);
        c->chunkHashVec[hashKey] = newNode;
    } else {
        TChunkHashNode *existingNode = c->chunkHashVec[hashKey];
        TChunkHashNode *prevNode = NULL;

        while (existingNode != NULL) {
            if (existingNode->chunk->x == chunkToLoad->x && existingNode->chunk->z == chunkToLoad->z) {
                // Refreshing sections based on primaryBitMask
                printf("Refreshing chunk X: %d, Z: %d at index %d\n", chunkToLoad->x, chunkToLoad->z, hashKey);

                for (int i = 0; i < sectionsPerChunk; i++) {
                    if (primaryBitMask.value & (1 << i)) {
                        // Free old section only if replacing it
                        free(existingNode->chunk->sectionArr[i].blockMatrix);
                        existingNode->chunk->sectionArr[i] = chunkToLoad->sectionArr[i];
                    }
                }

                free(chunkToLoad->sectionArr);  // Free temporary storage
                free(chunkToLoad);       // Free chunkToLoad as it's no longer needed
                return;
            }
            prevNode = existingNode;
            existingNode = existingNode->tail;
        }

        printf("GroundUpContinous is false but no chunk found at X: %d, Z: %d, ignoring\n", chunkToLoad->x, chunkToLoad->z);

        free(chunkToLoad->sectionArr);
        free(chunkToLoad);
    }
}
