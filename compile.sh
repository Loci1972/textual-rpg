#!/bin/sh
clang++ -Wall -Wextra -std=c++11 -I./headers main.cpp src/player.cpp src/enemy.cpp src/tools.cpp src/item.cpp src/game.cpp -o rpg_game
./rpg_game
