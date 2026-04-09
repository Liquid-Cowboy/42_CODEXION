#include "codexion.h"

int main(int argc, char** argv)
{
    quantum_compiler_t compiler = parser(argc, argv);
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
    return (0);
}