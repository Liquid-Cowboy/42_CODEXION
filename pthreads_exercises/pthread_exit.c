#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void*   routine()
{
    int value = (rand() % 6) + 1;
    int* result = (int*)malloc(sizeof(int));
    *result = value;
    printf("\t...rolling...\n");
    pthread_exit((void*) result);
    
}

int main(int argc, char** argv)
{
    pthread_t   th[8];
    int*        res[8];
    int         i;
    int         sum;

    (void)argc;
    (void)argv;

    srand(time(NULL));

    i = -1;
    sum = 0;
    while(++i < 8)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            return (i + 1);
        printf("Rolling dice %d...\n", i + 1);
    }
    pthread_exit(0);
    /*
    using pthread_exit() instead of return() here
    ensures the threads end up being executed and not
    just started
    */

    i = -1;
    while(++i < 8)
    {
        if (pthread_join(th[i], (void**)&res[i]) != 0)
            return (i + 1);
        printf("Roll %d finished\n", i + 1);
    }
    i = -1;
    printf("\n");
    while(++i < 8)
    {
        printf("Dice %d rolled %d\n", i+1, *res[i]);
        sum += *res[i];
    }
    printf("\nPlayer plays %d", sum);

    i = -1;
    while(++i < 8)
    {
        free(res[i]);
    }
    return 0;
}