//
// Created by Ignacio on 14/10/2024.
//

#include "internal_std_getBlockAtVec3.h"

TBlock * getBlockAtVec3(int x, int y, int z, client * c)
{
    TChunk * chunk = internal_std_getChunk(floor((double)x / CHUNKSECTION_DIM), floor((double)z/ CHUNKSECTION_DIM), c);
    if(chunk == NULL)
        return NULL;
    //searched y exceeds chunk height
    if(chunk->sectionArrDim >= y / CHUNKSECTION_DIM)
        return NULL;
    if(y < 0)
        return NULL;
    return &chunk->sectionArr[y/16].blockMatrix[y % 16][z - (int)floor((double)chunk->z / 16)][x - (int)floor((double)chunk->x / 16)];
}