//
// Created by Ignacio on 28/9/2024.
//


#include "keepAlive.h"

/*
 * Reads long and sends it to the server as a keepAlive response
 */
void internal_std_packet_KeepAlive(const uint8_t *data, int dataLen, struct client *c) {
    int typeLongByteSize = 8;
    uint8_t serverBoundKeepAliveId = 0x0B;
    uint8_t keepAliveResp[8 + 3] = {0x0A, 0x00, serverBoundKeepAliveId};
    memcpy(keepAliveResp + 3, data, typeLongByteSize);
    simpleSocket_send(c->sockfd, keepAliveResp, typeLongByteSize + 3);
}