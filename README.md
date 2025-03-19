# 🎰 Casino Game System

A console-based casino simulation developed in C with user management and gaming features.

![Casino Demo](https://via.placeholder.com/800x400.png?text=Casino+Game+System+Demo) *Example screenshot placeholder*

## 📋 Table of Contents
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-Usage)
- [Game Details](#-game-details)
- [Technical Specs](#-technical-specs)
- [Future Plans](#-future-plans)

## 🚀 Features

### 👤 User System
- **Secure Registration:** Password validation with unique username enforcement (3-20 characters).
- **Persistent Profiles:** User profiles stored in `users.txt`.
- **Password Requirements:**
  - Minimum 8 characters.
  - At least 1 uppercase letter.
  - At least 1 lowercase letter.
  - At least 1 number.

### 🎮 Gaming
- **Coin Flip Game:** Heads/Tails guessing with a bet range of $1.00 - $1000.00.
- **1:1 Payout System:** Win or lose based on your bet.
- **XP and Level Progression:** Earn XP and level up based on your wins.
- **Coming Soon:**
  - Blackjack
  - Lottery
  - Wheel of Fortune

### 👨💻 Admin Controls
- **View All Users:** See a complete list of registered users.
- **Modify Balances:** Adjust player funds (+/-).
- **Administrative Privileges:** Admin-only features.

## 💻 Installation

1. **Clone Repository**
   ```bash
   git clone https://github.com/yourusername/casino-game-system.git
   cd casino-game-system

2. **Compile Program**
   ```bash
    gcc index.c -o casino
   
3. **Run Application**
    ```bash
    ./casino

## 🕹️ Usage

### 🎮 Player Interface

**Main Menu:**

- **View Stats:** Check your balance, level, XP, and wins.
- **Start Game:** Access the game selection menu.
- **Log Out:** Exit the current session.

### 🔧 Admin Interface

**Admin Menu:**

- **View All Users:** See a complete list of registered users.
- **Modify Balances:** Adjust player funds (+/-).
- **Log Out:** Exit the current session.

---

---

## 📂 Data Storage

- **File:** `users.txt`
- **Format:**
  - `username password isAdmin balance xp level wins`

---

## 🔑 Key Constants

   
     ```c
     #define STARTING_BALANCE 100.0
    #define BET_MINIMUM 1.0
    #define BET_MAXIMUM 1000.0
    #define MIN_PASSWORD_LENGTH 8


  

## 📅 Future Plans

- Implement Blackjack game logic
- Add lottery number generator
- Develop wheel-spin mechanics
- Password encryption
- Transaction history tracking
- Graphical user interface

---

## ⚠️ Note

This is an educational project. Not associated with real gambling systems.
