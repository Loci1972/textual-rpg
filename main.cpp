#include "player.h"
#include <iostream>
#include <ctime>
#include <random>
#include "tools.h"
#include "enemy.h"

#define COMBAT_STATE_F "finished"
#define COMBAT_STATE_R "running"

int choises (Player& player, std::string& combatState, bool& fled, int &menuType){
    int a;
    while (true){
        if (player.isAlive() && combatState != COMBAT_STATE_F && !fled){
            std::cout << " <<<MENUE>>> " << std::endl;
            std::cout << " 1. Attack\n 2. Run away\n 3. Stats\n 4. Items\n" ;
            a = getNumber();
            if (a >= 1 && a <= 4) return a;
            menuType = 1;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (!player.isAlive() && !fled){
            std::cout << " <<<You Lose...>>> " << std::endl;
            std::cout << " 1. Retry\n 2. quit\n 3. Stats\n 4. Items\n" ;
            a = getNumber();
            menuType = 2;
            if (a >= 1 && a <= 4) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (fled){
            std::cout << " <<<You Ran Away 🐔...>>> " << std::endl;
            std::cout << " 1. New fight\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menuType = 3;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;
            
        }
        else {
            std::cout << " <<<YOU WON !!!...>>> " << std::endl;
            std::cout << " 1. New fight\n 2. quit\n 3. Stats\n" ;
            a = getNumber();
            menuType = 4;
            if (a >= 1 && a <= 3) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }
    }
}

int main() {
    bool playerTurn = true;
    bool fled = false;
    int choice;
    int menuType;
    std::string combatState;
    bool isRunning = true;

    Enemy enemy("Spider");
    Player hero("");

    // Load or Create Player
    if (hero.loadFromFile("save.txt")) {
        std::cout << "Welcome back, " << hero.getName() << "!\n";
    } else {
        std::cout << "New adventure! Enter your name: ";
        hero = Player(getString());
    }

    while (isRunning) {
        // --- 1. SET THE STATE AND MENU TYPE ---
        if (hero.isAlive() && enemy.isAlive() && !fled) {
            menuType = 1; // Combat menu
            combatState = COMBAT_STATE_R;
        } else if (!hero.isAlive()) {
            menuType = 2; // Death menu
            combatState = COMBAT_STATE_F;
        } else if (fled) {
            menuType = 4; // Flee menu
            combatState = COMBAT_STATE_F;
        } else {
            menuType = 3; // Victory menu
            combatState = COMBAT_STATE_F;
        }

        // --- 2. PLAYER OR ENEMY TURN ---
        if (playerTurn) {
            // Get the choice based on the current menu
            choice = choises(hero, combatState, fled, menuType);
            
            // Special case: Fleeing happens in menu 1, choice 2
            if (menuType == 1 && choice == 2) {
                fled = hero.runAway(randomState(), true, enemy);
                if (!fled) playerTurn = false; // Failed flee = Enemy hits you
            } else {
                // Execute options and update game state
                isRunning = options(hero, enemy, choice, playerTurn, menuType);
                
                // If we chose "Restart" (Choice 1) in a non-combat menu
                if (menuType != 1 && choice == 1) {
                    fled = false; // Reset flee status for the new fight
                }
            }
        } else {
            // --- ENEMY TURN ---
            if (hero.isAlive() && enemy.isAlive()) {
                std::cout << "\n--- " << enemy.getName() << "'s Turn ---\n";
                hero.takeDamage(enemy.getAttack());
                std::cout << enemy.getName() << " deals " << realDamage(enemy, hero, "enemy") << " damage!\n";
                hero.displayHealthBar();
            }
            playerTurn = true; // Hand over to player
        }
    }

    std::cout << "Thanks for playing!" << std::endl;
    return 0;
}