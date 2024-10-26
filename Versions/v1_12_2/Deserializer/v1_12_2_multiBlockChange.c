//
// Created by Ignacio on 25/10/2024.
//

#include "v1_12_2_multiBlockChange.h"


void internal_v1_12_2_deserializer_multiBlockChange(const uint8_t *data, int dataLen, struct client *c) {

    int chunkX =read_int32fromNetworkEndian(data);
    int chunkZ = read_int32fromNetworkEndian(data + 4);

    TVarInt arrayDim = sharedMain_readVarInt(data + 9, dataLen - 9);
    uint8_t * arrPtr = arrayDim.byteAfterEnd;
    for(int i = 0; i < arrayDim.value; i++)
    {
        uint8_t xzByte = read_uint8fromNetworkEndian(arrPtr);
        int blockX = (xzByte >> 4) & 15;
        int blockZ = xzByte& 15;
        uint8_t blockY = read_uint8fromNetworkEndian(arrPtr + 1);
        TVarInt blockId = sharedMain_readVarInt(arrPtr + 2, VARINTMAXLEN);
        if(blockId.byteSize < 0)
            return;
        arrPtr = blockId.byteAfterEnd;
        TBlock * block = getBlockAtVec3(chunkX * 16 + blockX,  blockY, chunkZ * 16 + blockZ, c);
        block->globalId = blockId.value >> 4;
    }
}