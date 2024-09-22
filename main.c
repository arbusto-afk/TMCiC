#include <stdio.h>


#include "Defs/clientDef.h"
#include "crossSocket/crossSocket.h"
#include "Parser/parser.h"
#include "Versions/v1_12_2/pDef_v1_12_2_2.h"

#include "file_io/file_io.h"
#include "Versions/v1_12_2/Interpreter/Interpreter.h"
#include "Defs/clientDef.h"
#include "Versions/v1_12_2/HshakeAndLogin/HshakeAndLogin.h"
#include "Defs/PacketDef.h"

#define MAXBUFDIM 1024 * 1024 //1mb

void sendHandshakeAndLogin(client * c)
{
    packet_t hShake = public_V1_12_2_createHandShakePacket(340, c->hostname, c->port, 2);
    packet_t login = public_V1_12_2_createLoginPacket(c->playerName);
    simpleSocket_send(c->sockfd, hShake.seq, hShake.dim);
    simpleSocket_send(c->sockfd, login.seq, login.dim);
    free(hShake.seq);
    free(login.seq);
    c->state = CSTATE_LOGIN;
}
client * initializeAndConnectClient(char *playerName, char *hostname, int port, char * version, packetHandler_t *customHandler)
{
    int sockfd = simpleSocket_setSocket(hostname, port);

    if (sockfd < 0)
    {
        printf("Failed to connect to server %s from client object\n", hostname);
        return NULL;
    }
    printf("Succesfully created socket with id %d\n",sockfd);

    if(!parser_isSupportedVersion(version)) {
        printf("Error unsupported version %s", version);
        return NULL;
    }
    client *c = malloc(sizeof(client));

    c-> version = version;
    //TODO map version to index;
    if(1) {
        c->packetInterpreter = internal_v1_12_2_defaultInterpreter;
        c->defaultGeneralHandler = internal_v1_12_2_defaultGeneralHandler;
    }
    c->compressionTreshold = -1;
    c->sockfd = sockfd;
    c->state = -1;
    c->playerName = playerName;
    c->hostname = hostname;
    c->port = port;
    c->customPlayStateHandler = customHandler;

    sendHandshakeAndLogin(c);
    return c;
}


int parser2(uint8_t * buf, int bufDim, client * c){
    TVarInt res = sharedMain_readVarInt(buf, bufDim);
    if(res.byteSize < 0) {
        printf("verr %d\n", res.byteSize);
            return 0;
    }
    puts("ok");
    return res.value + res.byteSize;
}

void startListening(client *c) {
    uint8_t buf[MAXBUFDIM] = {0};
   // for(int i=0; i <MAXBUFDIM;i++)
     //   buf[i] = 0x00;
    int bufdim = 0;  // The total size of unprocessed data in the buffer
    uint8_t *p = buf;  // Pointer to where new data should be written

    while (1) {
        // Receive data into the buffer starting at p
        int recvb = simpleSocket_receiveSocket(c->sockfd, p, MAXBUFDIM - bufdim);
    //    writeBufferToFile(p, bufdim + recvb);  // Write only the new bytes received

        if (recvb > 0) {
            bufdim += recvb;  // Increase the buffer size by the number of received bytes

            // Log the newly received data to the file
            // Process packets in the buffer
            int procB = parser_parseMcPacketsFromBuf(buf, bufdim, c);
         //   int procB = parser2(buf, bufdim, c);

            if (procB > 0) {
                bufdim -= procB;  // Update the remaining bytes in the buffer
                // Move unprocessed data to the beginning of the buffer
                if (bufdim > 0) {
                    memmove(buf, buf + procB, bufdim);
                }
                // Reset pointer to start of buffer
                p = buf + bufdim;  // Point to the next free space in the buffer
            }
        } else {
            if (recvb == 0) {
                printf("Connection closed by server\n");
            } else {
                perror("Socket error:");
            }
            break;
        }
    }
    return;
}

void recvChunk(uint* buf, int datalen, client * c){
//    printf("\nRecveiced chunk\n");
};

int main(void) {

    char hostname[] = "ignacioFerrero.aternos.me";
    char username[] = "mcbc6";
    int port = 57188;
    char ver[] = "1.12.2";
    packetHandler_t customHandler[MAXPACKETID] = {[0X20] = (packetHandler_t) recvChunk};
    packetInterpreter_t customInterpreter = internal_v1_12_2_defaultInterpreter;

    client *c = initializeAndConnectClient(username, hostname, port, ver, customHandler);

    startListening(c);

    free(c);
    return 0;
}
