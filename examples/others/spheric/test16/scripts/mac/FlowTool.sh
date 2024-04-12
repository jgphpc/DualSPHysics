#!/bin/bash
podman run -v /usr/local/games:/usr/local/games --rm dsph:latest /usr/local/games/FlowTool_linux64 "$@"
