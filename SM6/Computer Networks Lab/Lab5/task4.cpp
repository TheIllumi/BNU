// Task 4: Thread Synchronization
// Objective: Protect a shared resource (counter) using a mutex
// Without mutex: final value would be less than 5000 (race condition)
// With mutex:    final value is always exactly 5000
// Compile: g++ task4.cpp -o task4 -pthread

#include <iostream>
#include <pthread.h>

// ─────────────────────────────────────────────
// TOGGLE THIS to observe the race condition
// Set USE_MUTEX to 0 → incorrect/unpredictable counter (race condition)
// Set USE_MUTEX to 1 → correct counter = 5000 (mutex protected)
// ─────────────────────────────────────────────
#define USE_MUTEX 1

#define NUM_THREADS 5
#define INCREMENTS 1000

int counter = 0;      // Shared global counter
pthread_mutex_t lock; // Mutex to protect the counter

void *incrementCounter(void *arg)
{
    for (int i = 0; i < INCREMENTS; i++)
    {
#if USE_MUTEX
        pthread_mutex_lock(&lock);   // Acquire lock before touching counter
        counter++;                   // Critical section — only one thread at a time
        pthread_mutex_unlock(&lock); // Release lock so others can proceed
#else
        // No protection: multiple threads read/write counter simultaneously
        // This causes a race condition → lost updates → wrong final value
        counter++;
#endif
    }
    return nullptr;
}

int main()
{
#if USE_MUTEX
    std::cout << "Running WITH mutex (thread-safe)" << std::endl;
    pthread_mutex_init(&lock, nullptr);
#else
    std::cout << "Running WITHOUT mutex (race condition expected!)" << std::endl;
#endif

    pthread_t tid[NUM_THREADS];

    // Launch 5 threads, each incrementing the counter 1000 times
    // Expected total: 5 x 1000 = 5000
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&tid[i], nullptr, incrementCounter, nullptr);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(tid[i], nullptr);

#if USE_MUTEX
    pthread_mutex_destroy(&lock);
#endif

    std::cout << "Final counter value: " << counter << std::endl;
    std::cout << "Expected value:      " << NUM_THREADS * INCREMENTS << std::endl;

    return 0;
}