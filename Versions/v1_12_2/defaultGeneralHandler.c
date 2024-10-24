//
// Created by Ignacio on 9/17/2024.
//

#include "defaultGeneralHandler.h"

#include "../../stdPackets/stdPackets.h"
#include "Deserializer/v1_12_2_chunkData.h"
#include "Deserializer/v1_12_2_blockChange.h"
//<editor-fold   desc="defines">
#define TYPELONG_BYTESIZE 8

#define BITFORSTATEMAYBEIDK 13 //base 2 logarithm of the number of block states, rounded up. For the current vanilla release, this is 13 bits per block.
//</editor-fold>

// default packet handler used for basic 1.12.2 operation

void internal_v1_12_2_loginSuccess(const uint8_t *buf, int dataLen, struct client *c) {
    c->state = CSTATE_PLAY;
}


//<editor-fold desc="packetHandler_t *defaultPacketHandler">
static packetHandler_t defaultPackets_stateStatus[MAXPACKETID] = {0};
static packetHandler_t stateLoginPackets[MAXPACKETID] = {
        [v1_12_2_CPID_CLIENTBOUND_DISCONNECT_LOGIN] = internal_std_packet_onDisconnect,
        [v1_12_2_CPID_CLIENTBOUND_LOGINSUCCESS] = internal_v1_12_2_loginSuccess,
        [v1_12_2_CPID_CLIENTBOUND_SETCOMPRESSION] = internal_std_packet_setCompression};
static packetHandler_t stateConfigPackets[MAXPACKETID] = {};
static packetHandler_t statePlayPackets[MAXPACKETID] = {
        [v1_12_2_CPID_CLIENTBOUND_KEEPALIVE] = internal_std_packet_KeepAlive,
        [v1_12_2_CPID_CLIENTBOUND_DISCONNECT_PLAY] = internal_std_packet_onDisconnect,
        [v1_12_2_CPID_CLIENTBOUND_CHUNKDATA] = internal_v1_12_2_deserializer_chunkData,
        [v1_12_2_CPID_CLIENTBOUND_PLAYER_POSITION_AND_LOOK] = internal_std_packet_playerPositionAndLook,
        [v1_12_2_CPID_CLIENTBOUND_BLOCKUPDATE] = internal_v1_12_2_deserializer_blockChange
};


packetHandler_t *internal_v1_12_2_defaultGeneralHandler[CSTATE_TOTALCOUNT] = {
        [CSTATE_STATUS] = defaultPackets_stateStatus,
        [CSTATE_LOGIN] = stateLoginPackets,
        [CSTATE_TRANSFER] = stateConfigPackets,
        [CSTATE_PLAY] = statePlayPackets
};
//</editor-fold>

//</editor-fold>

