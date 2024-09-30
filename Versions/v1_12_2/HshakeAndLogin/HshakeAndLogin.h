//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_HSHAKEANDLOGIN_H
#define MCBC6_HSHAKEANDLOGIN_H

#include "../../../Parser/parser.h"
#include "../../../Defs/ClientDef.h"
#include "../../../crossSocket/crossSocket.h"
#include "../../../Defs/PacketDef.h"
#include <stdio.h>
#include <string.h>

packet_t public_V1_12_2_createHandShakePacket(int protocolVer, const unsigned char *serverAdress, unsigned short port, int nextState);

packet_t public_V1_12_2_createLoginPacket(const char *playerName);

#endif //MCBC6_HSHAKEANDLOGIN_H
