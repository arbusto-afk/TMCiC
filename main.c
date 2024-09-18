#include <stdio.h>


#include "Client/client.h"
#include "crossSocket/crossSocket.h"
#include "Parser/parser.h"
#include "pDef_v1_12_2_2.h"

#include "file_io/file_io.h"
#define MAXBUFDIM 1024 * 1024 //1mb

void sendHandshakeAndLogin(client * c)
{
    packet_t hShake = pDef_V12_2_2_createHandShakePacket(340, c->hostname, c->port, 2);
    packet_t login = pDef_V12_2_2_createLoginPacket(c->playerName);
    simpleSocket_send(c->sockfd, hShake.seq, hShake.dim);
    simpleSocket_send(c->sockfd, login.seq, login.dim);
    c->state = CSTATE_LOGIN;
}
client * initializeAndConnectClient(char *playerName, char *hostname, int port, char * version, packetHandler_t *customHandler, packetInterpreter_t versionPInterpreter)
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
    c->packetInterpreter = versionPInterpreter;

    c->compressionTreshold = -1;
    c->sockfd = sockfd;
    c->state = -1;
    c->playerName = playerName;
    c->hostname = hostname;
    c->port = port;
    //   c->customPlayStateHandler = customHandler;

    sendHandshakeAndLogin(c);
    return c;
}
void startListening(client *c)
{
    uint8_t buf[MAXBUFDIM] = {0};
    int bufdim = 0;  // The total size of unprocessed data in the buffer
    uint8_t *p = buf;  // Pointer to where new data should be written

    while (1) {
        // Receive data into the buffer starting at p
        int recvb = simpleSocket_receiveSocket(c->sockfd, p, MAXBUFDIM - bufdim);
        if (recvb > 0) {
            bufdim += recvb;  // Increase the buffer size by the number of received bytes

            // Process packets in the buffer
            int procB = parser_parseMcPacketsFromBuf(buf, bufdim, c);
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



int main(void) {

    char hostname[] = "ignacioFerrero.aternos.me";
    char username[] = "mcbc6";
    int port = 57188;
    char ver[] = "1.12.2";
    packetHandler_t customHandler[MAXPACKETID] = {NULL};
    packetInterpreter_t customInterpreter = pDef_v1_12_2_Interpreter;

    client *c = initializeAndConnectClient(username, hostname, port, ver, customHandler, customInterpreter);

    startListening(c);
    return 0;
}