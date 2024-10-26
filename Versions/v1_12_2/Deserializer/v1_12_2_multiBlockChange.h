//
// Created by Ignacio on 25/10/2024.
//

#ifndef MCBC6_V1_12_2_MULTIBLOCKCHANGE_H
#define MCBC6_V1_12_2_MULTIBLOCKCHANGE_H

#include "../../../Defs/ChunkHashFunc.h"
#include "../../../Std/internal_std_getChunk.h"
#include "../../../Std/internal_std_getBlockAtVec3.h"
#include "../../../crossSocket/crossSocket.h"
#include "../../../Defs/ClientDef.h"
#include "../../../Defs/ChunkDef.h"
#include "../../../Parser/parser.h"
#include "../../../TVarInt/sharedmain.h"


void internal_v1_12_2_deserializer_multiBlockChange(const uint8_t *data, int dataLen, struct client *c);

#endif //MCBC6_V1_12_2_MULTIBLOCKCHANGE_H
