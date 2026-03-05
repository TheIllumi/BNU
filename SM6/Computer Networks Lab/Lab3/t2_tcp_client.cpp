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
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    // --- TASK 2: Read from file and Encrypt ---
    ifstream inputFile("fileData.txt");
    if (!inputFile)
    {
        perror("Could not open fileData.txt");
        close(sockfd);
        return 1;
    }

    string fileWord, encryptedData = "";
    // Read file content word by word
    while (inputFile >> fileWord)
    {
        for (char &c : fileWord)
        {
            if (islower(c))
                c = c + 3; // Lowercase +3
            else if (isupper(c))
                c = c + 2; // Uppercase +2
            else if (isdigit(c))
                c = c + 1; // Numeric +1
        }
        encryptedData += fileWord + " ";
    }
    inputFile.close();

    // FIXED: Use encryptedData instead of 'content'
    cout << "Client sending (Encrypted): " << encryptedData << endl;

    // Send encrypted data to server
    send(sockfd, encryptedData.c_str(), encryptedData.length(), 0);
    cout << "Encrypted data sent to server.\n";

    // Receive decrypted data back from server
    memset(buffer, '\0', MAXLINE);
    int n = recv(sockfd, buffer, MAXLINE, 0);
    if (n > 0)
    {
        cout << "Decrypted data from Server: " << buffer << endl; // Display result
    }

    close(sockfd);
    return 0;
}