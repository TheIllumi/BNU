// TCP Client - C++ Version

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char message[MAXLINE];

    struct sockaddr_in servaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY; // For local testing

    // Connect to server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (true)
    {
        memset(message, '\0', MAXLINE);

        cout << "Enter message: ";
        cin >> message;

        send(sockfd, message, strlen(message), 0);

        memset(buffer, '\0', MAXLINE);

        int n = recv(sockfd, buffer, MAXLINE, 0);

        if (n <= 0)
        {
            cout << "Server disconnected.\n";
            break;
        }

        buffer[n] = '\0';

        cout << "Server Replied: " << buffer << endl;

        if (strcmp(buffer, "EXIT") == 0)
            break;
    }

    close(sockfd);
    return 0;
}