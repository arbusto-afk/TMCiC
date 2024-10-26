//
// Created by Ignacio on 23/10/2024.
//

#include "v1_12_2_blockChange.h"
#include "../../../Std/internal_std_getBlockAtVec3.h"

void internal_v1_12_2_deserializer_blockChange(const uint8_t *data, int dataLen, struct client *c) {
    int64_t position = read_int64fromNetworkEndian(data);

    // Extract x (26 bits), y (12 bits), and z (26 bits) in the correct ranges
    int x = (position >> 38) & 0x3FFFFFF;  // Top 26 bits for x
    int y = (position >> 26) & 0xFFF;      // Middle 12 bits for y
    int z = position & 0x3FFFFFF;          // Bottom 26 bits for z

    // Convert to signed integers
    if (x >= (1 << 25)) x -= (1 << 26);
    if (y >= (1 << 11)) y -= (1 << 12);
    if (z >= (1 << 25)) z -= (1 << 26);

    // Read the block ID as a VarInt, starting after the 8-byte position
    TVarInt blockId = sharedMain_readVarInt(data + 8, dataLen - 8);
    if (blockId.byteSize < 0) return;  // Return if VarInt is invalid

    // Update the block at (x, y, z) if found
    TBlock *blockAt = getBlockAtVec3(x, y, z, c);
    if (blockAt == NULL) return;

    blockAt->globalId = blockId.value >> 4;
}
