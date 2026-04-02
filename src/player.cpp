#include "player.h"
#include <iostream>
#include <string>
#include <numeric>
#include "enemy.h"
#include <fstream> // Nécessaire pour la gestion des fichiers

Player::Player(std::string playerName){
    name = playerName;
    level = 1;
    xp = 0;
    xpToNextLevel = 50;
    maxHp = 120;
    hp = maxHp;
    attack = 10;
    defense = 5;
    gold = 50;
}

void Player::levelUp(){
    std::cout << "Level increased !! " << std::endl;
    level += 1;
    maxHp += 1+(level/2);
    hp = maxHp;
    displayStats();
    attack += 2*((level/10) + 1);
    defense += 2;
}

void Player::addXp(int amount){
    xp += amount;
    while (xp >= xpToNextLevel) {
        xp -= xpToNextLevel;
        levelUp();
    }
}

void Player::heal(int amount){
    if (amount + hp > maxHp){
        hp = maxHp;
    }else {
        hp += amount;
    }
}

void Player::takeDamage(int amount){
    int actualDamage = amount - defense;
    if (actualDamage > 0){
        hp = std::max(0,hp - actualDamage);
    }
}

void Player::displayHealthBar(){
    int barLength = 25;
    int filledLength = (hp * barLength) / maxHp;
    if (filledLength < 0 && hp > 0) filledLength += 1;
    std::cout << name << " [";
    for (int i = 0 ; i < barLength; i++){
        
        std::cout << (i < filledLength ? "█" : "░");

    }
    std::cout << "] " << hp << "/" << maxHp << "\n" << dialogue() << std::endl;
}

void Player::displayStats(){
    std::cout<<"===STATS===\n" << "Player: " << name 
    << "\nLevel : " << level <<"\nAttack : " << attack 
    << "\nDefense : " << defense 
    << std::endl;
    displayHealthBar();
    dialogue();
}

bool Player::runAway(bool state,bool isTakingDamage,Enemy enemy){
    if (!state) std::cout << "you flee but you broke your leg\n";
    else if (state) std::cout << "you fled with SUCCESS !!! " << std::endl;
    if (isTakingDamage && !state) {
        std::cout << ", -" << enemy.getAttack() - defense <<"\n";
        takeDamage(enemy.getAttack());
    }
    return state;
}



std::string Player::dialogue() { 
    int hp_percent = (100 *hp)/maxHp;
    if (hp_percent >= 90){
        return "Ez pls" ;
    }else if (hp_percent >= 60){
        return "still alive barelly..." ;
    }else if(hp_percent >= 30){
        return "why do i hear boss music ?" ; 
    }else if (hp_percent > 0){
        return "mom... pick me up I'm scrared :( ";
    }else{
        return "DEAD 💀 !!!";
    }
}

void Player::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << name << "\n"
             << level << "\n"
             << xp << "\n"
             << maxHp << "\n"
             << hp << "\n"
             << attack << "\n"
             << defense << "\n"
             << gold << "\n";
        file.close();
        std::cout << "Partie sauvegardée avec succès !\n";
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier de sauvegarde.\n";
    }
}

bool Player::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::getline(file, name);
        file >> level >> xp >> maxHp >> hp >> attack >> defense >> gold;
        file.close();
        return true;
    }
    return false; // Le fichier n'existe pas encore
}