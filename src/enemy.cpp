#include "enemy.h"
#include <iostream>
#include <string>
#include <numeric>

Enemy::Enemy(std::string playerName){
    name = playerName;
    level = 1;
    xp = 0;
    xpToNextLevel = 50;
    maxHp = 120;
    hp = maxHp;
    attack = 10;
    defense = 5;
    goldReward = 50*level ;
}


void Enemy::takeDamage(int amount){
    int actualDamage = amount - defense;
    if (actualDamage > 0){
        hp = std::max(0,hp - actualDamage);
    }
}

void Enemy::displayHealthBar(){
    int barLength = 25;
    int filledLength = (hp * barLength) / maxHp;
    if (filledLength < 0 && hp > 0) filledLength += 1;
    std::cout << name << " [";
    for (int i = 0 ; i < barLength; i++){
        
        std::cout << (i < filledLength ? "█" : "░");

    }
    std::cout << "] " << hp << "/" << maxHp << "\n" << dialogue() << std::endl;
}

void Enemy::displayStats(){
    std::cout<<"===STATS===\n" << "Enemy: " << name 
    << "\nLevel : " << level <<"\nAttack : " << attack 
    << "\nDefense : " << defense 
    << std::endl;
    displayHealthBar();
    dialogue();
}

std::string Enemy::dialogue() { 
    int hp_percent = (100 *hp)/maxHp;
    if (hp_percent >= 90){
        return "I will kill you !" ;
    }else if (hp_percent >= 60){
        return "How can you do this !?" ;
    }else if(hp_percent >= 30){
        return "am I actually dying ?"; 
    }else if (hp_percent > 0){
        return "...";
    }else{
        return "DEAD 💀 !!!";
    }
}