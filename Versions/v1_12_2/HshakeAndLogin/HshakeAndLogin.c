//
// Created by Ignacio on 9/22/2024.
//

#include "HshakeAndLogin.h"

packet_t public_V1_12_2_createHandShakePacket(int protocolVer, const unsigned char *serverAdress, unsigned short port, int nextState) {
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

packet_t public_V1_12_2_createLoginPacket(const char *playerName) {
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
    int byteLength = finalLoginPacket - finalStartAdress + loginPacketByteSize;

    packet_t res;
    res.seq = finalStartAdress;
    res.dim = byteLength;
    return res;
}