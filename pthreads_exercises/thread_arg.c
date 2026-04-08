#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg)
{
    int index = *(int*)arg;
    printf("%d ", index);
    return (NULL);
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    pthread_t th[10];
    int i;

    i = -1;
    while(++i < 10)
    {
       //printf("primes i: %d\n", primes[i]);
        if(pthread_create(&th[i], NULL, &routine, (void *)&primes[i]) != 0)
            perror("Failed to create thread");
    }
    i = -1;
    while(++i < 10)
    {
        if(pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
    return (0);
}