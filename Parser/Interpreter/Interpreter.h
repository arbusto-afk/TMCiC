//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_INTERPRETER_H
#define MCBC6_INTERPRETER_H
#include "../../Defs/ClientDef.h"
#include "../../TVarInt/TVarInt.h"
#include "../../Defs/ErrorCodes.h"
#include "../../file_io/file_io.h"
#include <zlib.h>
#include <stdio.h>
#include <errno.h>
/*
 * Returns and int corresponding to packetId or error code if negative
 * Assumes complete packet with varint of packetLen;
 */
int internal_parser_defaultInterpreter(const uint8_t  * buf, client * c);

#endif //MCBC6_INTERPRETER_H
