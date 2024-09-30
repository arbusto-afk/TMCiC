//
// Created by Ignacio on 29/9/2024.
//

#include <stdio.h>
#include "teleportConfirm.h"
#include "string.h"
//TODO compress when minimum treshold
void internal_std_packet_serialize_teleportConfirm(struct client *c, int Id) {
    // Temporary buffer to hold the uncompressed packet data
    uint8_t packetBuffer[10];
    int packetOffset = 0;

    // Step 1: Add the packet ID (0x00 for Teleport Confirm in 1.12.2)
    packetBuffer[packetOffset++] = 0x00;

    // Step 2: Add the teleport ID using sharedMain_writeVarInt
    packetOffset += sharedMain_writeVarInt(&packetBuffer[packetOffset], Id) - &packetBuffer[packetOffset];

    // Now we check if compression is needed
    uint8_t finalBuffer[20]; // Allocate buffer large enough to handle possible compression
    int finalOffset = 0;

    if (c->compressionTreshold > 0) {
        // Compression is enabled, check if we need to compress or send uncompressed
        if (packetOffset >= c->compressionTreshold) {
            // Packet should be compressed

            // Step 3: Add the packet length (with the data included), VarInt encoded
            finalOffset += sharedMain_writeVarInt(&finalBuffer[finalOffset], packetOffset + 1) - &finalBuffer[finalOffset];

            // Step 4: Add the uncompressed length (VarInt encoded), 0 (no data) means no compression
            finalOffset += sharedMain_writeVarInt(&finalBuffer[finalOffset], 0) - &finalBuffer[finalOffset];

            // Step 5: Copy the uncompressed data to the final buffer
            memcpy(&finalBuffer[finalOffset], packetBuffer, packetOffset);
            finalOffset += packetOffset;
        } else {
            // Send an uncompressed packet (compressionTreshold not reached)

            // Step 3: Add the packet length (VarInt encoded, length of uncompressed data + 1 for the compression length field)
            finalOffset += sharedMain_writeVarInt(&finalBuffer[finalOffset], packetOffset + 1) - &finalBuffer[finalOffset];

            // Step 4: Add 0 as the uncompressed length (no compression)
            finalBuffer[finalOffset++] = 0;

            // Step 5: Copy the uncompressed data to the final buffer
            memcpy(&finalBuffer[finalOffset], packetBuffer, packetOffset);
            finalOffset += packetOffset;
        }
    } else {
        // No compression, simple case
        // Step 3: Add the packet length (VarInt encoded, length of packetBuffer)
        finalOffset += sharedMain_writeVarInt(&finalBuffer[finalOffset], packetOffset) - &finalBuffer[finalOffset];

        // Step 4: Copy the uncompressed data to the final buffer
        memcpy(&finalBuffer[finalOffset], packetBuffer, packetOffset);
        finalOffset += packetOffset;
    }

    // Step 6: Send the complete packet in one go
    simpleSocket_send(c->sockfd, finalBuffer, finalOffset);
}
