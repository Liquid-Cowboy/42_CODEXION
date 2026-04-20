#!/bin/bash

ARGS=(
  12        # NB_COD
  5000    # BURNOUT
  1000    # COMPILE
  1000    # DEBUG
  1000    # REFACTOR
  1         # REQ
  1000    # COOLDOWN
  edf       # SCHD
)

FILES=(
	srcs/main.c
	srcs/parser.c
	srcs/init.c
	srcs/routines/coder_routine.c
	srcs/routines/monitor_routine.c
	srcs/routines/dongle_management.c
	srcs/threads/thread_cleanup.c
	srcs/threads/thread_start_1.c
	srcs/threads/thread_start_2.c
	srcs/enqueue.c
	srcs/memory_handling.c
	srcs/utils.c
)

clear
gcc -g "${FILES[@]}" -o prog
./prog "${ARGS[@]}"

#valgrind --leak-check=full --show-leak-kinds=all -s