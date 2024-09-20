//
// Created by Ignacio on 9/16/2024.
//

#ifndef MCBC3_CLIENT_H
#define MCBC3_CLIENT_H
#include <stdint.h>
#

typedef struct client {
    int sockfd;
    int compressionTreshold;
    int state; //0 status, 1 login, 2 for transfer?, 3 configuration, 4 play
    char * playerName;
    char * hostname;
    int port;

    //TODO load interpreter according to version
    char * version;
    //both func should be assigned as soon as client is initiliazed;
    int (*packetInterpreter)(uint8_t *buf, struct client *c); //func called by parser, assigned depending on ver

    void (**customPlayStateHandler)(const uint8_t * data, int datalen, struct client * c); //packetHandler_t
} client;

typedef int (*packetInterpreter_t)(uint8_t *buf, client *c);
typedef void (*packetHandler_t)(const uint8_t * buf, int dataLen, client * c);
#endif //MCBC3_CLIENT_H
