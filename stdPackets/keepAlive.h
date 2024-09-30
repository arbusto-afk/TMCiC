//
// Created by Ignacio on 28/9/2024.
//

#ifndef MCBC6_KEEPALIVE_H
#define MCBC6_KEEPALIVE_H

#include <stdint.h>
#include <string.h>
#include "../../TVarInt/TVarInt.h"
#include "../../Defs/ClientDef.h"
#include "../../crossSocket/crossSocket.h"

void internal_std_packet_KeepAlive(const uint8_t *data, int dataLen, struct client *c);

#endif //MCBC6_KEEPALIVE_H
