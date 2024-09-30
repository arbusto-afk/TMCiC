//
// Created by Ignacio on 28/9/2024.
//

#include "disconnect.h"
/*
 * Logs disconnect cause
 */
void internal_std_packet_onDisconnect(const uint8_t *buf, int dataLen, struct client *c) {
    char *str = malloc(dataLen + 1);
    memcpy(str, buf, dataLen + 1);
    str[dataLen] = 0;
    printf("Disconnected w/ reason: %s", str);
    free(str);
}