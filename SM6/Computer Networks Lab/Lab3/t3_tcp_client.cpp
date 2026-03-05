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
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];
    string filename;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Connect failed");
        return 1;
    }

    cout << "Enter filename to request from server: ";
    cin >> filename;

    // Send filename to server
    send(sockfd, filename.c_str(), filename.length(), 0);

    // Receive file content
    ofstream outFile("received_" + filename, ios::binary);
    int n;
    while ((n = recv(sockfd, buffer, MAXLINE, 0)) > 0)
    {
        outFile.write(buffer, n);
    }

    cout << "File received and connection closed." << endl;
    outFile.close();
    close(sockfd);

    return 0;
}