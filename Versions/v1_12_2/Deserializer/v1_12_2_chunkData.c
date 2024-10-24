//
// Created by Ignacio on 28/9/2024.
//

#define TYPELONG_BITCOUNT 64

#include "v1_12_2_chunkData.h"
#include "../../../Defs/ErrorCodes.h"
#include "../../../Std/internal_std_getChunk.h"
#include "../../../Public/public_getBlockAtCoords.h"
#include <math.h>

/*
 * returns byte after end;
 * start at sectionArr
 */
static const uint8_t * oncePerSection(const uint8_t * data, long dataLen, TChunk * ch, int sectionIndex) {
    //foreach section
    // Do sections calculations here
    int bitsPerBlock = read_uint8fromNetworkEndian(data);
    bitsPerBlock = bitsPerBlock < 4 ? 4 : bitsPerBlock;

    TVarInt paletteLen = sharedMain_readVarInt(data + 1, VARINTMAXLEN);
    int *palette = NULL;

    //compacted long array dim
    TVarInt cLongArrDim = sharedMain_readVarInt(paletteLen.byteAfterEnd,VARINTMAXLEN);

    //sets palette arr or keeps NULL, read cLongArrDim from palette end if it corrensponds
    if (paletteLen.value != 0) {
        palette = malloc(sizeof(int) * paletteLen.value);
        if (palette == NULL) {
            perror("Error allocating memory for palette");
            return NULL; // Handle the error appropriately
        }
        uint8_t *aux = paletteLen.byteAfterEnd;
        for (int i = 0; i < paletteLen.value; i++)
        {
            TVarInt auxVarInt = sharedMain_readVarInt(aux, VARINTMAXLEN);
            palette[i] = auxVarInt.value;
            aux = auxVarInt.byteAfterEnd;
        }
        cLongArrDim = sharedMain_readVarInt(aux, VARINTMAXLEN);
    }
    const uint8_t *cLongArr = cLongArrDim.byteAfterEnd;

    int longIndex = 0, bitIndex = 0;
    int ll = 0;
    for (int i = 0; i < CHUNKSECTION_BLOCKCOUNT; i++) {
        int y = i / CHUNKSECTION_DIM / CHUNKSECTION_DIM;
        int z = (i / CHUNKSECTION_DIM) % CHUNKSECTION_DIM;
        int x = i % CHUNKSECTION_DIM;

        long currentLong = read_int64fromNetworkEndian((long*)cLongArr + longIndex);
        int globalId;

        if (bitIndex + bitsPerBlock <= 64) {
            globalId = (currentLong >> bitIndex) & ((1L << bitsPerBlock) - 1);

            ch->sectionArr[sectionIndex].blockMatrix[y][z][x].longIndex = longIndex;
            ch->sectionArr[sectionIndex].blockMatrix[y][z][x].bitIndex = bitIndex;
            bitIndex += bitsPerBlock;
            if (bitIndex >= 64) {
                bitIndex = 0;
                longIndex++;
            }
        }
        else
        {
            long nextLong = read_int64fromNetworkEndian((long*)cLongArr + longIndex + 1);
            int bitsRemainingInCurrentLong = 64 - bitIndex;
            int lowPart = (currentLong >> bitIndex) & ((1LL << bitsRemainingInCurrentLong) - 1);
            int highPart = nextLong & ((1LL << (bitsPerBlock - bitsRemainingInCurrentLong)) - 1);

            globalId = (highPart << bitsRemainingInCurrentLong) | lowPart;
            ch->sectionArr[sectionIndex].blockMatrix[y][z][x].longIndex = -longIndex;
            ch->sectionArr[sectionIndex].blockMatrix[y][z][x].bitIndex = bitIndex;

            longIndex++;
            bitIndex = bitsPerBlock - bitsRemainingInCurrentLong;
        }


        //assign globalId to chunk
        if (palette != NULL) {
            ch->sectionArr[sectionIndex].blockMatrix[y][z][x].globalId = palette[globalId] >> 4;
        }
        else
        {
            ch->sectionArr[sectionIndex].blockMatrix[y][z][x].globalId = globalId >> 4;
        }

       int DEBUGFLAG = 2;
        if (ch->x == 3 && ch->z == 1) {
            if (DEBUGFLAG++ == 1) {

                printf("Dumped 3-1 to file\n");
            }
            int posByte = cLongArr - data + (longIndex * 8) + (bitIndex / 8) + 10 + 2;
            file_io_write_formatted_to_file("./chunk3-1_DUMP.txt", "wrote global id: %d to pos [%d][%d][%d] at rel byte %d from data, lIndex %d / bitIndex %d\n", ch->sectionArr[sectionIndex].blockMatrix[y][z][x].globalId, y, z, x, posByte,  ch->sectionArr[sectionIndex].blockMatrix[y][z][x].longIndex,  ch->sectionArr[sectionIndex].blockMatrix[y][z][x].bitIndex);

            if (ll != longIndex) {
                file_io_write_formatted_to_file("./chunk3-1_DUMP.txt", "Advanced long\n");
                ll = longIndex;
            }
        }
    }

    const uint8_t * byteAfterCLongArr = cLongArrDim.byteAfterEnd + cLongArrDim.value * sizeof(long);
    const uint8_t * endPtr = byteAfterCLongArr + CHUNKSECTION_BLOCKCOUNT / 2;

    //placeholder if for dimension checking
    if (1) {
        endPtr += CHUNKSECTION_BLOCKCOUNT / 2;
    }
    free(palette);
    return endPtr;
}

