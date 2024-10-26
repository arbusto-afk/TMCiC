#ifndef CROSSSOCKET_H
#define CROSSSOCKET_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")  // Link against the Winsock library on Windows
    typedef int socklen_t;  // Define socklen_t for compatibility on Windows
    #define CLOSE_SOCKET closesocket
#else
    #include <sys/socket.h>   // For socket functions on Linux
    #include <arpa/inet.h>    // For inet_pton and inet_ntop on Linux
    #include <netdb.h>        // For getaddrinfo and addrinfo on Linux
    #include <unistd.h>       // For close on Linux
    #include <errno.h>        // For error codes on Linux
    #define INVALID_SOCKET -1 // Define INVALID_SOCKET for compatibility on Linux
    #define SOCKET_ERROR   -1 // Define SOCKET_ERROR for compatibility on Linux
    #define CLOSE_SOCKET close
    typedef int SOCKET;       // Use int as SOCKET type on Linux
#endif


#define LOG_SOCKET_SEND 0
#include <stdint.h>

// Function to initialize the socket library (does nothing on Linux, initializes Winsock on Windows)
int simpleSocket_initialize();

// Function to create and connect a socket to the specified hostname and port
int simpleSocket_setSocket(const char* hostname, int port);

// Function to receive data from the specified socket into the provided buffer
int simpleSocket_receiveSocket(SOCKET sockfd, unsigned char* buffer, int bufdim);

// Function to send data through the specified socket
int simpleSocket_send(SOCKET sockfd, const uint8_t* data, int datalen);

// Function to close the socket
void simpleSocket_close(SOCKET sockfd);

// Function to clean up the socket library (does nothing on Linux, cleans up Winsock on Windows)
void simpleSocket_cleanup();

#endif // CROSSSOCKET_H
