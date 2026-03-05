
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

constexpr const char* SERVER_IP = "127.0.0.1";
constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

int main() {
    int client_socket;
    sockaddr_in server_addr{};
    string message;

    cout << "Enter message to send to server: ";
    getline(cin, message);

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        cerr << "Socket creation failed\n";
        return EXIT_FAILURE;
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send message
    ssize_t sent_len = sendto(client_socket,
                              message.c_str(),
                              message.length(),
                              0,
                              reinterpret_cast<sockaddr*>(&server_addr),
                              sizeof(server_addr));

    if (sent_len < 0) {
        cerr << "Send failed\n";
    } else {
        cout << "Message sent to server: " << message << endl;
    }

    close(client_socket);
    return 0;
}
