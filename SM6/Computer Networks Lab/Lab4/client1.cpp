/*
 * ============================================================
 *  Lab 4 - Socket Programming: TCP Concurrent Server
 *  Course: Lab 209 - Computer Communications and Networks
 * ============================================================
 *
 *  FILE: client1.cpp
 *
 *  OBJECTIVE:
 *    Create a TCP client that connects to the concurrent server,
 *    sends a "Hello Server" message, and receives a reply.
 *    This is CLIENT 1 — it will bind to local port 1234.
 *
 *  HOW TO COMPILE:
 *    g++ client1.cpp -o client1
 *
 *  HOW TO RUN (in a separate terminal, AFTER starting the server):
 *    ./client1
 *
 *  EXPECTED OUTPUT (client 1 side):
 *    Client 1 connecting to server on port 8080...
 *    Connected to server!
 *    Message sent: Hello Server
 *    Reply from server (port 8080): Hello Client
 * ============================================================
 */

// ----------------------------------------------------------
// SECTION 1: INCLUDE NECESSARY HEADERS
// ----------------------------------------------------------
// You need the same headers as the server.
// Hint: stdio.h, stdlib.h, unistd.h, string.h,
//       sys/socket.h, netinet/in.h, sys/types.h, arpa/inet.h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

// ----------------------------------------------------------
// SECTION 2: DEFINE CONSTANTS
// ----------------------------------------------------------

#define SERVER_PORT 8080      // Port the server is listening on
#define CLIENT_PORT 1234      // This client's own local port
#define SERVER_IP "127.0.0.1" // Server IP — localhost for local testing
#define BUFFER_SIZE 1024

// ----------------------------------------------------------
// SECTION 3: main() FUNCTION
// ----------------------------------------------------------
int main()
{

    // ------------------------------------------------------
    // STEP 1: DECLARE VARIABLES
    // ------------------------------------------------------
    // You will need:
    //   - sockfd     : file descriptor for this client's socket
    //   - serverAddr : struct sockaddr_in for the server's address
    //   - clientAddr : struct sockaddr_in for this client's own address
    //   - buffer[]   : to store the server's reply
    //   - message[]  : the message to send to the server

    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    char message[] = "Hello Server";

    // ------------------------------------------------------
    // STEP 2: CREATE A TCP SOCKET
    // ------------------------------------------------------
    // Same as the server — use socket(AF_INET, SOCK_STREAM, 0).
    // Check for errors.

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // ------------------------------------------------------
    // STEP 3: BIND THE CLIENT TO ITS OWN LOCAL PORT (1234)
    // ------------------------------------------------------
    // This is what gives CLIENT 1 its identity (port 1234).
    // The server will see this port number when we connect.
    //
    // Steps:
    //   a) Zero out clientAddr with memset
    //   b) Set clientAddr.sin_family      = AF_INET
    //      Set clientAddr.sin_addr.s_addr = INADDR_ANY
    //      Set clientAddr.sin_port        = htons(CLIENT_PORT)
    //   c) Call bind() with the clientAddr
    //   d) Check for errors

    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = INADDR_ANY;
    clientAddr.sin_port = htons(CLIENT_PORT);

    if (bind(sockfd, (struct sockaddr *)&clientAddr, sizeof(clientAddr)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // ------------------------------------------------------
    // STEP 4: CONFIGURE THE SERVER ADDRESS STRUCTURE
    // ------------------------------------------------------
    // Tell the socket WHERE to connect (the server's IP and port).
    //
    //   a) Zero out serverAddr with memset
    //   b) Set serverAddr.sin_family = AF_INET
    //   c) Set serverAddr.sin_port   = htons(SERVER_PORT)
    //   d) Convert SERVER_IP string to binary using inet_pton():
    //        inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr)

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0)
    {
        perror("Invalid address / Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Client 1 connecting to server on port %d...\n", SERVER_PORT);

    // ------------------------------------------------------
    // STEP 5: CONNECT TO THE SERVER
    // ------------------------------------------------------
    // Use connect() to initiate the TCP connection.
    // Hint: connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr))
    // Check for errors: connect() returns -1 on failure.

    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Connected to server!\n");

    // ------------------------------------------------------
    // STEP 6: SEND A MESSAGE TO THE SERVER
    // ------------------------------------------------------
    // Use send() to transmit the message string to the server.
    // Hint: send(sockfd, message, strlen(message), 0)
    // Check for errors.

    if (send(sockfd, message, strlen(message), 0) < 0)
    {
        perror("Send failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Message sent: %s\n", message);

    // ------------------------------------------------------
    // STEP 7: RECEIVE THE SERVER'S REPLY
    // ------------------------------------------------------
    // Use recv() to read the server's response into buffer.
    // Null-terminate the buffer, then print it.
    // Hint: recv(sockfd, buffer, BUFFER_SIZE, 0)

    int bytesReceived = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
    if (bytesReceived < 0)
    {
        perror("Receive failed");
    }
    else
    {
        buffer[bytesReceived] = '\0';
        printf("Reply from server (port %d): %s\n", SERVER_PORT, buffer);
    }

    // ------------------------------------------------------
    // STEP 8: CLOSE THE SOCKET
    // ------------------------------------------------------
    // Always close the socket when done.
    close(sockfd);

    return 0;
}

/*
 * ============================================================
 *  REVISION QUESTIONS (Answer in your lab report):
 *
 *  Q1. Why does a client need to bind() to a port?
 *      What would happen if we skipped the bind() step?
 *
 *  Q2. What is the purpose of inet_pton() here?
 *
 *  Q3. What is the difference between send() and write()?
 *
 *  Q4. Run client1 and client2 at the same time. Does the
 *      server respond to both? How does it manage that?
 * ============================================================
 */
