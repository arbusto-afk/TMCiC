//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_INTERPRETER_H
#define MCBC6_INTERPRETER_H
#include "../../../Defs/clientDef.h"
#include "../../../TVarInt/TVarInt.h"
#include "../../../Defs/ErrorCodes.h"
#include <zlib.h>
#include <stdio.h>
#include <errno.h>

int internal_v1_12_2_defaultInterpreter(uint8_t  * buf, client * c);

#endif //MCBC6_INTERPRETER_H
