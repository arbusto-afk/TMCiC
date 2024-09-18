//
// Created by Ignacio on 8/29/2024.
//

#ifndef SHAREDMAIN_H
#define SHAREDMAIN_H

#include <stdlib.h>
#include <stdint.h>
#define CSTATE_STATUS 0
#define CSTATE_LOGIN 1
#define CSTATE_TRANSFER 2
#define CSTATE_CONFIGURATION 3
#define CSTATE_PLAY 4
#define CSTATE_TOTALCOUNT 5

//in 1.12.2 client goes from handshake directly to play
//1.12.2 status 1 login 2
// 1.12.2 login seq

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
