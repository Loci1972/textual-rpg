#include "player.h"
#include <iostream>
#include <ctime>
#include <random>
#include "tools.h"
#include "enemy.h"

enum gameState {
    RUNNING,
    FLED,
    WON,
    DEAD,
};


int choises (gameState& combatState, int &menuType){
    int a;
    while (true){
        if (combatState == RUNNING){
            std::cout << " <<<MENUE>>> " << std::endl;
            std::cout << " 1. Attack\n 2. Run away\n 3. Stats\n 4. Items\n" ;
            a = getNumber();
            if (a >= 1 && a <= 4) return a;
            menuType = 1;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == DEAD){
            std::cout << " <<<You Lose...>>> " << std::endl;
            std::cout << " 1. Retry\n 2. quit\n 3. Stats\n 4. Items\n" ;
            a = getNumber();
            menuType = 2;
            if (a >= 1 && a <= 4) return a;
            std::cout << "Invalid choice !!" << std::endl;
        }else if (combatState == FLED){
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
    bool isRunning = true;
    int choice;
    int menuType;
    gameState combatState = RUNNING;
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
        if (combatState != FLED){
            // --- 1. SET THE STATE AND MENU TYPE ---
            if (hero.isAlive() && enemy.isAlive()) {
                menuType = 1; // Combat menu
                combatState = RUNNING;
            } else if (!hero.isAlive()) {
                menuType = 2; // Death menu
                combatState = DEAD;
            }else {
                menuType = 3; // Victory menu
                combatState = WON;
            }
        }else {
            menuType = 4; // Flee menu
        }
        // --- 2. PLAYER OR ENEMY TURN ---
        if (playerTurn) {
            // Get the choice based on the current menu
            choice = choises(combatState, menuType);
            
            // Special case: Fleeing happens in menu 1, choice 2
            if (menuType == 1 && choice == 2) {
                combatState = (hero.runAway(randomState(), true) ? FLED : RUNNING);
                if (combatState != FLED) playerTurn = false; // Failed flee = Enemy hits you
            } else {
                // Execute options and update game state
                isRunning = options(hero, enemy, choice, playerTurn, menuType);
                
                // If we chose "Restart" (Choice 1) in a non-combat menu
                if (menuType != 1 && choice == 1) {
                    combatState = RUNNING;
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