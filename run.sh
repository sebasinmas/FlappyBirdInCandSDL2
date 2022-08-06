#!/bin/sh
# Let's make a quick gcc start for my SDL project

gcc main.c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm -o Flappy.exe

./Flappy.exe

