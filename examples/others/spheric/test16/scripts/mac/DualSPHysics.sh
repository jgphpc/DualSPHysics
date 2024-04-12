#!/bin/bash
podman run -v /usr/local/games:/usr/local/games --rm dsph:latest bash -c "LD_LIBRARY_PATH=/usr/local/games:$LD_LIBRARY_PATH /usr/local/games/DualSPHysics5.2_linux64 $@"
# dualsphysics
# podman run -v /usr/local/games:/usr/local/games --rm dsph:latest /usr/local/games/DualSPHysics5.2CPU_linux64 "$@"
