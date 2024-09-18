//
// Created by Ignacio on 9/17/2024.
//

#include "pDef_v1_12_2_2.h"

#define TYPELONG_BYTESIZE 8
#define v1_12_2_CPID_SERVERBOUND_KEEPALIVE 0x0B // client packet id
#define v1_12_2_CPID_CLIENTBOUND_KEEPALIVE 0x1F
#define v1_12_2_CPID_CLIENTBOUND_LOGINSUCCESS 0x02
#define v1_12_2_CPID_CLIENTBOUND_DISCONNECT_PLAY 0x1A
#define v1_12_2_CPID_CLIENTBOUND_DISCONNECT_LOGIN 0x00
#define v1_12_2_CPID_CLIENTBOUND_SETCOMPRESSION 0x03

#include "pDef_v1_12_2_2.h"

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

static packetHandler_t defaultPackets_stateStatus[MAXPACKETID] = {0};
static packetHandler_t stateLoginPackets[MAXPACKETID] = {
        [v1_12_2_CPID_CLIENTBOUND_DISCONNECT_LOGIN] = onDisconnect,
        [v1_12_2_CPID_CLIENTBOUND_LOGINSUCCESS] = onLoginSuccess,
        [v1_12_2_CPID_CLIENTBOUND_SETCOMPRESSION] = onSetCompression};
static packetHandler_t stateConfigPackets[MAXPACKETID] = {};
static packetHandler_t statePlayPackets[MAXPACKETID] = {
        [v1_12_2_CPID_CLIENTBOUND_KEEPALIVE] = KeepAlive,
        [v1_12_2_CPID_CLIENTBOUND_DISCONNECT_PLAY] = onDisconnect};


static packetHandler_t *defaultHandler[CSTATE_TOTALCOUNT] = {
        [CSTATE_STATUS] = defaultPackets_stateStatus,
        [CSTATE_LOGIN] = stateLoginPackets,
        [CSTATE_TRANSFER] = stateConfigPackets,
        [CSTATE_PLAY] = statePlayPackets
};

int uncompressPacket(uint8_t *compressedData, int compressedSize, uint8_t *uncompressedData, int uncompressedSize);
/*int pDef_v1_12_2_Interpreter(uint8_t  * buf, client * c)
{
    return 0;
}*/
/*
static int uncompressPacket(uint8_t *compressedData, int compressedSize, uint8_t *uncompressedData, int uncompressedSize)
{
    if (compressedSize <= 0 || uncompressedSize <= 0) return Z_DATA_ERROR;

    z_stream stream = {0}; // Simplified initialization
    int status;

    stream.avail_in = compressedSize;
    stream.next_in = compressedData;
    stream.avail_out = uncompressedSize;
    stream.next_out = uncompressedData;

    status = inflateInit2(&stream, -MAX_WBITS); // Using raw deflate stream
    if (status != Z_OK)
    {
        return status;
    }

    status = inflate(&stream, Z_FINISH);
    inflateEnd(&stream);  // Always clean up

    return (status == Z_STREAM_END) ? Z_STREAM_END : status;
}
*/
int pDef_v1_12_2_Interpreter(uint8_t *buf, client *c) {
    TVarInt packetLen = sharedMain_readVarInt(buf, VARINTPACKETMAXLEN);
    int totalPacketLen = packetLen.value + packetLen.byteSize;

    TVarInt packetId;
    uint8_t *data = NULL;
    int dataLen;
    TVarInt  uncompressedPacketLen;
    void *memToFree = NULL; //in case of failed uncompression
    if (c->compressionTreshold < 0) {
        packetId = sharedMain_readVarInt(packetLen.byteAfterEnd, VARINTPACKETMAXLEN);
        dataLen = packetLen.value - packetId.byteSize;
        if (dataLen > 0)
            data = packetId.byteAfterEnd;
    }
    else
    {
        //Packet ID + data uncomrpessed len
        uncompressedPacketLen = sharedMain_readVarInt(packetLen.byteAfterEnd, VARINTPACKETMAXLEN);

        // compression set, but packet is smaller than treshold, interpret directly
        if (uncompressedPacketLen.value == 0) {
            packetId = sharedMain_readVarInt(uncompressedPacketLen.byteAfterEnd, VARINTPACKETIDMAXLEN);
            dataLen = packetLen.value - uncompressedPacketLen.byteSize;
            if (dataLen > 0)
                data = packetId.byteAfterEnd;
        }
        else
        {
            printf("<cmplen %d>, ", packetLen.value);
            return 0;
            /*
            uint8_t * compressedData = uncompressedPacketLen.byteAfterEnd;
            int compressedDim = packetLen.value - uncompressedPacketLen.byteSize;

            uint8_t *uncompressedData = malloc(uncompressedPacketLen.value);
            if(errno == ENOMEM || uncompressedData == NULL){
                printf("malloc failure in packet interpreter");
                free(uncompressedData);
                return -1;
            }
            memToFree = uncompressedData;

            int result = uncompressPacket(compressedData, compressedDim, uncompressedData, uncompressedPacketLen.value);
            if (result != Z_STREAM_END)
            {
                printf("Decompression failed: %d , packetLen: %d, no:(   flushing packet\n", result, packetLen.value);
                free(uncompressedData);
                free(memToFree);
                //  return totalPacketLen;
                return 1;
            }
            packetId = sharedMain_readVarInt(uncompressedData, VARINTPACKETIDMAXLEN);
            data = packetId.byteAfterEnd;
            dataLen = uncompressedPacketLen.value - packetId.byteSize;
             */
        }


    }

    int handledPacket = 0;
    if(packetId.value > MAXPACKETID){
        printf("abort,");
        return 0;
    }
    if (defaultHandler[c->state] != NULL && defaultHandler[c->state][packetId.value] != NULL) {
        handledPacket = 1;
        printf("<h:%d>, ", packetId.value);
        defaultHandler[c->state][packetId.value](data, dataLen, c);
    }
    if (c->state = CSTATE_PLAY && c->customPlayStateHandler != NULL && c->customPlayStateHandler[packetId.value] != NULL) {
        handledPacket = 1;
        c->customPlayStateHandler[packetId.value](data, dataLen, c);
    }
    if(handledPacket == 0){
        printf("%02x, ", packetId.value);
    }
    return 0;
}

