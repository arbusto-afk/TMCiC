//
// Created by Ignacio on 9/22/2024.
//

#ifndef MCBC6_PACKETDEF_H
#define MCBC6_PACKETDEF_H

#include <stdint.h>

typedef struct packet{
    uint8_t * seq;
    int dim;
} packet_t;

#endif //MCBC6_PACKETDEF_H
