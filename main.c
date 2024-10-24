#include <stdio.h>


#include "Defs/ClientDef.h"
#include "crossSocket/crossSocket.h"
#include "Parser/parser.h"
#include "Versions/v1_12_2/defaultGeneralHandler.h"

#include "file_io/file_io.h"
#include "Versions/v1_12_2/Interpreter/v1_12_2_Interpreter.h"
#include "Defs/ClientDef.h"
#include "Versions/v1_12_2/HshakeAndLogin/HshakeAndLogin.h"
#include "Defs/PacketDef.h"

#include "Std/internal_std_getBlockAtVec3.h"

#include <pthread.h>
#include <unistd.h>

#define MAXBUFDIM 1024 * 1024 //1mb
time_t NOW;

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
    for(int i = 0; i < CHUNK_HASHVEC_DIM; i++)
        c->chunkHashVec[i] = NULL;



    c->compressionTreshold = -1;
    c->sockfd = sockfd;
    c->state = -1;
    c->playerName = playerName;
    c->hostname = hostname;
    c->port = port;
    c->customPlayStateHandler = customHandler;

    char filename[RECVLOGFILENAME_MAXDIM];
    // sprintf(filename, "./log");
    struct tm *t = localtime(&NOW);  // Convert to local time structure
    strftime(filename, sizeof(filename), "./log-%d-%m_%H-%M-%S.txt", t);
    //printf("main log file: %s\n", filename);
    strcpy(c->socketRecvLogPath,filename);
    sendHandshakeAndLogin(c);
    return c;
}

void* readline_thread(void* arg) {
    client *c = (client *)arg; // Assuming client is passed in `arg`
    char buffer[256];
    int x, y, z;

    printf("Enter input (non-blocking readline):\n");
    while (1) {
        // Read input from the user
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Check if the input matches the expected command and extract the coordinates
            if (sscanf(buffer, "getBlockAtVec3 %d %d %d", &x, &y, &z) == 3) {
                // Call the function and print the block globalId
                TBlock *block = getBlockAtVec3(x, y, z, c);
                if (block != NULL) {
                    printf("Block at (%d, %d, %d) has globalId: %u\n", x, y, z, block->globalId);
                } else {
                    printf("Block not found at (%d, %d, %d)\n", x, y, z);
                }
            } else {
                printf("Invalid input. Use: getBlockAtVec3 x y z\n");
            }
            char exitCheck[20];  // Allocate a writable buffer
            if (sscanf(buffer, "%s", exitCheck) == 1 && strcmp(exitCheck, "exit12") == 0) {

                printf("Exiting");
                exit(12);
            }

            fflush(stdout); // Flush the output buffer
        } else {
            printf("Error reading input.\n");
            fflush(stdout); // Flush the output buffer
        }
    }

    return NULL;
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
        file_io_write_hex_to_file(c->socketRecvLogPath, p, recvb);

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

// Use strftime to format the time as month-day-hour-minute-second

int main(void) {
    NOW = time(NULL);  // Get the current time


    //  unsigned char buf[] = {0,0,0};
  //  file_io_write_buffer_to_file("\\\\wsl.localhost\\Ubuntu-22.04\\home\\arb\\mcbc6\\testFile.asd",buf , 1);

    char hostname[] = "ignacioFerrero.aternos.me";
    char username[] = "mcbc6";
    int port = 57188;
    char ver[] = "1.12.2";
    //printf("START\n");

    packetHandler_t customHandler[MAXPACKETID] = {[0X20] = (packetHandler_t) recvChunk};
    //packetInterpreter_t customInterpreter = internal_v1_12_2_defaultInterpreter;

    client *c = initializeAndConnectClient(username, hostname, port, ver, NULL);
    if(c == NULL)
        exit(-2);
    pthread_t readline_thread_id;

    // Create a thread for the readline function
    if (pthread_create(&readline_thread_id, NULL, readline_thread, c) != 0) {
        perror("Failed to create readline thread");
        return 1;
    }
    startListening(c);

    pthread_join(readline_thread_id, NULL);

    free(c);
    return 0;
}
