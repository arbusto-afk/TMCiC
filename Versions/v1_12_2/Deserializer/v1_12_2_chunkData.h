//
// Created by Ignacio on 28/9/2024.
//

#ifndef MCBC6_V1_12_2_CHUNKDATA_H
#define MCBC6_V1_12_2_CHUNKDATA_H
#include "../../../Defs/ChunkHashFunc.h"
#include "../../../crossSocket/crossSocket.h"
#include "../../../Defs/ClientDef.h"
#include "../../../Defs/ChunkDef.h"
#include "../../../Parser/parser.h"
#include "../../../TVarInt/sharedmain.h"

void internal_v1_12_2_deserializer_chunkData(const uint8_t *data, int dataLen, struct client *c);

#endif //MCBC6_V1_12_2_CHUNKDATA_H
