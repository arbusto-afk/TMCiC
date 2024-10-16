//
// Created by Ignacio on 28/9/2024.
//

#ifndef MCBC6_DISCONNECT_H
#define MCBC6_DISCONNECT_H

#include "../../TVarInt/TVarInt.h"
#include "../../Defs/ClientDef.h"
#include <stdio.h>
#include <string.h>

void internal_std_packet_onDisconnect(const uint8_t *buf, int dataLen, struct client *c);
#endif //MCBC6_DISCONNECT_H
