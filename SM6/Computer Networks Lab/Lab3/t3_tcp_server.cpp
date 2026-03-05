#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;

#define PORT 8080
#define MAXLINE 1024

int main()
{
    int sockfd, newsockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAXLINE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sockfd, 10);

    // REQUIREMENT: Snapshot the server in listening stage here
    cout << "Server listening on port " << PORT << "..." << endl;

    while (true)
    {
        socklen_t len = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);

        if (newsockfd > 0)
        {
            // REQUIREMENT: Show Port number and PID
            cout << "\n[!] Client Connected!" << endl;
            cout << "Client Port: " << ntohs(cliaddr.sin_port) << endl;
            cout << "Process ID: " << getpid() << endl;

            // Receive filename
            memset(buffer, 0, MAXLINE);
            recv(newsockfd, buffer, MAXLINE, 0);
            cout << "Client requested file: " << buffer << endl;

            // Open and send file
            ifstream file(buffer, ios::binary);
            if (file)
            {
                while (file.read(buffer, MAXLINE) || file.gcount() > 0)
                {
                    send(newsockfd, buffer, file.gcount(), 0);
                }
                cout << "File sent successfully." << endl;
                file.close();
            }
            else
            {
                string msg = "Error: File not found";
                send(newsockfd, msg.c_str(), msg.length(), 0);
            }

            close(newsockfd);
            cout << "Connection closed. Ready for next client..." << endl;
        }
    }
    close(sockfd);
    return 0;
}