packet_t pDef_V12_2_2_createHandShakePacket(int protocolVer, const unsigned char *serverAdress, unsigned short port, int nextState) {
    unsigned char *handshakePacket = malloc(1024); // 0.5kb
    if (!handshakePacket) {
        perror("Failed to allocate memory for handshake packet");
        exit(EXIT_FAILURE);
    }

    unsigned char *startAdress = handshakePacket;
    (*handshakePacket) = 0x00; // handshake packet id
    handshakePacket++;
    handshakePacket = sharedMain_writeVarInt(handshakePacket, protocolVer);
    handshakePacket = sharedMain_writeString(handshakePacket, serverAdress);
    *handshakePacket = (port >> 8) & 0xFF;
    handshakePacket++;
    *handshakePacket = port & 0xFF;
    handshakePacket++;
    handshakePacket = sharedMain_writeVarInt(handshakePacket, nextState);
    int prePacketByteSize = handshakePacket - startAdress;

    int varIntSize = sharedMain_getSizeAsVarInt(prePacketByteSize);
    printf("varint size %d pre packet:%d\n", varIntSize, prePacketByteSize);

    packet_t res;
    res.dim = prePacketByteSize + varIntSize;
    res.seq = malloc(res.dim);
    unsigned char *aux = sharedMain_writeVarInt(res.seq, prePacketByteSize);
    memcpy(aux, startAdress, prePacketByteSize);
    free(startAdress);

    return res;
}

packet_t pDef_V12_2_2_createLoginPacket(const char *playerName) {
    unsigned char *loginPacket = malloc(256);
    unsigned char *startPtr = loginPacket;
    (*loginPacket) = 0x00; // login packet id
    loginPacket++;
    loginPacket = sharedMain_writeString(loginPacket, playerName);
    // loginPacket = writeUUID(loginPacket);
    int loginPacketByteSize = loginPacket - startPtr;
    int dataLen = sharedMain_getSizeAsVarInt(loginPacketByteSize);

    unsigned char *finalLoginPacket = malloc(dataLen + loginPacketByteSize);
    unsigned char *finalStartAdress = finalLoginPacket;
    finalLoginPacket = sharedMain_writeVarInt(finalLoginPacket, loginPacketByteSize);
    finalLoginPacket = memcpy(finalLoginPacket, startPtr, loginPacketByteSize);
    free(startPtr);
    long byteLength = finalLoginPacket - finalStartAdress + loginPacketByteSize;

    packet_t res;
    res.seq = finalStartAdress;
    res.dim = byteLength;
    return res;
}