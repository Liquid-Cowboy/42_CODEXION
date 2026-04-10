#include "codexion.h"

void    print_compiler(struct quantum_compiler_s compiler)
{
    printf(
    "======Compiler stats======\n"
    "Number of coders: %d\n"
    "Time to burnout: %d\n"
    "Time to compile: %d\n"
    "Time to debug: %d\n"
    "Time to refactor: %d\n"
    "Number of compiles required: %d\n"
    "Dongle cooldown: %d\n"
    "scheduler: %s\n",
    compiler.number_of_coders,
    compiler.time_to_burnout,
    compiler.time_to_compile,
    compiler.time_to_debug,
    compiler.time_to_refactor,
    compiler.number_of_compiles_required,
    compiler.dongle_cooldown,
    compiler.scheduler);
}

void*   monitoring(void *arg)
{
    (void)arg;
    return (NULL);
}

void*   comp_debug_refact(void* arg)
{
    (void)arg;
    return (NULL);
}

int main(int argc, char** argv)
{
    quantum_compiler_t  compiler;
    //coder_t*  coders;
    //pthread_t           monitor;
    //int                 i;
    //dongle_t            dongles[compiler.number_of_coders];

    compiler = parser(argc, argv);
    /*coders = (coder_t*) malloc(sizeof(coder_t) * (compiler.number_of_coders));
    while
    i = -1;
    while (i < compiler.number_of_coders + 1)
    {
        if(i == compiler.number_of_coders)
        {
            pthread_create(&monitor, NULL, &monitoring, NULL);
        }
        else
            pthread_create(&coders[i], NULL, &comp_debug_refact, NULL);
    }
    i = -1;

    while (i < compiler.number_of_coders + 1)
    {
        if(i == compiler.number_of_coders)
        {
            pthread_join(&monitor, NULL);
        }
        else
            pthread_join(&coders[i], NULL);
    }*/

    print_compiler(compiler);
    return (0);
}