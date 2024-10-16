//
// Created by Ignacio on 28/9/2024.
//

#include "setCompression.h"

//these function expected only data not containing packet Id,in other words packetId.byteAfterEnd
void internal_std_packet_setCompression(const uint8_t *buf, int dataLen, struct client *c) {
    TVarInt cTreshold = sharedMain_readVarInt(buf, VARINTMAXLEN);
    c->compressionTreshold = cTreshold.value;
}