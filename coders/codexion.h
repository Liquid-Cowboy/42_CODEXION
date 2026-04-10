#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h> // gettimeofday
#include <unistd.h> // write
#include <pthread.h>

typedef struct  quantum_compiler_s
{
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char* scheduler;
} quantum_compiler_t;


typedef struct coder_s
{
    pthread_t   coder;
    int         coder_i;
    int         burnout;
} coder_t;


typedef struct dongle_s
{
    pthread_mutex_t d_mutex;
    int             mutex_i;
} dongle_t;


void    check_valid_nb(int nb, char* arg, int arg_nb);
struct quantum_compiler_s parser(int argc, char** argv);