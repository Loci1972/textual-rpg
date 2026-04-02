#ifndef ENEMY_H
#define ENEMY_H

#include <vector>
#include <string>
#include <algorithm>

class Enemy{
    private:
        std::string name;
        int maxHp, xp, hp, level, xpToNextLevel, attack, defense, goldReward;
    public:
        //constructor
        Enemy(std::string PlayerName);
        //getters
        int getAttack() const { return attack; }
        int getMaxHp() const {return maxHp;}
        int getDefense() const { return defense; }
        int getHp() const { return hp; }
        int getGoldReward() const { return goldReward; }
        bool isAlive() const { return hp > 0; }
        std::string getName() const { return name; }
        //setters
        void takeDamage(int amount);
        void addXp(int amount);
        void levelUp();
        void fullHeal () {hp = maxHp;}
        //helpful functions
        void displayStats();
        std::string dialogue();
        void displayHealthBar();
};

#endif