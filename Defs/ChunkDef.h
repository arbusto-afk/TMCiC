//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_CHUNKDEF_H
#define MCBC6_CHUNKDEF_H

#include "TPoint2d.h"
#define CHUNKSECTION_DIM 16

typedef struct {
    unsigned short id;
} TBlockId;

typedef struct {
    TBlockId arr[CHUNKSECTION_DIM][CHUNKSECTION_DIM][CHUNKSECTION_DIM];
    TBlockId *palette;
    int paletteDim;
} TChunkSection;

typedef struct {
    TPoint2d coords;

    TChunkSection * arr;
    int arrDim; //chunk height in sections
    TBlockId *palette;
    int paletteDim;
} TChunk;

#endif //MCBC6_CHUNKDEF_H
