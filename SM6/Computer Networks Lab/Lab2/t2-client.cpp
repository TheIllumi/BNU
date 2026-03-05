#include <iostream>
#include <cstring>
#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    typedef int SOCKET;
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket close
#endif

using namespace std;

constexpr const char* SERVER_IP = "127.0.0.1";
constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

int main() {
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    SOCKET client_socket;
    sockaddr_in server_addr{};
    char buffer[BUFFER_SIZE];
    string roll;

    cout << "Enter Roll Number: ";
    getline(cin, roll);

    // Create UDP socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == INVALID_SOCKET) {
        cerr << "Socket creation failed\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Send roll number
    int sent_len = sendto(client_socket,
                          roll.c_str(),
                          (int)roll.length(),
                          0,
                          reinterpret_cast<sockaddr*>(&server_addr),
                          sizeof(server_addr));

    if (sent_len == SOCKET_ERROR) {
        cerr << "Send failed\n";
    } else {
        cout << "Roll number sent to server. Waiting for response..." << endl;
        
        int addr_len = sizeof(server_addr);
        int recv_len = recvfrom(client_socket,
                                buffer,
                                BUFFER_SIZE - 1,
                                0,
                                reinterpret_cast<sockaddr*>(&server_addr),
                                &addr_len);

        if (recv_len != SOCKET_ERROR) {
            buffer[recv_len] = '\0';
            cout << "Server Response (Name): " << buffer << endl;
        } else {
            cerr << "Receive failed\n";
        }
    }

    closesocket(client_socket);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
