//
// Created by Ignacio on 9/13/2024.
//

#include "parser.h"

//InterpreterFunc interpreters[] = {pDef_V12_2_2_pInterpreter()};

//returns 1 if version is supported
//returns 0 if unsuported version
int parser_isSupportedVersion(char * version)
{
    //null terminated for maintance
    char * supportedVersions[] = {"1.12.2", 0};
    for(int i = 0; supportedVersions[i] != 0; i++){
        if(strcmp(version, supportedVersions[i]) == 0 ){
            return 1;
        }
    }
    return 0;
}
/*
 * Given a buffer attempts to parse packets until incomplete or invalid packet, in which case returns
 * byteConsumed so that the begining of the incomplete packet is the new start of the bufer
 * Returns amount of bytes consumed
 * Calls packetInterpreter which must be present on the client
 * Version independant
 */

int parser_parseMcPacketsFromBuf(uint8_t *buf, int bufDim, client *c)
{
    // If bufDim is zero or less, there's nothing to parse
    if (bufDim <= 0) {
        printf("emptyBuf");
        printf("<PARSEREXIT>, ");

        return 0;
    }

    int procBytes = 0;
    int remainingBytes = bufDim;

    while (remainingBytes > 0)
    {
        TVarInt packetLen = sharedMain_readVarInt(buf, remainingBytes);

        // Error: could not interpret a valid VarInt, incomplete or invalid packet
        if (packetLen.byteSize < 0)
        {
            printf("parser: Error %d reading varint at %p with seq: [", packetLen.byteSize, buf);
            for (int i = 0; i < remainingBytes && i < VARINTMAXLEN; i++)
                printf("%02x ", buf[i]);
            printf("]\n");
            printf("<PARSEREXIT>");
            return procBytes;
        }
        int totalPacketLen = packetLen.value + packetLen.byteSize;

        // Check for invalid or overly large packet lengths
        if (totalPacketLen > remainingBytes)
        {
            return procBytes;
        }
        if(totalPacketLen < 0) {
            return procBytes;
        }

        // Handle complete packet
     /*
        printf("Parsed <");
        for(int i=0; i <totalPacketLen && i < 5; i++)
            printf("%02x ", buf[i]);
        if(totalPacketLen >= 5) {
            printf("... ");
            for(int i = totalPacketLen - 10; i < totalPacketLen; i++)
                printf("%02x ", buf[i]);
            printf(">\n");
        } else {
            printf(">\n");
        }*/
        int handlerExitCode = c->packetInterpreter(buf, c);
        if (handlerExitCode != 0)
        {
            printf("Parser: Error interpreting complete packet %d with totallen: %d\n", handlerExitCode, totalPacketLen);
          //  for(int i = 0; i < 50; i++)
          //      printf( "%02x ", buf[i]);
         //   fflush(stdout);
            return procBytes;
        }

        // Move the buffer forward and update counters
     //   printf("<p:%d>", totalPacketLen);
        buf += totalPacketLen;
        procBytes += totalPacketLen;
        remainingBytes -= totalPacketLen;
    }

    return procBytes;
}
