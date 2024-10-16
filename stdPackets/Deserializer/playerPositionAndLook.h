//
// Created by Ignacio on 29/9/2024.
//

#ifndef MCBC6_PLAYERPOSITIONANDLOOK_H
#define MCBC6_PLAYERPOSITIONANDLOOK_H

#include <stdlib.h>
#include <stdint.h>
#include "../../Defs/ClientDef.h"
#include "../../TVarInt/TVarInt.h"
#include "../../TVarInt/sharedmain.h"

#include "../Serializer/teleportConfirm.h"


void internal_std_packet_playerPositionAndLook(const uint8_t * data, int dataLen, struct client * c);

#endif //MCBC6_PLAYERPOSITIONANDLOOK_H
