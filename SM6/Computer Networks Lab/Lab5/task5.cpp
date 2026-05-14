// Task 5: Thread-per-Client Echo Simulation
// Objective: Simulate a thread-per-client server (no sockets needed)
// Each thread represents a client connecting, doing work, then disconnecting
// A mutex ensures console output stays clean and readable
// Compile: g++ task5.cpp -o task5 -pthread

#include <iostream>
#include <pthread.h>
#include <unistd.h> // for sleep()

#define NUM_CLIENTS 3

pthread_mutex_t consoleLock; // Protects cout so messages don't interleave

// Simulates one client's session with the server
void *clientHandler(void *arg)
{
    int clientID = *((int *)arg);

    // ── Client connects ──
    pthread_mutex_lock(&consoleLock);
    std::cout << "Client " << clientID << " connected" << std::endl;
    pthread_mutex_unlock(&consoleLock);

    // ── Simulate the client doing some work (e.g., sending/receiving data) ──
    // sleep() here represents the time a real client would spend communicating
    sleep(1); // Each client "works" for 1 second

    // ── Client disconnects ──
    pthread_mutex_lock(&consoleLock);
    std::cout << "Client " << clientID << " disconnected" << std::endl;
    pthread_mutex_unlock(&consoleLock);

    return nullptr;
}

int main()
{
    pthread_t tid[NUM_CLIENTS];
    int clientIDs[NUM_CLIENTS];

    pthread_mutex_init(&consoleLock, nullptr);

    std::cout << "=== Thread-per-Client Server Simulation ===" << std::endl;
    std::cout << "Server started. Waiting for clients..." << std::endl
              << std::endl;

    // Simulate clients arriving one by one (slight delay between arrivals)
    for (int i = 0; i < NUM_CLIENTS; i++)
    {
        clientIDs[i] = i + 1; // Client IDs: 1, 2, 3
        pthread_create(&tid[i], nullptr, clientHandler, (void *)&clientIDs[i]);
        usleep(100000); // 100ms between client arrivals (realistic staggering)
    }

    // Wait for all clients to finish
    for (int i = 0; i < NUM_CLIENTS; i++)
        pthread_join(tid[i], nullptr);

    pthread_mutex_destroy(&consoleLock);

    std::cout << std::endl
              << "All clients handled. Server shutting down." << std::endl;

    return 0;
}