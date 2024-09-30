//
// Created by Ignacio on 8/29/2024.
//

#ifndef SHAREDMAIN_H
#define SHAREDMAIN_H


#define TYPELONG_BITSIZE 64
#define TYPELONG_BYTESIZE 8
#define TYPEFLOAT_BYTESIZE 4
#include <stdlib.h>
#include <stdint.h>
#include "TVarInt.h"
#include <string.h>

//in 1.12.2 client goes from handshake directly to play
//1.12.2 status 1 login 2
// 1.12.2 login seq


double read_doubleFromNetworkEndian(const uint8_t *data);

float read_floatFromNetworkEndian(const uint8_t *data);

int read_uint8fromNetworkEndian(const uint8_t* data);

int8_t read_int8fromNetworkEndian(const uint8_t* data);

int read_boolean(const uint8_t* data);

int32_t read_int32fromNetworkEndian(const uint8_t* data);

int64_t read_int64fromNetworkEndian(const uint8_t *data);
/*
 * given a buffer write a string prefixed with its length as a varint
 * Assumes there is enough space in the buffer
 * Returns an unsigned char *  to the next byte after string
 */
unsigned char *sharedMain_writeString(unsigned char * buf, const char * str);

/*
 * Given an int returns its size as a varInt
 */
int sharedMain_getSizeAsVarInt(int n);


#endif //SHAREDMAIN_H
