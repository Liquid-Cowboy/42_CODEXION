#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void* routine(void* arg)
{
    int i;
    int sum;
    int *index = (int*)arg;
    int*    res;

    i = -1;
    sum = 0;
    res = (int*)malloc(sizeof(int));
    if(!res)
        return (NULL);
    while(++i < 5)
        sum += index[i];
    printf("Local sum: %d\n", sum);
    *res = sum;
    return ((void*)res);
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    pthread_t   th[2];
    int         i;
    int         x;
    int         total;
    int         *res;

    i = -1;
    total = 0;
    while(++i < 2)
    {
        x = i * 5;
        if(pthread_create(&th[i], NULL, &routine, (void *)&primes[x]) != 0)
            perror("Failed to create thread");
    }
    i = -1;
    while(++i < 2)
    {
        if(pthread_join(th[i], (void**)&res) != 0)
            perror("Failed to join thread");
        total += *res;
        free(res);
    }
    printf("Total: %d", total);
    return (0);
}