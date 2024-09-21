//
// Created by Ignacio on 9/17/2024.
//

#ifndef MCBC4_PDEF_V12_2_2_C
#define MCBC4_PDEF_V12_2_2_C

#define v1_12_2_CPID_SERVERBOUND_KEEPALIVE 0x0B // client packet id
#define v1_12_2_CPID_CLIENTBOUND_KEEPALIVE 0x1F
#define v1_12_2_CPID_CLIENTBOUND_LOGINSUCCESS 0x02
#define v1_12_2_CPID_CLIENTBOUND_DISCONNECT_PLAY 0x1A
#define v1_12_2_CPID_CLIENTBOUND_DISCONNECT_LOGIN 0x00
#define v1_12_2_CPID_CLIENTBOUND_SETCOMPRESSION 0x03

#include <string.h>
#include <stdio.h>
#include "crossSocket/crossSocket.h"
#include "Client/client.h"
#include "Parser/parser.h"
#include "zlib.h"

int pDef_v1_12_2_Interpreter(uint8_t  * buf, client * c);
packet_t pDef_V12_2_2_createHandShakePacket(int protocolVer, const unsigned char *serverAdress, unsigned short port, int nextState);
packet_t pDef_V12_2_2_createLoginPacket(const char *playerName);

#endif //MCBC4_PDEF_V12_2_2_C
