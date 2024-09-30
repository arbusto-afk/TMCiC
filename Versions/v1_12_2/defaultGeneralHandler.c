//
// Created by Ignacio on 9/17/2024.
//

#include "pDef_v1_12_2_2.h"
//<editor-fold   desc="defines">
#define TYPELONG_BYTESIZE 8


//</editor-fold>

//<editor-fold desc="dph functions">
// default packet handler used for basic 1.12.2 operation
static void onSetCompression(const uint8_t *buf, int dataLen, struct client *c) {
    TVarInt cTreshold = sharedMain_readVarInt(buf, VARINTMAXLEN);
    c->compressionTreshold = cTreshold.value;
}

static void onDisconnect(const uint8_t *buf, int dataLen, struct client *c) {
    char *str = malloc(dataLen + 1);
    memcpy(str, buf, dataLen + 1);
    str[dataLen] = 0;
    printf("Disconnected w/ reason: %s", str);
    free(str);
}

static void onLoginSuccess(const uint8_t *buf, int dataLen, struct client *c) {
    c->state = CSTATE_PLAY;
}

static void KeepAlive(const uint8_t *data, int dataLen, struct client *c) {
    uint8_t keepAliveResp[TYPELONG_BYTESIZE + 3] = {0x0A, 0x00, v1_12_2_CPID_SERVERBOUND_KEEPALIVE};
    memcpy(keepAliveResp + 3, data, TYPELONG_BYTESIZE);
    simpleSocket_send(c->sockfd, keepAliveResp, TYPELONG_BYTESIZE + 3);
}
//</editor-fold>

//<editor-fold desc="packetHandler_t *defaultPacketHandler">
static packetHandler_t defaultPackets_stateStatus[MAXPACKETID] = {0};
static packetHandler_t stateLoginPackets[MAXPACKETID] = {
        [v1_12_2_CPID_CLIENTBOUND_DISCONNECT_LOGIN] = onDisconnect,
        [v1_12_2_CPID_CLIENTBOUND_LOGINSUCCESS] = onLoginSuccess,
        [v1_12_2_CPID_CLIENTBOUND_SETCOMPRESSION] = onSetCompression};
static packetHandler_t stateConfigPackets[MAXPACKETID] = {};
static packetHandler_t statePlayPackets[MAXPACKETID] = {
        [v1_12_2_CPID_CLIENTBOUND_KEEPALIVE] = KeepAlive,
        [v1_12_2_CPID_CLIENTBOUND_DISCONNECT_PLAY] = onDisconnect};


packetHandler_t *internal_v1_12_2_defaultGeneralHandler[CSTATE_TOTALCOUNT] = {
        [CSTATE_STATUS] = defaultPackets_stateStatus,
        [CSTATE_LOGIN] = stateLoginPackets,
        [CSTATE_TRANSFER] = stateConfigPackets,
        [CSTATE_PLAY] = statePlayPackets
};
//</editor-fold>

//</editor-fold>

