#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 

int fuel = 0;
pthread_mutex_t fuel_mutex;
pthread_cond_t cond_fuel;

void*   fuel_car(void* car_nb)
{
    int nb = *(int*)car_nb;
    pthread_mutex_lock(&fuel_mutex);
    while (fuel < 40)
    {
        printf("Not enough fuel to fill car %d. Waiting...\n", nb);
        pthread_cond_wait(&cond_fuel, &fuel_mutex);
    }
    fuel -= 40;
    printf("Car %d fuelled: -40 fuel\n", nb);
    pthread_mutex_unlock(&fuel_mutex);
    return(NULL);
}

void*   fill_fuel(void* null)
{
    int i;

    i = -1;
    while(++i < 5)
    {
        pthread_mutex_lock(&fuel_mutex);
        fuel += 60;
        printf("Filling fuel... Fuel: %d\n", fuel);
        if (fuel >= 40)
            pthread_cond_broadcast(&cond_fuel);

            /* cond_broadcast is similar to
            cond_signal but it awakens all
            the threads at once, not only
            one of them
            */
        pthread_mutex_unlock(&fuel_mutex);
        sleep(1);
    }
    
    return (NULL);
}

int main(void)
{
    int         i;
    pthread_t   th[5];
    int         ids[4];

    pthread_mutex_init(&fuel_mutex, NULL);
    pthread_cond_init(&cond_fuel, NULL);
    i = -1;
    while (++i < 5)
    {
        if (i < 4)
        {
            ids[i] = i;
            if(pthread_create(&th[i], NULL, &fuel_car, (void*)&ids[i]) != 0)
                perror("Failed to create thread");
        }
        else
            if(pthread_create(&th[i], NULL, &fill_fuel, NULL) != 0)
                perror("Failed to create thread");
    }
    i = -1;
    while (++i < 5)
    {
        if(pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
    pthread_cond_destroy(&cond_fuel);
    pthread_mutex_destroy(&fuel_mutex);
    return (0);
}