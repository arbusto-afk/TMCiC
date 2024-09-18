//
// Created by Ignacio on 9/17/2024.
//

#ifndef MCBC4_PDEF_V12_2_2_C
#define MCBC4_PDEF_V12_2_2_C

#include <string.h>
#include <stdio.h>
#include "crossSocket/crossSocket.h"
#include "Client/client.h"
#include "Parser/parser.h"

int pDef_v1_12_2_Interpreter(uint8_t  * buf, client * c);
packet_t pDef_V12_2_2_createHandShakePacket(int protocolVer, const unsigned char *serverAdress, unsigned short port, int nextState);
packet_t pDef_V12_2_2_createLoginPacket(const char *playerName);

#endif //MCBC4_PDEF_V12_2_2_C
