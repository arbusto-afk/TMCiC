//
// Created by Ignacio on 9/17/2024.
//

#include "TVarInt.h"

TVarInt sharedMain_readVarInt(const uint8_t *buf, int bufDim) {

    if (buf == NULL) {
        return NULLVARINT;
    }
    if(bufDim < 0){
        return NULLVARINT;
    }

    int value = 0;
    int position = 0;
    int shift = 0;

    while (1) {
        if (position >= VARINTMAXLEN) {
            return NULLVARINTLENOVERFLOW;
        }
        if(position >= bufDim){
            return NULLVARINTLENOVERFLOW;
        }

        unsigned char byte = buf[position];
        value |= (byte & 0x7F) << shift;
        shift += 7;

        if (!(byte & 0x80)) break; // If the continuation bit is not set, stop reading

        position++;
    }
    TVarInt res = {value , position + 1 , buf + (position + 1)};
    return res;
}

uint8_t *sharedMain_writeVarInt(unsigned char *buf , int value) {
    if (value > VARINTMAXVAL || value < VARINTMINVAL) {
        //  setLerrno("sharedMain_writeVarInt varint out of bounds");
        return NULL;
    }
    if (buf == NULL) {
//        setLerrno("sharedMain_writeVarInt pointer is NULL");
        return NULL;
    }
    long long rawVal;
    if (value < 0)
        rawVal = VARINTMAXVAL - (long long)VARINTMINVAL+ value + 1;
    else
        rawVal = value;

    while (1) {
        *(buf) = rawVal & 0x7f;
        rawVal >>= 7;
        if (rawVal == 0)
            break;
        *(buf) |= 0x80;//turn on signed bit
        buf += 1;
    }
    //skipping one byte since here buf is the last byte used by the varint
    return buf + 1;
}