void internal_v1_12_2_deserializer_chunkData(const uint8_t *data, int dataLen, struct client *c) {

        int sectionsPerChunk = 16;
        TChunk * chunkToLoad = malloc(sizeof(TChunk));
        chunkToLoad->sectionArr = malloc(sectionsPerChunk * sizeof(TChunkSection));
        chunkToLoad->sectionArrDim = sectionsPerChunk;
        chunkToLoad->x = read_int32fromNetworkEndian(data);
        chunkToLoad->z = read_int32fromNetworkEndian(data + 4);
        int groundUpContinuous = read_boolean(data + 8);

        /*
        if(chunkToLoad->x == 0 && chunkToLoad->z == 0)
        {
            file_io_write_buffer_to_file("./c0-0.bin", data, dataLen);
            printf("wrote 0-0 to file\n");
        }
        if(chunkToLoad->x == 3 && chunkToLoad->z == 1)
        {
            printf("wrote 3-1 to file\n");
            file_io_write_buffer_to_file("./c3-1.bin", data, dataLen);
        }*/


        TVarInt primaryBitMask = sharedMain_readVarInt(data + 9, VARINTMAXLEN);
        TVarInt sectionDataLen = sharedMain_readVarInt(primaryBitMask.byteAfterEnd, VARINTMAXLEN);

        const uint8_t * compactedLongArr = sectionDataLen.byteAfterEnd;
        for(int val = primaryBitMask.value, i = 0; val > 0; val >>= 1, i++)
        {
            if(val & 1) {
                uint8_t *byteAfterCurrentSection = oncePerSection(compactedLongArr, data - compactedLongArr + dataLen, chunkToLoad, i);
                if (byteAfterCurrentSection == NULL) {
                    return;
                }
                compactedLongArr = byteAfterCurrentSection;
            }
        }
        size_t hashKey = hash2d(chunkToLoad->x, chunkToLoad->z) % CHUNK_HASHVEC_DIM;

        if (groundUpContinuous)
        {
            TChunkHashNode *newNode = malloc(sizeof(TChunkHashNode));
            newNode->chunk = chunkToLoad;
            newNode->tail = c->chunkHashVec[hashKey];
            printf("Successfully loaded chunk X: %d, Z: %d, at sectionIndex %d\n", chunkToLoad->x, chunkToLoad->z, hashKey);
            c->chunkHashVec[hashKey] = newNode;
            fflush(stdout);
        }
        else
        {
            TChunkHashNode *existingNode = c->chunkHashVec[hashKey];
            TChunkHashNode *prevNode = NULL;

            while (existingNode != NULL) {
                if (existingNode->chunk->x == chunkToLoad->x && existingNode->chunk->z == chunkToLoad->z) {
                    // Refreshing sections based on primaryBitMask
                    printf("Refreshing chunk X: %d, Z: %d at sectionIndex %d\n", chunkToLoad->x, chunkToLoad->z, hashKey);

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
