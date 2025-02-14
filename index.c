#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FILE_NAME "users.txt"
#define MAX_USERS 100
#define MAX_STRING 50
#define MIN_PASSWORD_LENGTH 8
#define STARTING_BALANCE 100.0
#define BET_MINIMUM 1.0
#define BET_MAXIMUM 1000.0

typedef struct {
    char username[MAX_STRING];
    char password[MAX_STRING];
    int isAdmin;
    float balance;
    int xp;
    int level;
    int wins;
} User;


int userExists(const char *username);
void registerUser(void);
int loginUser(const char *username, const char *password, User *loggedUser);
int modifyBalance(const char *username, float amount);
void adminTerminal(User *loggedUser);
void userTerminal(User *loggedUser);
int validatePassword(const char *password);
void saveUserData(const User *user);
void playCoinFlip(User *user);
void updateUserStats(User *user, int won, float betAmount);

// File operations
int userExists(const char *username) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        return 0;
    }

    User user;
    while (fscanf(file, "%49s %49s %d %f %d %d %d\n", 
           user.username, user.password, &user.isAdmin, 
           &user.balance, &user.xp, &user.level, &user.wins) == 7) {
        if (strcmp(username, user.username) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

int validatePassword(const char *password) {
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        printf("Password must be at least %d characters long.\n", MIN_PASSWORD_LENGTH);
        return 0;
    }
    
    int hasUpper = 0, hasLower = 0, hasDigit = 0;
    for (const char *p = password; *p; p++) {
        if (*p >= 'A' && *p <= 'Z') hasUpper = 1;
        if (*p >= 'a' && *p <= 'z') hasLower = 1;
        if (*p >= '0' && *p <= '9') hasDigit = 1;
    }
    
    if (!hasUpper || !hasLower || !hasDigit) {
        printf("Password must contain at least one uppercase letter, one lowercase letter, and one number.\n");
        return 0;
    }
    
    return 1;
}

void registerUser(void) {
    FILE *file = fopen(FILE_NAME, "r");
    int userCount = 0;

    // Count existing users if the file exists
    if (file) {
        User tempUser;
        while (fscanf(file, "%49s %49s %d %f %d %d %d\n",
               tempUser.username, tempUser.password, &tempUser.isAdmin,
               &tempUser.balance, &tempUser.xp, &tempUser.level,
               &tempUser.wins) == 7) {
            userCount++;
        }
        fclose(file);
    }

    if (userCount >= MAX_USERS) {
        printf("Error: Maximum number of users reached (%d). Cannot register new user.\n", MAX_USERS);
        return;
    }

    file = fopen(FILE_NAME, "a+");
    if (!file) {
        printf("Error: Cannot open user database.\n");
        return;
    }

    User user;
    char input[MAX_STRING];

    // Username input
    printf("Enter a username (3-20 characters): ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fclose(file);
        return;
    }
    input[strcspn(input, "\n")] = '\0';
    
    if (strlen(input) < 3 || strlen(input) > 20) {
        printf("Error: Username must be between 3 and 20 characters.\n");
        fclose(file);
        return;
    }
    
    if (userExists(input)) {
        printf("Error: Username already exists.\n");
        fclose(file);
        return;
    }
    strncpy(user.username, input, MAX_STRING - 1);

    // Password input
    printf("Enter a password (minimum %d characters, must include uppercase, lowercase, and number): ", 
           MIN_PASSWORD_LENGTH);
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fclose(file);
        return;
    }
    input[strcspn(input, "\n")] = '\0';
    
    if (!validatePassword(input)) {
        fclose(file);
        return;
    }
    strncpy(user.password, input, MAX_STRING - 1);


    user.isAdmin = 0;  
    user.balance = STARTING_BALANCE;
    user.xp = 0;
    user.level = 1;
    user.wins = 0;

    fprintf(file, "%s %s %d %.2f %d %d %d\n", 
            user.username, user.password, user.isAdmin, 
            user.balance, user.xp, user.level, user.wins);
    fclose(file);
    printf("User registered successfully! Starting balance: $%.2f\n", STARTING_BALANCE);
}

