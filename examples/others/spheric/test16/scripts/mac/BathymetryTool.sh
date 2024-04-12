#!/bin/bash
# cp /Users/jg/git/DSPH/DesignSPHysics.git/dualsphysics/bin/BathymetryTool_linux64 /usr/local/games/
podman run -v /usr/local/games:/usr/local/games --rm dsph:latest /usr/local/games/BathymetryTool_linux64 "$@"
