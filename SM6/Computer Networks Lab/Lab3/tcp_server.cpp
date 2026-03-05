// TCP Server - C++ Version

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

using namespace std;

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd;
    char buffer[MAXLINE];

    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen
    listen(sockfd, 10);

    cout << "Server running on port " << PORT << "...\n";

    while (true)
    {
        socklen_t length = sizeof(cliaddr);

        int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &length);
        if (newsockfd < 0)
        {
            perror("Accept failed");
            continue;
        }

        int pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Child process
            close(sockfd);

            int port = ntohs(cliaddr.sin_port);
            string ip = inet_ntoa(cliaddr.sin_addr);

            while (true)
            {
                memset(buffer, '\0', MAXLINE);

                int n = recv(newsockfd, buffer, MAXLINE, 0);
                if (n <= 0)
                    break;

                buffer[n] = '\0';

                cout << "Client with Port " << port
                     << " message: " << buffer << endl;

                if (strcmp(buffer, "EXIT") == 0)
                {
                    send(newsockfd, "EXIT", strlen("EXIT"), 0);
                    break;
                }

                memset(buffer, '\0', MAXLINE);

                sprintf(buffer,
                        "Client with Port %d and IP Address %s",
                        port, ip.c_str());

                send(newsockfd, buffer, strlen(buffer), 0);
            }

            close(newsockfd);
            exit(0);
        }
        else
        {
            // Parent process
            close(newsockfd);
        }
    }

    close(sockfd);
    return 0;
}