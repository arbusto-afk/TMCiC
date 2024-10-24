//
// Created by Ignacio on 14/10/2024.
//

#include "internal_std_getBlockAtVec3.h"
/*
 * Returns NULL or invalid position or unloaded chunk
 * Retuns TBlock *
 */
TBlock * getBlockAtVec3(int x, int y, int z, client * c)
{
    TChunk * chunk = internal_std_getChunk(floor((double)x / CHUNKSECTION_DIM), floor((double)z/ CHUNKSECTION_DIM), c);
    if(chunk == NULL)
        return NULL;
    //searched y exceeds chunk height
    if(chunk->sectionArrDim <= y / CHUNKSECTION_DIM)
        return NULL;
    if(y < 0)
        return NULL;
    int chx = x - chunk->x * 16;
    int chz = z - chunk->z * 16;
    int secY = y % CHUNKSECTION_DIM;
    TBlock * retVal = &chunk->sectionArr[y/chunk->sectionArrDim].blockMatrix[secY][chz][chx];
    return retVal;
}