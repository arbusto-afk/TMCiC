//
// Created by Ignacio on 30/9/2024.
//

#include "public_getBlockAtCoords.h"

int public_getBlockAtCoords(int x, int y, int z, struct client * c)
{
    int chunkX = floor(x / 16);
    int chunkZ = floor(z / 16);
    int sectionIndex = floor(y / 16);
    TChunk * chunk = internal_std_getChunk(chunkX, chunkZ, c);
    if(chunk == NULL)
        return ERR_FINDBLOCK_AT_UNLOADED_CHUNK;
    if(sectionIndex >= chunk->sectionArrDim)
        return ERR_FINDBLOCK_HEIGHT_BEYOND_CHUNKHEIGHT;
    TBlock block = chunk->sectionArr[sectionIndex].blockMatrix[y - sectionIndex * 16][z - chunkZ * 16][x - chunkX * 16];
    return block.globalId;
}