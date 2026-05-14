// Task 3: Print Thread IDs
// Objective: Identify threads and understand concurrency
// Demonstrates the effect of mutex on console output
// Compile: g++ task3.cpp -o task3 -pthread

#include <iostream>
#include <pthread.h>
#include <unistd.h> // for usleep()

// ─────────────────────────────────────────────
// TOGGLE THIS to switch between Part A and Part B
// Set USE_MUTEX to 0 → Part A: observe interleaved/jumbled output
// Set USE_MUTEX to 1 → Part B: observe clean output with mutex
// ─────────────────────────────────────────────
#define USE_MUTEX 0

pthread_mutex_t lock; // Mutex (only used when USE_MUTEX == 1)

// ── Part A: No mutex — outputs may jumble ──
void *printID_NoMutex(void *arg)
{
    // Multiple threads writing to cout at same time → interleaved output
    std::cout << "Thread ID: " << pthread_self() << " is running" << std::endl;
    return nullptr;
}

// ── Part B: With mutex — clean output ──
void *printID_WithMutex(void *arg)
{
    pthread_mutex_lock(&lock); // Lock: only one thread enters this section at a time
    std::cout << "Thread ID: " << pthread_self() << " is running" << std::endl;
    pthread_mutex_unlock(&lock); // Unlock: next thread can now proceed
    return nullptr;
}

int main()
{
    pthread_t tid[3];

#if USE_MUTEX
    // Part B — initialize mutex before use
    pthread_mutex_init(&lock, nullptr);
    std::cout << "=== Part B: With Mutex (Clean Output) ===" << std::endl;

    for (int i = 0; i < 3; i++)
        pthread_create(&tid[i], nullptr, printID_WithMutex, nullptr);

    for (int i = 0; i < 3; i++)
        pthread_join(tid[i], nullptr);

    pthread_mutex_destroy(&lock); // Clean up mutex when done
#else
    // Part A — no mutex, observe interleaving
    std::cout << "=== Part A: Without Mutex (May show interleaved output) ===" << std::endl;

    for (int i = 0; i < 3; i++)
        pthread_create(&tid[i], nullptr, printID_NoMutex, nullptr);

    for (int i = 0; i < 3; i++)
        pthread_join(tid[i], nullptr);
#endif

    return 0;
}