// Task 2: Thread Function with Arguments
// Objective: Learn to pass arguments to threads using void*
// Compile: g++ task2.cpp -o task2 -pthread

#include <iostream>
#include <pthread.h>

// Thread function receives a void* — we cast it back to int*
void *printNumber(void *arg)
{
    int num = *((int *)arg); // Cast void* back to int* then dereference
    std::cout << "Thread received number: " << num << std::endl;
    return nullptr;
}

int main()
{
    pthread_t tid[3];
    int numbers[3] = {10, 20, 30}; // Unique number for each thread

    // Create 3 threads, each gets a different number
    for (int i = 0; i < 3; i++)
    {
        // Cast int* to void* when passing the argument
        pthread_create(&tid[i], nullptr, printNumber, (void *)&numbers[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++)
    {
        pthread_join(tid[i], nullptr);
    }

    return 0;
}