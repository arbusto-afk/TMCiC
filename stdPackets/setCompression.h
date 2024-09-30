//
// Created by Ignacio on 28/9/2024.
//

#ifndef MCBC6_SETCOMPRESSION_H
#define MCBC6_SETCOMPRESSION_H

#include <stdlib.h>
#include <stdint.h>
#include "../../Defs/ClientDef.h"
#include "../../TVarInt/TVarInt.h"

void internal_std_packet_setCompression(const uint8_t * data, int dataLen, struct client * c);
#endif //MCBC6_SETCOMPRESSION_H