void saveUserData(const User *user) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error: Cannot open user database.\n");
        return;
    }

    User users[MAX_USERS];
    int userCount = 0;
    
    while (userCount < MAX_USERS && 
           fscanf(file, "%49s %49s %d %f %d %d %d\n",
                  users[userCount].username, users[userCount].password,
                  &users[userCount].isAdmin, &users[userCount].balance,
                  &users[userCount].xp, &users[userCount].level,
                  &users[userCount].wins) == 7) {
        if (strcmp(users[userCount].username, user->username) == 0) {
            users[userCount] = *user;
        }
        userCount++;
    }
    fclose(file);

    file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error: Cannot update user database.\n");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %d %.2f %d %d %d\n",
                users[i].username, users[i].password, users[i].isAdmin,
                users[i].balance, users[i].xp, users[i].level, users[i].wins);
    }
    fclose(file);
}

void playCoinFlip(User *user) {
    float bet;
    char choice;

    printf("\nCoin Flip Game - Balance: $%.2f\n", user->balance);
    
    // Get and validate bet
    while (1) {
        printf("Bet ($%.2f-$%.2f): ", BET_MINIMUM, BET_MAXIMUM);
        if (scanf("%f", &bet) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (bet >= BET_MINIMUM && bet <= BET_MAXIMUM && bet <= user->balance) break;
        printf("Invalid bet! Must be $%.2f-$%.2f\n", BET_MINIMUM, BET_MAXIMUM);
    }

    // Get and validate choice
    while (1) {
        printf("Heads (H) or Tails (T): ");
        choice = getchar();
        while (getchar() != '\n');
        
        if (choice == 'H' || choice == 'h' || choice == 'T' || choice == 't') break;
        printf("Invalid choice. Enter H or T\n");
    }

    // Game logic
    int result = rand() % 2;
    int won = ((choice == 'H' || choice == 'h') && !result) || 
              ((choice == 'T' || choice == 't') && result);
    
    printf("\nCoin landed: %s\n", result ? "TAILS" : "HEADS");
    printf("You %s $%.2f\n", won ? "won" : "lost", bet);
    
    updateUserStats(user, won, won ? bet : -bet);
    printf("New balance: $%.2f\n", user->balance);
    saveUserData(user);
}

void updateUserStats(User *user, int won, float betAmount) {
    user->balance += betAmount;
    if (won) {
        user->wins++;
        user->xp += 10;
        if (user->xp >= user->level * 100) {
            user->level++;
            printf("Level Up! You are now level %d!\n", user->level);
        }
    }
}

void userTerminal(User *loggedUser) {
    int choice;
    printf("\nWelcome, %s! (Level %d)\n", loggedUser->username, loggedUser->level);
    
    while (1) {
        printf("\nUser Menu:\n");
        printf("1. View Stats\n");
        printf("2. Start Game\n");
        printf("3. Log Out\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');
        
        switch (choice) {
            case 1:
                printf("\nUser Stats:\n");
                printf("Balance: $%.2f\n", loggedUser->balance);
                printf("Level: %d\n", loggedUser->level);
                printf("XP: %d/%d\n", loggedUser->xp, loggedUser->level * 100);
                printf("Wins: %d\n", loggedUser->wins);
                break;
                
            case 2: {
                int gameChoice;
                printf("\nChoose a game to play:\n");
                printf("1. Coin Flip\n");
                printf("2. Black Jack\n");
                printf("3. Lottery\n");
                printf("4. Spin The Wheel\n");
                printf("Enter your choice: ");
                
                if (scanf("%d", &gameChoice) != 1) {
                    printf("Invalid input.\n");
                    while (getchar() != '\n');
                    break;
                }
                while (getchar() != '\n');

                switch (gameChoice) {
                    case 1:
                        playCoinFlip(loggedUser);
                        break;
                    case 2:
                        printf("Black Jack game is under development.\n");
                        break;
                    case 3:
                        printf("Lottery game is under development.\n");
                        break;
                    case 4:
                        printf("Spin The Wheel game is under development.\n");
                        break;
                    default:
                        printf("Invalid game choice. Please try again.\n");
                }
                break;
            }
                
            case 3:
                printf("Logging out. Goodbye!\n");
                return;
                
            default:
                printf("Invalid choice.\n");
        }
    }
}

void adminTerminal(User *loggedUser) {
    int choice;
    printf("\nWelcome, Admin %s!\n", loggedUser->username);
    
    while (1) {
        printf("\nAdmin Menu:\n");
        printf("1. View All Users\n");
        printf("2. Modify User Balance\n");
        printf("3. Log Out\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        while (getchar() != '\n');  // Clear input buffer
        
        switch (choice) {
            case 1: {
                FILE *file = fopen(FILE_NAME, "r");
                if (!file) {
                    printf("Error: Cannot open user database.\n");
                    break;
                }
                
                User user;
                printf("\nUser List:\n");
                printf("%-20s %-10s %-10s %-6s %-6s\n", 
                       "Username", "Balance", "Level", "XP", "Wins");
                printf("------------------------------------------------\n");
                
                while (fscanf(file, "%49s %49s %d %f %d %d %d\n",
                       user.username, user.password, &user.isAdmin,
                       &user.balance, &user.xp, &user.level, &user.wins) == 7) {
                    printf("%-20s $%-9.2f %-10d %-6d %-6d\n",
                           user.username, user.balance, user.level,
                           user.xp, user.wins);
                }
                fclose(file);
                break;
            }
            
            case 2: {
                char username[MAX_STRING];
                float amount;
                
                printf("Enter username: ");
                if (fgets(username, sizeof(username), stdin) == NULL) break;
                username[strcspn(username, "\n")] = '\0';
                
                if (!userExists(username)) {
                    printf("User not found.\n");
                    break;
                }
                
                printf("Enter amount to add/subtract: ");
                if (scanf("%f", &amount) != 1) {
                    printf("Invalid amount.\n");
                    while (getchar() != '\n');  // Clear input buffer
                    break;
                }
                while (getchar() != '\n');  // Clear input buffer
                
                if (modifyBalance(username, amount)) {
                    printf("Balance updated successfully.\n");
                }
                break;
            }
            
            case 3:
                printf("Logging out. Goodbye!\n");
                return;
                
            default:
                printf("Invalid choice.\n");
        }
    }
}

int modifyBalance(const char *username, float amount) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error: Cannot open user database.\n");
        return 0;
    }

    User users[MAX_USERS];
    int userCount = 0;
    int found = 0;
    
    while (userCount < MAX_USERS && 
           fscanf(file, "%49s %49s %d %f %d %d %d\n",
                  users[userCount].username, users[userCount].password,
                  &users[userCount].isAdmin, &users[userCount].balance,
                  &users[userCount].xp, &users[userCount].level,
                  &users[userCount].wins) == 7) {
        if (strcmp(users[userCount].username, username) == 0) {
            users[userCount].balance += amount;
            if (users[userCount].balance < 0) {
                users[userCount].balance = 0;
            }
            found = 1;
        }
        userCount++;
    }
    fclose(file);

    if (!found) {
        printf("User not found.\n");
        return 0;
    }

    file = fopen(FILE_NAME, "w");
    if (!file) {
        printf("Error: Cannot update user database.\n");
        return 0;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %d %.2f %d %d %d\n",
                users[i].username, users[i].password, users[i].isAdmin,
                users[i].balance, users[i].xp, users[i].level, users[i].wins);
    }
    fclose(file);
    return 1;
}

