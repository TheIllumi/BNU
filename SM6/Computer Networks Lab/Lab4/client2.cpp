/*
 * ============================================================
 *  Lab 4 - Socket Programming: TCP Concurrent Server
 *  Course: Lab 209 - Computer Communications and Networks
 * ============================================================
 *
 *  FILE: client2.cpp
 *
 *  OBJECTIVE:
 *    Create a second TCP client that connects to the SAME
 *    concurrent server simultaneously as client1.
 *    This is CLIENT 2 — it will bind to local port 1235.
 *
 *    By running client1 and client2 at the same time, you
 *    will PROVE that the server handles both concurrently
 *    using the fork() mechanism.
 *
 *  HOW TO COMPILE:
 *    g++ client2.cpp -o client2
 *
 *  HOW TO RUN (open a NEW terminal, server and client1 already running):
 *    ./client2
 *
 *  EXPECTED OUTPUT (client 2 side):
 *    Client 2 connecting to server on port 8080...
 *    Connected to server!
 *    Message sent: Hello Server
 *    Reply from server (port 8080): Hello Client
 *
 * ============================================================
 *  NOTE FOR STUDENTS:
 *    Compare this file carefully with client1.cpp.
 *    The ONLY difference is the CLIENT_PORT value (1235 vs 1234).
 *    This shows how the same client logic can represent different
 *    clients just by binding to different local ports.
 * ============================================================
 */

// ----------------------------------------------------------
// SECTION 1: INCLUDE NECESSARY HEADERS
// ----------------------------------------------------------
// Copy the same includes you used in client1.cpp.

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
// Notice CLIENT_PORT is 1235 here — different from client1!

#define SERVER_PORT 8080      // Same server port as client1
#define CLIENT_PORT 1235      // This client's own local port (DIFFERENT!)
#define SERVER_IP "127.0.0.1" // Same server IP
#define BUFFER_SIZE 1024

// ----------------------------------------------------------
// SECTION 3: main() FUNCTION
// ----------------------------------------------------------
int main()
{

    // ------------------------------------------------------
    // STEP 1: DECLARE VARIABLES
    // ------------------------------------------------------
    // Same variables as client1.cpp.
    // Hint: sockfd, serverAddr, clientAddr, buffer[], message[]

    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    char message[] = "Hello Server";

    // ------------------------------------------------------
    // STEP 2: CREATE A TCP SOCKET
    // ------------------------------------------------------
    // Identical to client1 — socket(AF_INET, SOCK_STREAM, 0).

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // ------------------------------------------------------
    // STEP 3: BIND THE CLIENT TO ITS OWN LOCAL PORT (1235)
    // ------------------------------------------------------
    // This is what gives CLIENT 2 its unique identity.
    // The server will see port 1235 for this client.
    //
    //   a) Zero out clientAddr
    //   b) Set sin_family, sin_addr.s_addr, sin_port (use CLIENT_PORT)
    //   c) Call bind() and check for errors

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
    // Identical to client1 — point to the same server.

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);

    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0)
    {
        perror("Invalid address / Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Client 2 connecting to server on port %d...\n", SERVER_PORT);

    // ------------------------------------------------------
    // STEP 5: CONNECT TO THE SERVER
    // ------------------------------------------------------
    // Same connect() call as client1.
    // The server will fork() a NEW child process just for this client.

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
    // Use send() to send "Hello Server" to the server.

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
    // Use recv() to get the server's reply and print it.

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

    close(sockfd);

    return 0;
}

/*
 * ============================================================
 *  FINAL LAB CHALLENGE:
 *
 *  Run all three programs at the same time:
 *    Terminal 1: ./server
 *    Terminal 2: ./client1
 *    Terminal 3: ./client2
 *
 *  Observe the server terminal — you should see BOTH clients
 *  being handled. Take a screenshot for your lab report.
 *
 *  DISCUSSION QUESTIONS:
 *
 *  Q1. How many child processes does the server create in this run?
 *      What are their PIDs? (Add getpid() calls to find out!)
 *
 *  Q2. What would happen if the server used an iterative design
 *      instead of fork()? Would client2 connect while client1
 *      is still being served?
 *
 *  Q3. Modify the server to print its PID and the child's PID
 *      every time fork() is called. Use getpid() and the return
 *      value of fork().
 * ============================================================
 */
