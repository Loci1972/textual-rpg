#include <random>
#include <ctime>
#include "tools.h"
#include "player.h"
#include "enemy.h"
#include <iostream>
#include <numeric>
#include <string>

int getNumber(){
    int a;
    while (true){
        if (std::cin >> a) {
            std::cin.clear();
            break;
        }else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid Input retry :( \n";
        }
    }
    return a;
}

std::string getString(){
    std::string text;
    while(text != "" || text != " "){
        std::getline(std::cin, text);
        break;
    }
    return text;
}

int realDamage(const Enemy& enemy, const Player& player, const std::string& entity){
    if (entity == "player") return std::max(0, player.getAttack() - enemy.getDefense());
    else if (entity == "enemy") return std::max(0, enemy.getAttack() - player.getDefense());
    return 0;
}

bool randomState () {
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distrib(0, 3); 
    int random_num = distrib(gen);
    if (random_num == 1) return true;
    else return false;
}

bool options(Player& player, Enemy& enemy, int& choice, bool& playerTurn, int& menueType) {
    // Cas 1 : Le combat est en cours
    if (menueType == 1) {
        switch (choice) {
            case 1: // Attack
                enemy.takeDamage(player.getAttack());
                std::cout << "You hit " << enemy.getName() << " with " 
                          << realDamage(enemy, player, "player") << " Damages.\n";
                playerTurn = false; 
                break;
            case 2: // Run away (souvent géré dans le main, mais au cas où)
                break;
            case 3: // Stats
                player.displayStats();
                break;
            case 4: // Items
                std::cout << "Bag empty...\n";
                break;
        }
        return true;
    } 
    // Cas 2, 3 ou 4 : Le combat est fini (Mort, Victoire ou Fuite)
    else {
        switch (choice) {
            case 1: // Restart / Continue
                player.heal(player.getMaxHp());
                enemy.fullHeal();
                playerTurn = true;
                std::cout << "Restarting...\n";
                break;
            case 2: // Quit
                player.saveToFile("save.txt");
                return false;
            case 3: // Stats
                player.displayStats();
                break;
            case 4: // Items
                std::cout << "Bag empty...\n";
                break;
        }
    }
    return true;
}