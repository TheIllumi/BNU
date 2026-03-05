#include <iostream>
#include <cstring>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
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

constexpr int PORT = 8080;
constexpr int BUFFER_SIZE = 1024;

int main()
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cerr << "WSAStartup failed\n";
        return 1;
    }
#endif

    SOCKET server_socket;
    sockaddr_in server_addr{}, client_addr{};
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Create UDP socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == INVALID_SOCKET)
    {
        cerr << "Socket creation failed\n";
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    // Setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_socket, reinterpret_cast<sockaddr *>(&server_addr), sizeof(server_addr)) == SOCKET_ERROR)
    {
        cerr << "Bind failed\n";
        closesocket(server_socket);
#ifdef _WIN32
        WSACleanup();
#endif
        return 1;
    }

    cout << "UDP Server is listening on port " << PORT << "...\n";

    while (true)
    {
        int recv_len = recvfrom(server_socket,
                                buffer,
                                BUFFER_SIZE - 1,
                                0,
                                reinterpret_cast<sockaddr *>(&client_addr),
                                &addr_len);

        if (recv_len == SOCKET_ERROR)
        {
            cerr << "Receive failed\n";
            continue;
        }

        buffer[recv_len] = '\0';
        string roll = buffer;

        // Remove whitespace
        roll.erase(0, roll.find_first_not_of(" \n\r\t"));
        roll.erase(roll.find_last_not_of(" \n\r\t") + 1);

        cout << "Received roll number: [" << roll << "]" << endl;

        string reply;
        if (roll == "F2023-009")
            reply = "Saad Mughal";
        else if (roll == "F2023-956")
            reply = "Khadijah Zahoor";
        else if (roll == "F2023-630")
            reply = "Sheikh Muhammad Ibrahim";
        else if (roll == "F2023-744")
            reply = "Sara Haider";
        else if (roll == "F2023-026")
            reply = "Ramsha Naveed";
        else if (roll == "F2023-551")
            reply = "Muhammad Ismail Rana";
        else
            reply = "Roll number not found";

        sendto(server_socket,
               reply.c_str(),
               (int)reply.length(),
               0,
               reinterpret_cast<sockaddr *>(&client_addr),
               addr_len);
    }

    closesocket(server_socket);
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
