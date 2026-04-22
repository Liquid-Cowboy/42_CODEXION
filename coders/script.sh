#!/bin/bash

ARGS=(
  12        # NB_COD
  800    # BURNOUT
  100    # COMPILE
  100    # DEBUG
  100    # REFACTOR
  3         # REQ
  100    # COOLDOWN
  edf       # SCHD
)

FILES=(
	srcs/main.c
	srcs/helpers/parser.c
	srcs/helpers/init.c
	srcs/routines/coder_routine.c
	srcs/routines/monitor_routine.c
	srcs/routines/dongle_management.c
	srcs/threads/thread_cleanup.c
	srcs/threads/thread_start_1.c
	srcs/threads/thread_start_2.c
	srcs/helpers/enqueue.c
	srcs/helpers/memory_handling.c
	srcs/helpers/utils.c
)

clear
gcc -g  "${FILES[@]}" -o prog
./prog "${ARGS[@]}"

#valgrind --leak-check=full --show-leak-kinds=all -s