#ifndef TOOLS_H
#define TOOLS_H

#include <random>
#include <ctime>
#include "player.h"
#include "enemy.h"
#include <iostream>
#include <numeric>
#include <string>

int getNumber();
std::string getString();
int realDamage(const Enemy& enemy, const Player& player, const std::string& entity);
bool randomState ();
bool options(Player& player, Enemy& enemy, int& choice,bool& playerTurn,int& menueType);

#endif