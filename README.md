# 🗡️ Textual RPG (C++)

A turn-based textual RPG built in C++ focusing on core game mechanics and system design.

---

## 🎮 Overview

This project simulates a simple RPG combat system in the terminal.
The player can fight enemies, gain experience, level up, and manage game progression through a save system.

---

## ✨ Features

* ⚔️ Turn-based combat system
* 📈 XP & Level progression
* ❤️ Health, attack, and defense stats
* 💬 Dynamic dialogue based on player HP
* 💾 Save / Load system (file-based)
* 🎯 Multiple game states (combat, victory, defeat, flee)

---

## 🧠 Technical Highlights

* Object-Oriented Design (`Player`, `Enemy`)
* Separation of concerns (`tools`, game logic)
* File handling (`std::fstream`)
* State-driven gameplay logic

---

## 📦 Project Structure

```
.
├── main.cpp
├── player.h / player.cpp
├── enemy.h / enemy.cpp
├── tools.h / tools.cpp
```

---

## ⚙️ Build & Run

### Compile

```bash
g++ main.cpp player.cpp enemy.cpp tools.cpp -o game
```

### Run

```bash
./game
```

---

## 💾 Save System

Player data is stored in:

```
save.txt
```

Includes:

* Name
* Level
* XP
* Stats
* Gold

---

## 🚀 Future Improvements

* Inventory system
* Multiple enemies
* Skills / abilities
* Better game state architecture (enum-based)
* Graphical version (SFML / Raylib)

---

## 👤 Author

Laurent

---

## ⚠️ Note

This project was built as a learning experience and is continuously being improved.
