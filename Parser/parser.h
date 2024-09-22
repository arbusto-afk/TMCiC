//
// Created by Ignacio on 9/16/2024.
//

#ifndef MCBC3_PARSER_H
#define MCBC3_PARSER_H

#include "../Defs/clientDef.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "../TVarInt//sharedmain.h"
#include "../TVarInt/TVarInt.h"
#include "../file_io/file_io.h"

#define MAXPACKETID 128

int parser_isSupportedVersion(char * version);

int parser_parseMcPacketsFromBuf(unsigned char *buf, int bufDim, client *c);

#endif //MCBC3_PARSER_H
