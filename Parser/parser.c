//
// Created by Ignacio on 9/13/2024.
//

#include "parser.h"
#include <string.h>


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

#define LOGPACKETSTOFILE 1
#define LOGPARSINGTOFILE 1

        //print error or log success
        int handlerExitCode = internal_parser_defaultInterpreter(buf, c);
        if (handlerExitCode < 0)
        {
            char msg[256];
            sprintf(msg,"Parser: Error %d interpreting packet with seq:", handlerExitCode);
            printf("%s", msg);
            file_io_write_formatted_to_file(c->packetInterpretingLogPath, "%s", msg);
            for(int i = 0; i < 25; i++) {
                printf("%02x ", buf[i]);
                file_io_write_formatted_to_file(c->packetInterpretingLogPath, "%02x", buf[i]);
            }
            file_io_write_formatted_to_file(c->packetInterpretingLogPath, "\n");
            printf("\n");
            fflush(stdout);
            return procBytes;
        }
        else
        {
#if LOGPACKETSTOFILE
    //        printf("succesfully interpt packet %d\n", handlerExitCode);
            file_io_write_formatted_to_file(c->packetInterpretingLogPath, "packet [0x%02x] %d\n",handlerExitCode, handlerExitCode);
#endif
        }

#if LOGPARSINGTOFILE
        file_io_write_formatted_to_file(c->packetParserLogPath, "<");
        file_io_write_hex_to_file(c->packetParserLogPath, buf, totalPacketLen);
        file_io_write_formatted_to_file(c->packetParserLogPath, ">\n");
#endif


        // Move the buffer forward and update counters
     //   printf("<p:%d>", totalPacketLen);
        buf += totalPacketLen;
        procBytes += totalPacketLen;
        remainingBytes -= totalPacketLen;
    }

    return procBytes;
}
