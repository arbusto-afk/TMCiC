//
// Created by Ignacio on 30/9/2024.
//

#ifndef MCBC6_PUBLIC_GETBLOCKATCOORDS_H
#define MCBC6_PUBLIC_GETBLOCKATCOORDS_H

#include <math.h>
#include "../Defs/ChunkDef.h"
#include "../Defs/ClientDef.h"
#include "../Defs/ChunkHashFunc.h"
#include "../Defs/ErrorCodes.h"
#include "../Std/internal_std_getChunk.h"


int public_getBlockAtCoords(int x, int y, int z, struct client * c);

#endif //MCBC6_PUBLIC_GETBLOCKATCOORDS_H
