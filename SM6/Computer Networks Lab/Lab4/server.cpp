/*
 * ============================================================
 *  Lab 4 - Socket Programming: TCP Concurrent Server
 *  Course: Lab 209 - Computer Communications and Networks
 * ============================================================
 *
 *  FILE: server.cpp
 *
 *  OBJECTIVE:
 *    Build a TCP Concurrent Server using fork() that can handle
 *    multiple clients at the same time.
 *
 *  HOW TO COMPILE:
 *    g++ server.cpp -o server
 *
 *  HOW TO RUN:
 *    ./server
 *
 *  EXPECTED OUTPUT (server side):
 *    Server is running and waiting for connections on port 8080...
 *    New connection accepted! Client port: 1234
 *    New connection accepted! Client port: 1235
 *    [Child] Handling client on port 1234
 *    Message from client (port 1234): Hello Server
 *    [Child] Handling client on port 1235
 *    Message from client (port 1235): Hello Server
 * ============================================================
 */

// ----------------------------------------------------------
// SECTION 1: INCLUDE NECESSARY HEADERS
// ----------------------------------------------------------
// Hint: You will need headers for:
//   - Standard I/O              → <stdio.h>
//   - Standard library funcs    → <stdlib.h>
//   - UNIX process functions    → <unistd.h>
//   - String operations         → <string.h>
//   - Socket API                → <sys/socket.h>
//   - Internet address structs  → <netinet/in.h>
//   - Process/type definitions  → <sys/types.h>
//   - Waiting for child process → <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>

// ----------------------------------------------------------
// SECTION 2: DEFINE CONSTANTS
// ----------------------------------------------------------
// Define the port number the server will listen on.
// Define the maximum number of queued connections (backlog).

#define PORT 8080
#define BACKLOG 10
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
    //   - listenfd  : file descriptor for the listening socket
    //   - connfd    : file descriptor for each accepted connection
    //   - pid       : to store the return value of fork()
    //   - serverAddr: struct sockaddr_in to hold server address info
    //   - clientAddr: struct sockaddr_in to hold client address info
    //   - addrLen   : length of the client address struct
    //   - buffer[]  : char array to store incoming messages
    //   - message[] : char array for the reply message to client

    int listenfd, connfd;
    pid_t pid;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    char message[] = "Hello Client";

    // ------------------------------------------------------
    // STEP 2: CREATE THE LISTENING SOCKET
    // ------------------------------------------------------
    // Use socket() to create a TCP socket.
    // Hint: AF_INET = IPv4, SOCK_STREAM = TCP, protocol = 0
    // Check for errors: socket() returns -1 on failure.

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // ------------------------------------------------------
    // STEP 3: CONFIGURE SERVER ADDRESS STRUCTURE
    // ------------------------------------------------------
    // Zero out the serverAddr struct first (use memset or bzero).
    // Set:
    //   serverAddr.sin_family      = AF_INET       (IPv4)
    //   serverAddr.sin_addr.s_addr = INADDR_ANY    (accept from any IP)
    //   serverAddr.sin_port        = htons(PORT)   (convert port to network byte order)

    memset(&serverAddr, 0, sizeof(serverAddr)); // Zero out the structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // ------------------------------------------------------
    // STEP 4: BIND THE SOCKET TO THE ADDRESS AND PORT
    // ------------------------------------------------------
    // Use bind() to attach the socket to the address/port defined above.
    // Cast &serverAddr to (struct sockaddr *).
    // Check for errors: bind() returns -1 on failure.

    if (bind(listenfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Bind failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    // ------------------------------------------------------
    // STEP 5: START LISTENING FOR INCOMING CONNECTIONS
    // ------------------------------------------------------
    // Use listen() on listenfd with BACKLOG as the queue length.
    // Check for errors: listen() returns -1 on failure.

    if (listen(listenfd, BACKLOG) < 0)
    {
        perror("Listen failed");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("Server is running and waiting for connections on port %d...\n", PORT);

    // ------------------------------------------------------
    // STEP 6: ACCEPT CONNECTIONS IN AN INFINITE LOOP
    // ------------------------------------------------------
    // This is the heart of the concurrent server.
    // For each new client:
    //   a) Call accept() to get connfd (blocks until a client connects)
    //   b) Print the client's port number using ntohs(clientAddr.sin_port)
    //   c) Call fork() — the parent keeps accepting, the child handles the client

    for (;;)
    {

        // (a) Accept a new client connection
        // Hint: accept(listenfd, (struct sockaddr *)&clientAddr, &addrLen)

        connfd = accept(listenfd, (struct sockaddr *)&clientAddr, &addrLen);
        if (connfd < 0)
        {
            perror("Accept failed");
            continue; // Continue listening for other connections
        }

        // (b) Print which client just connected

        printf("New connection accepted! Client port: %d\n",
               ntohs(clientAddr.sin_port));

        // (c) Fork a child process to handle this client
        // Hint: pid = fork();

        pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            close(connfd);
            continue;
        }

        // --------------------------------------------------
        // STEP 7: CHILD PROCESS — Handle the client
        // --------------------------------------------------
        // If fork() returns 0, we are in the child process.
        // The child should:
        //   1. Close listenfd (child doesn't need to listen)
        //   2. Read the client's message using recv() into buffer
        //   3. Print: "[Child] Message from client (port XXXX): <message>"
        //   4. Send "Hello Client" back using send()
        //   5. Close connfd
        //   6. Exit the child process with exit(0)

        if (pid == 0)
        {

            printf("[Child] Handling client on port %d\n",
                   ntohs(clientAddr.sin_port));

            // 1. Close the listening socket in the child
            close(listenfd);

            // 2. Receive the message from the client
            int bytesReceived = recv(connfd, buffer, BUFFER_SIZE - 1, 0);
            if (bytesReceived < 0)
            {
                perror("Receive failed");
            }
            else
            {

                // 3. Null-terminate and print the received message
                buffer[bytesReceived] = '\0';
                printf("Message from client (port %d): %s\n",
                       ntohs(clientAddr.sin_port), buffer);
            }

            // 4. Send reply back to client
            if (send(connfd, message, strlen(message), 0) < 0)
            {
                perror("Send failed");
            }

            // 5. Close the connection socket
            close(connfd);

            // 6. Child exits — do NOT let it loop back to accept()
            exit(0);
        }

        // --------------------------------------------------
        // STEP 8: PARENT PROCESS — Close connfd and loop back
        // --------------------------------------------------
        // If fork() returns > 0, we are in the parent process.
        // The parent must close connfd (the child handles it).
        // Then the parent loops back to accept() the next client.
        // Hint: close(connfd);

        // The parent must close connfd (the child handles it).
        close(connfd);

    } // end infinite for loop

    return 0;
}

/*
 * ============================================================
 *  REVISION QUESTIONS (Answer in your lab report):
 *
 *  Q1. Why does the parent process close(connfd) after fork()?
 *
 *  Q2. Why does the child process close(listenfd) after fork()?
 *
 *  Q3. What happens if you forget exit(0) in the child process?
 *
 *  Q4. What does fork() return in the parent vs. child process?
 *
 *  Q5. How does the server know which port the client is using?
 * ============================================================
 */
