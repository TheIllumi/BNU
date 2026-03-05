// TCP Server - C++ Version (Task 2 with Acknowledgements)

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

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // --- ADDED: Fix for "Address already in use" ---
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 10);

    cout << "Server running on port " << PORT << "..." << endl;

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
        if (pid == 0) // Child process
        {
            close(sockfd);
            memset(buffer, '\0', MAXLINE);

            int n = recv(newsockfd, buffer, MAXLINE, 0);
            if (n > 0)
            {
                // Add this line to see the encrypted data from the client
                cout << "Server received (Encrypted): " << buffer << endl;

                // --- Decryption Logic ---
                for (int i = 0; i < n; i++)
                {
                    if (buffer[i] >= 'a' + 3 && buffer[i] <= 'z' + 3)
                        buffer[i] = buffer[i] - 3;
                    else if (buffer[i] >= 'A' + 2 && buffer[i] <= 'Z' + 2)
                        buffer[i] = buffer[i] - 2;
                    else if (buffer[i] >= '0' + 1 && buffer[i] <= '9' + 1)
                        buffer[i] = buffer[i] - 1;
                }

                cout << "Server Decrypted: " << buffer << endl;
                send(newsockfd, buffer, n, 0);
            }
            close(newsockfd);
            exit(0);
        }
        else // Parent process
        {
            close(newsockfd);
        }
    }

    close(sockfd);
    return 0;
}