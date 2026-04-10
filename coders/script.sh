#!/bin/bash

ARGS=(
  12        # NB_COD
  500000    # BURNOUT
  100000    # COMPILE
  100000    # DEBUG
  100000    # REFACTOR
  1         # REQ
  100000    # COOLDOWN
  sedf       # SCHD
)

./prog "${ARGS[@]}"