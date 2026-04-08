#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void*   routine(void* arg)
{
    (void)arg;
    pthread_mutex_lock(&mutex);
    printf("Locked thread\n");
    sleep(1);
    pthread_mutex_unlock(&mutex);
    return(NULL);
}

void*   routine2(void* arg)
{
    (void)arg;
    printf("Unlocked thread\n");
    sleep(1);
    return (NULL);
}

int main(void)
{
    int         t_num = 3;
    int         i;
    pthread_t   th[t_num];
    void*    (*f_ptr)(void*);

    f_ptr = &routine; // change between routine and routine2 to check differences
    pthread_mutex_init(&mutex, NULL);

    i = -1;
    while(++i < t_num)
    {
        pthread_create(&th[i], NULL, f_ptr, NULL);
    }
    i = -1;
        while(++i < t_num)
    {
        pthread_join(th[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    return (0);
}