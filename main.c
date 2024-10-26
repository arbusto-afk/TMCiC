#include <stdio.h>


#include "Defs/ClientDef.h"
#include "crossSocket/crossSocket.h"
#include "Parser/parser.h"
#include "Versions/v1_12_2/defaultGeneralHandler.h"

#include "file_io/file_io.h"
//#include ""
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
    //TODO map version to index in defaultGeneralHandlerArr;
    if(1) {
     //   c->packetInterpreter = internal_parser_defaultInterpreter;
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
    strftime(filename, sizeof(filename), "./%d-%m_%H-%M-%S_log_Recv.txt", t);
    //printf("main log file: %s\n", filename);
    strcpy(c->socketRecvLogPath,filename);
    char packetLogFilename[PACKETSLOGFILENAME_MAXDIM];
    strftime(packetLogFilename, sizeof(packetLogFilename), "./%d-%m_%H-%M-%S_log_Handler.txt", t);
    strcpy(c->packetInterpretingLogPath, packetLogFilename);

    char packetParserLogFileName[PACKETSPARSERLOGFILENAME_MAXDIM];
    strftime(packetParserLogFileName, sizeof(packetParserLogFileName), "./%d-%m_%H-%M-%S_log_parser.txt", t);
    strcpy(
            c->packetParserLogPath, packetParserLogFileName
            );
    sendHandshakeAndLogin(c);
    return c;
}

void clearInputBuffer() {
    int c;
    // Read until a newline is found or EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

void* readline_thread(void* arg) {
    client *c = (client *)arg; // Assuming client is passed in `arg`
    char buffer[1024] = {0};
    char lastbuffer[1024] = {0};

    printf("Enter input (non-blocking readline):\n");
    while (1) {
        // Read input from the user
        if (fgets(buffer, sizeof(buffer), stdin)) {
            // Remove the newline character from buffer, if present
            buffer[strcspn(buffer, "\n")] = '\0';

            // Check for command length to ensure it fits buffer size
            if (strlen(buffer) >= sizeof(buffer) - 1) {
                printf("Input was too long! Unread characters exist.\n");
                clearInputBuffer(); // Clear the unread characters
            }
            else
            {
                int match = 0;
                int x, y, z;

                // Check for the "l" command to reuse the last input
                if (strcmp(buffer, "l") == 0) {
                    if (strlen(lastbuffer) == 0) {
                        printf("No previous command to reuse.\n");
                    } else {
                        match = 3;  // Reuse last command
                        strcpy(buffer, lastbuffer);  // Load last command into buffer
                    }
                }

                // Parse command for getBlockAtVec3 coordinates
                if (sscanf(buffer, "getBlockAtVec3 %d %d %d", &x, &y, &z) == 3) {
                    match = 1;
                }

                // Check for exit command
                if (strcmp(buffer, "exit") == 0) {
                    match = 2;
                }

                // Switch based on matched command
                switch (match) {
                    case 1:
                        // Handle getBlockAtVec3 command
                        TBlock *block = getBlockAtVec3(x, y, z, c);
                        if (block != NULL) {
                            printf("Block at (%d, %d, %d) has globalId: %u\n", x, y, z, block->globalId);
                        } else {
                            printf("Block not found at (%d, %d, %d)\n", x, y, z);
                        }
                        // Save current command as last command
                        strcpy(lastbuffer, buffer);
                        break;
                    case 2:
                        // Handle exit command
                        printf("Exiting\n");
                        exit(12);
                        break;
                    case 3:
                        // Confirm reuse of last command
                        printf("Reused last command: %s\n", buffer);
                        break;
                    default:
                        // Unknown command
                        printf("Unknown input: %s\n", buffer);
                        strcpy(lastbuffer,buffer);
                }
                fflush(stdout); // Flush the output buffer
            }

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
            fflush(stdout);
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
    //packetInterpreter_t customInterpreter = internal_parser_defaultInterpreter;

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
