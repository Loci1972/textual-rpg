#!/bin/bash
clang++ -Wall -Wextra -std=c++11 -I./headers main.cpp src/player.cpp src/enemy.cpp src/tools.cpp -o rpg_game
./rpg_game