int loginUser(const char *username, const char *password, User *loggedUser) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("Error: Cannot open user database.\n");
        return -1;
    }

    User user;
    while (fscanf(file, "%49s %49s %d %f %d %d %d\n",
           user.username, user.password, &user.isAdmin,
           &user.balance, &user.xp, &user.level, &user.wins) == 7) {
        if (strcmp(username, user.username) == 0 &&
           strcmp(password, user.password) == 0) {
            *loggedUser = user;
            fclose(file);
            return user.isAdmin;
        }
    }
    fclose(file);
    return -1;
}

int main(void) {
    srand((unsigned int)time(NULL));
    
    // Create the users file if it doesn't exist
    FILE *file = fopen(FILE_NAME, "a");
    if (file) {
        fclose(file);
    }

    int choice;
    char username[MAX_STRING], password[MAX_STRING];
    User loggedUser;

    while (1) {
        printf("\nWelcome to Casino Game System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;
        }
        while (getchar() != '\n');  // Clear input buffer
        
        switch (choice) {
            case 1:
                registerUser();
                break;
                
            case 2:
                printf("Username: ");
                if (fgets(username, sizeof(username), stdin) == NULL) break;
                username[strcspn(username, "\n")] = '\0';
                
                printf("Password: ");
                if (fgets(password, sizeof(password), stdin) == NULL) break;
                password[strcspn(password, "\n")] = '\0';
                
                int loginResult = loginUser(username, password, &loggedUser);
                if (loginResult == -1) {
                    printf("Login failed: Invalid username or password.\n");
                } else if (loginResult == 1) {
                    adminTerminal(&loggedUser);
                } else {
                    userTerminal(&loggedUser);
                }
                break;
                
            case 3:
                printf("Thank you for playing! Goodbye!\n");
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}