//
// Created by Ignacio on 29/9/2024.
//

#ifndef MCBC6_TELEPORTCONFIRM_H
#define MCBC6_TELEPORTCONFIRM_H

#include "../../Defs/ClientDef.h"
#include "../../TVarInt/TVarInt.h"
#include "../../crossSocket/crossSocket.h"

void internal_std_packet_serialize_teleportConfirm(struct client * c, int Id);

#endif //MCBC6_TELEPORTCONFIRM_H
