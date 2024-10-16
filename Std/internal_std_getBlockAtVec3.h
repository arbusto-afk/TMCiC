//
// Created by Ignacio on 14/10/2024.
//

#ifndef MCBC6_INTERNAL_STD_GETBLOCKATVEC3_H
#define MCBC6_INTERNAL_STD_GETBLOCKATVEC3_H

#include "../Defs/ChunkDef.h"
#include "../Defs/ChunkHashFunc.h"
#include "../Defs/ClientDef.h"
#include "internal_std_getChunk.h"
#include <math.h>

/*
 * Returns TBlock *, null on error
 */
TBlock * getBlockAtVec3(int x, int y, int z, client * c);

#endif //MCBC6_INTERNAL_STD_GETBLOCKATVEC3_H
