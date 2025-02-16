# 🎰 Casino Game System

A console-based casino simulation developed in C with user management and gaming features.

![Casino Demo](https://via.placeholder.com/800x400.png?text=Casino+Game+System+Demo) *Example screenshot placeholder*

## 📋 Table of Contents
- [Features](#-features)
- [Installation](#-installation)
- [Usage](#-usage)
- [Game Details](#-game-details)
- [Technical Specs](#-technical-specs)
- [Future Plans](#-future-plans)

## 🚀 Features

### 👤 User System
- Secure registration with password validation
- Unique username enforcement (3-20 characters)
- Persistent user profiles stored in `users.txt`
- Password requirements:
  - Minimum 8 characters
  - At least 1 uppercase letter
  - At least 1 lowercase letter
  - At least 1 number

### 🎮 Gaming
- **Coin Flip Game** (Currently Available):
  - Heads/Tails guessing
  - Bet range: $1.00 - $1000.00
  - 1:1 payout system
  - XP and level progression
- **Coming Soon**:
  - Blackjack
  - Lottery
  - Wheel of Fortune

### 👨💻 Admin Controls
- View all registered users
- Modify user balances
- Administrative privileges

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

# 🕹️ Telecom Game Project

## 📖 Usage

### 🎮 Player Interface

#### Main Menu:

1. **View Stats** - Check balance, level, XP, and wins
2. **Start Game** - Access game selection
3. **Log Out**

### 🔧 Admin Interface

#### Admin Menu:

1. **View All Users** - See complete user list
2. **Modify Balances** - Adjust player funds (+/-)
3. **Log Out**

## 🎲 Gameplay Example

```
Coin Flip Game - Balance: $150.00
Bet ($1.00-$1000.00): 50
Heads (H) or Tails (T): h

Coin landed: HEADS
You won $50.00!
New balance: $200.00
Level Up! You are now level 2!
```

---

## 📂 Data Storage

- **File:** `users.txt`
- **Format:**
  ```
  username password isAdmin balance xp level wins
  ```

---

## 🔑 Key Constants

```c
#define STARTING_BALANCE 100.0
#define BET_MINIMUM 1.0
#define BET_MAXIMUM 1000.0
#define MIN_PASSWORD_LENGTH 8
```

---

## 📅 Future Plans

- ✅ Implement Blackjack game logic
- ✅ Add lottery number generator
- ✅ Develop wheel-spin mechanics
- ✅ Password encryption
- ✅ Transaction history tracking
- ✅ Graphical user interface

---

⚠️ **Note:** This is an educational project. Not associated with real gambling systems.

---




    
