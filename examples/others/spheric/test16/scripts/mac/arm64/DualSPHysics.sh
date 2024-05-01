#!/bin/bash
/opt/homebrew/bin/wine64 /Users/jgp/git/DUALSPH/DualSPHysics/5.2.2/DualSPHysics_v5.2/bin/windows/DualSPHysics5.2CPU_win64.exe "$@"
# podman run -v /usr/local/games:/usr/local/games --rm dsph:latest bash -c "LD_LIBRARY_PATH=/usr/local/games:$LD_LIBRARY_PATH /usr/local//Users/jgp/git/DUALSPH/DualSPHysics/5.2.2/DualSPHysics_v5.2/bin/windows/DualSPHysics5.2_win64.exe $@"
