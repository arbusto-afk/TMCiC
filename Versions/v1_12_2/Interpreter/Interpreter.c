//
// Created by Ignacio on 9/22/2024.
//

#include "Interpreter.h"

/*
 * Receves packetId as int, pointer to data after packetId, dataLen, c
 * Returns 0 or error
 * Assumes internal_v1_12_2_defaultGeneralHandler != NULL
 */
static int pDef_v1_12_2_handlePacketById(int packetId, uint8_t * data, int dataLen, client *c){
    int handledPacket = 0;
    //internal_v1_12_2_defaultGeneralHandler
    if (c->defaultGeneralHandler[c->state] != NULL && c->defaultGeneralHandler[c->state][packetId] != NULL)
    {
        handledPacket = 1;
        printf("<dh:0x%02x>, ", packetId);
        c->defaultGeneralHandler[c->state][packetId](data, dataLen, c);
    }
    //customPlayHandler
    if (c->state == CSTATE_PLAY && c->customPlayStateHandler != NULL && c->customPlayStateHandler[packetId] != NULL)
    {
        handledPacket = 1;
        printf("<ch:0x%02x>, ", packetId);
        c->customPlayStateHandler[packetId](data, dataLen, c);
    }
    //unhandled packet
    if(handledPacket == 0)
    {
        printf("<uh:0x%02x>,", packetId);
    }
    fflush(stdout);
    return 0;
}
/*
 * Takes data (excluding first packetLen), datalen and c
 */
static int packetWoutComp(const uint8_t * data, int dataLen, client * c)
{
    int aux = VARINTMAXLEN;
    if(dataLen < VARINTMAXLEN)
        aux = dataLen;
    TVarInt packetId = sharedMain_readVarInt(data, aux);
    if(packetId.byteSize < 0)
        return packetId.byteSize;

    int fDataLen = dataLen - packetId.byteSize;
    return pDef_v1_12_2_handlePacketById(packetId.value, packetId.byteAfterEnd, fDataLen, c);
}
/*
 * Takes data (excluding first packetLen), datalen and c
 */
static int packetWithCompOff(const uint8_t * data, int dataLen, client * c) {
    TVarInt uncDataLen = sharedMain_readVarInt(data, dataLen);
    if (uncDataLen.byteSize < 0)
        return uncDataLen.byteSize;
    if (uncDataLen.value != 0) {
        printf("[");
        for(int i = 0; i < 5; i++)
            printf("%02x ", data[i]);
        printf("]\n");
        return v1_12_2_ERR_SENT_COMP_TO_UNCOMP_HANDLER;
        }
    TVarInt packetId = sharedMain_readVarInt(uncDataLen.byteAfterEnd, dataLen - uncDataLen.byteSize);
    if(packetId.byteSize < 0)
        return packetId.byteSize;

    int fDataLen = dataLen - packetId.byteSize;
    return pDef_v1_12_2_handlePacketById(packetId.value, packetId.byteAfterEnd, fDataLen, c);
}
/*
 * Takes data (excluding first packetLen), datalen and c
 */
static int packetWithCompOn(const uint8_t * data, int dataLen, client * c)
    {
        TVarInt uncompressedLen = sharedMain_readVarInt(data, dataLen);
        if(uncompressedLen.byteSize < 0)
            return uncompressedLen.byteSize -3;
        if(uncompressedLen.value == 0)
            return v1_12_2_ERR_SENT_UNCOMP_TO_COMP_HANDLER;

        uint8_t * uncompressedBuffer = calloc(1,uncompressedLen.value);
        if(uncompressedBuffer == NULL)
        {
            //free(uncompressedBuffer);
            return -1;
        }

       // uncompressPacket(uncompressedLen.byteAfterEnd, dataLen - uncompressedLen.byteSize, uncompressedBuffer, uncompressedLen.value);

        int status = uncompress(uncompressedBuffer, &uncompressedLen.value, uncompressedLen.byteAfterEnd, dataLen - uncompressedLen.byteSize);
        if (status == Z_STREAM_END || status == Z_OK)
        {
            // Decompression successful
        //   printf("Decompression completed successfully.\n");
        }
        else
        {
            // Handle errors (you can check specific error codes or handle all errors similarly)
        //  printf("Decompression failed with error code: %d\n", status);
          //  printf("Compressed size: %d\n", dataLen - uncompressedLen.byteSize);
           // printf("Expected uncompressed size: %d\n", uncompressedLen.value);
           free(uncompressedBuffer);
            return status;  // Return the error for further debugging
        }
      //  fflush(stdout);

        TVarInt packetId = sharedMain_readVarInt(uncompressedBuffer, uncompressedLen.value);
        if(packetId.byteSize < 0)
        {
            free(uncompressedBuffer);
            return packetId.byteSize - 2;
        }

        pDef_v1_12_2_handlePacketById(packetId.value,packetId.byteAfterEnd, uncompressedLen.value, c);

       // printf("Prefree");
       //    fflush(stdout);
        free(uncompressedBuffer);
        return 0;
    }
/*
 * Assumes complete packet
 */
int internal_v1_12_2_defaultInterpreter(const uint8_t *buf, client *c)
    {
            TVarInt packetLen = sharedMain_readVarInt(buf, VARINTPACKETMAXLEN);
            if (c->compressionTreshold < 0) {
                return packetWoutComp(packetLen.byteAfterEnd, packetLen.value, c);
            }
            else
            {
                //Packet ID + data uncomrpessed len
                TVarInt uncompressedPacketLen = sharedMain_readVarInt(packetLen.byteAfterEnd, VARINTPACKETMAXLEN);

                if (uncompressedPacketLen.value == 0)
                    return packetWithCompOff(packetLen.byteAfterEnd, packetLen.value, c);
                else
                    return packetWithCompOn(packetLen.byteAfterEnd, packetLen.value, c);

            }
        }