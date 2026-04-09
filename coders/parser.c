#include "codexion.h"

void    check_valid_nb(int nb, char* arg, int arg_nb);
struct quantum_compiler_s parser(int argc, char** argv);


struct quantum_compiler_s parser(int argc, char** argv)
{
    int args[7];
    int i;
    quantum_compiler_t compiler;

    if (argc != 9)
    {
        fprintf(stderr, "Invalid number of arguments: expected 8.");
        exit(1);
    }
    i = 0;
    while(++i < 8)
    {
        args[i] = atoi((const char*)argv[i]);
        check_valid_nb(args[i-1], argv[i], i + 2);
    }
    if (strcmp(argv[8], "fifo") != 0 && strcmp(argv[8], "edf") != 0)
    {
        fprintf(stderr, "Invalid argument. "
            "Only \"fifo\" or \"edf\" are considered.");
        exit(8);
    }
    compiler.number_of_coders = args[0];
    compiler.time_to_burnout = args[1];
    compiler.time_to_compile = args[2];
    compiler.time_to_debug = args[3];
    compiler.time_to_refactor = args[4];
    compiler.number_of_compiles_required = args[5];
    compiler.dongle_cooldown = args[6];
    compiler.scheduler = argv[8];
    return (compiler);
}

void    check_valid_nb(int nb, char* arg, int arg_nb)
{
    char    c;

    while(*arg)
        if (*arg == ' ' || (*arg >= 9 && *arg <= 13) ||
        *arg == '+' || *arg == '-')
            arg++;
        else
            break;

    c = *arg;
        
    if (nb == 0 && c != '0')
    {
        fprintf(stderr, "Invalid argument. "
            "Only valid integers are considered.");
            exit (arg_nb);
    }
}
