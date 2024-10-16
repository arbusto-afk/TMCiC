//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_V1_12_2_INTERPRETER_H
#define MCBC6_V1_12_2_INTERPRETER_H
#include "../../../Defs/ClientDef.h"
#include "../../../TVarInt/TVarInt.h"
#include "../../../Defs/ErrorCodes.h"
#include <zlib.h>
#include <stdio.h>
#include <errno.h>

int internal_v1_12_2_defaultInterpreter(const uint8_t  * buf, client * c);

#endif //MCBC6_V1_12_2_INTERPRETER_H
