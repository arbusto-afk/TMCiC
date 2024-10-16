//
// Created by Ignacio on 30/9/2024.
//

#ifndef MCBC6_INTERNAL_STD_GETCHUNK_H
#define MCBC6_INTERNAL_STD_GETCHUNK_H
#include "../Defs/ErrorCodes.h"
#include "../Defs/ChunkDef.h"
#include "../Defs/ClientDef.h"
#include "../Defs/ChunkHashFunc.h"

/*
 * Returns Tchunk *, or NULL if chunk not found
 */
TChunk * internal_std_getChunk(int x, int z, client *c);
#endif //MCBC6_INTERNAL_STD_GETCHUNK_H
