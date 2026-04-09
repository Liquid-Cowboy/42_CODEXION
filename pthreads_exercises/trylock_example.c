#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t stove_mutex[4];
int stove_fuel[4] = { 100, 100, 100, 100};

void    *routine(void* args) {
    int i;

    i = -1;
    while(++i < 4)
    {
        if(pthread_mutex_trylock(&stove_mutex[i]) == 0)
        {
            int fuel_needed = (rand() % 40) + 1;
            if (stove_fuel[i] - fuel_needed < 0)
                printf("Not enough fuel in stove %d. Leaving...\n", (i + 1));
            else
            {
                stove_fuel[i] -= fuel_needed;
                usleep(500000);
                printf("Fueled: %d \nFuel left in stove %d: %d\n", fuel_needed, (i + 1),stove_fuel[i]);
            }
            pthread_mutex_unlock(&stove_mutex[i]);
            break;
        }
        else if (i == 3)
        {
            printf("No stove available yet. Waiting...\n");
            usleep(500000);
            i = -1;
        }
    }
    return (NULL);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    pthread_t   th[10];
    int         i;

    i = -1;
    while(++i < 4)
        pthread_mutex_init(&stove_mutex[i], NULL);
    i = -1;
    while(++i < 10)
    {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
            perror("Failed to create thread");
    }
    i = -1;
    while(++i < 10)
    {
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
    i = -1;
    while(++i < 4)
        pthread_mutex_destroy(&stove_mutex[i]);
    return (0);
}