#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 

int fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t cond_fuel;

void*   fuel_car(void*)
{
    pthread_mutex_lock(&fuel_mutex);
    while (fuel < 40)
    {
        printf("Not enough fuel. Waiting...\n");
        pthread_cond_wait(&cond_fuel, &fuel_mutex);
    }
    fuel -= 40;
    printf("Car fuelled: -40 fuel\n");
    pthread_mutex_unlock(&fuel_mutex);
    return(NULL);
}

void*   fill_fuel(void*)
{
    int i;

    i = -1;
    while(++i < 5)
    {
        pthread_mutex_lock(&fuel_mutex);
        fuel += 15;
        printf("Filling fuel... Fuel: %d\n", fuel);
        if (fuel >= 40)
            pthread_cond_signal(&cond_fuel);

            /* cond_signal is equivalent to doing:
            - pthread_mutex_unlock(&fuel_mutex)
            - wait for signal on cond_fuel
            - pthread_mutex_lock(&fuel_mutex) (lock it again)
            */
        pthread_mutex_unlock(&fuel_mutex);
        sleep(1);
    }
    
    return (NULL);
}

int main(void)
{
    int         i;
    pthread_t   th[2];

    pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    i = -1;
    while (++i < 2)
    {
        if (i == 0)
        {
            if(pthread_create(&th[i], NULL, &fuel_car, NULL) != 0)
                perror("Failed to create thread");
        }
        else
            if(pthread_create(&th[i], NULL, &fill_fuel, NULL) != 0)
                perror("Failed to create thread");
    }
    i = -1;
    while (++i < 2)
    {
        if(pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
    pthread_cond_destroy(&cond_fuel);
    pthread_mutex_destroy(&fuel_mutex);
    return (0);
}