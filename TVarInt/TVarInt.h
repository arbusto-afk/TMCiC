//
// Created by Ignacio on 9/17/2024.
//

#ifndef MCBC6_TVARINT_H
#define MCBC6_TVARINT_H


#define VARINTMAXLEN 5
#define VARINTPACKETIDMAXLEN 3
#define VARINTPACKETMAXLEN 3
#define VARINTMAXVAL 2147483647
#define VARINTMINVAL -2147483648

#include <stdint.h>
#include <stdlib.h>

/*
 * C→S: Handshake with Next State set to 2 (login)
C→S: Login Start
S→C: Encryption Request
Client auth
C→S: Encryption Response
Server auth, both enable encryption
S→C: Set Compression (optional)
S→C: Login Success
 */
typedef struct varInt{
    int value;
    int byteSize;
    uint8_t *byteAfterEnd;
} TVarInt;


#define VARINTEXCEEDSMAXLEN -2000
#define NULLVARINT ((TVarInt){0, -1, NULL})
#define NULLVARINTLENOVERFLOW ((TVarInt){0,VARINTEXCEEDSMAXLEN,NULL})


/*
 * Given a buffer interprets a varInt
 * Performs compulsory  bounds checking
 * Return a varint or nullVarInt on error
 */
TVarInt sharedMain_readVarInt(const uint8_t *buf, int bufDim);

/*
 * Writes a varInt into a mem address
 * Assumes there is enough space in the buffer
 * Returns byte after end
 * Returns NULLVARINT on incomplete, len excedeed varint, buf == NULL, dim < 0
 */
uint8_t *sharedMain_writeVarInt(uint8_t *address, int value);

#endif //MCBC6_TVARINT_H
