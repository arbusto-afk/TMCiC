//
// Created by Ignacio on 23/10/2024.
//

#include "v1_12_2_blockChange.h"
#include "../../../Std/internal_std_getBlockAtVec3.h"

void internal_v1_12_2_deserializer_blockChange(const uint8_t *data, int dataLen, struct client *c)
{
    long position = read_int64fromNetworkEndian(data);
    //position type x as 26bits, followed by z 26 bits, y 12 bits
    int x = (position >> 38) & 0x3FFFFFF;  // Extract the first 26 bits for x
    int z = (position >> 12) & 0x3FFFFFF;  // Extract the next 26 bits for z
    int y = position & 0xFFF;              // Extract the last 12 bits for y

    // Convert x and z to signed 26-bit integers if necessary
    if (x >= (1 << 25)) x -= (1 << 26);  // Handle two's complement for x
    if (z >= (1 << 25)) z -= (1 << 26);  // Handle two's complement for z
    TVarInt blockId = sharedMain_readVarInt(data + 8, dataLen - 8);
    if(blockId.byteSize < 0)
        return;
    TBlock * blockAt = getBlockAtVec3(x,y,z,c);
    if(blockAt == NULL)
        return;
    blockAt->globalId = blockId.value >>4;
}
