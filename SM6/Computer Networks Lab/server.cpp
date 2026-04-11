// UDP Server (server.cpp)

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

int main() {
    int server_socket;
    sockaddr_in server_addr{}, client_addr{};
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket < 0) {
        cerr << "Socket creation failed\n";
        return EXIT_FAILURE;
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket,
             reinterpret_cast<sockaddr*>(&server_addr),
             sizeof(server_addr)) < 0) {
        cerr << "Bind failed\n";
        close(server_socket);
        return EXIT_FAILURE;
    }

    cout << "UDP Server is listening on port " << PORT << "...\n";

    // Receive data
    ssize_t recv_len = recvfrom(server_socket,
                                buffer,
                                BUFFER_SIZE - 1,
                                0,
                                reinterpret_cast<sockaddr*>(&client_addr),
                                &addr_len);

    if (recv_len < 0) {
        cerr << "Receive failed\n";
    } else {
        buffer[recv_len] = '\0';
        cout << "Received message: " << buffer << endl;
    }

    close(server_socket);
    return 0;
}