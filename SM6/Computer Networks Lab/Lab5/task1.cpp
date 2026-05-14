#include <iostream>
#include <pthread.h>

void *printMessage(void *arg)
{
    std::cout << "Hello from thread!" << std::endl;
    return nullptr;
}

int main()
{
    pthread_t tid;
    pthread_create(&tid, nullptr, printMessage, nullptr);
    pthread_join(tid, nullptr);
    std::cout << "Hello from main thread" << std::endl;
    return 0;
}
