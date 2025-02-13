#include <stdio.h>
#include <string.h>

typedef struct
{
    char username[50];
    char password[50];
    int isAdmin;   
    float balance;  
} User;

void registerUser()
{
    FILE *file = fopen("users.dat", "a+b");
    if (!file)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    User user;

    printf("Enter a username: ");
    scanf("%s", user.username);

    printf("Enter a password: ");
    scanf("%s", user.password);

    printf("Is this an admin (1 = admin, 0 = user): ");
    scanf("%d", &user.isAdmin);

    user.balance = 0.0;

    size_t written = fwrite(&user, sizeof(User), 1, file);
    if (written != 1)
    {
        printf("Error writing user data to file.\n");
    }
    fclose(file);

    printf("User registered successfully.\n");
}

int loginUser(char *username, char *password)
{
    FILE *file = fopen("users.dat", "rb");
    if (!file)
    {
        printf("Error opening file for reading.\n");
        return -1;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0)
        {
            fclose(file);
            return user.isAdmin;  // Return user role (0 = User, 1 = Admin)
        }
    }
    fclose(file);
    return -1;  // Invalid login
}

void viewBalance(char *username)
{
    FILE *file = fopen("users.dat", "rb");
    if (!file)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (strcmp(username, user.username) == 0)
        {
            printf("Current balance for %s: %.2f\n", username, user.balance);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("User not found.\n");
}

void modifyBalance(char *username, float amount)
{
    FILE *file = fopen("users.dat", "r+b");
    if (!file)
    {
        printf("Error opening file for reading and writing.\n");
        return;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file))
    {
        if (strcmp(username, user.username) == 0)
        {
            user.balance += amount;  // Modify the balance (e.g., adding or subtracting)
            fseek(file, -sizeof(User), SEEK_CUR);
            fwrite(&user, sizeof(User), 1, file);
            printf("Balance updated. New balance: %.2f\n", user.balance);
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("User not found.\n");
}

void adminMenu()
{
    printf("\n=====================================\n");
    printf("          Admin Menu\n");
    printf("=====================================\n");
    printf("1. View User Balance\n");
    printf("2. Modify User Balance\n");
    printf("3. Logout\n");
    printf("=====================================\n");
    printf("Select an option (1-3): ");
}

void userMenu(char *username)
{
    printf("\n=====================================\n");
    printf("           User Menu\n");
    printf("=====================================\n");
    printf("1. View My Balance\n");
    printf("2. Logout\n");
    printf("=====================================\n");
    printf("Select an option (1-2): ");
}

void display_menu()
{
    printf("\n===============================\n");
    printf("  Login or Register\n");
    printf("===============================\n\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("===============================\n\n");
    printf("Select an option (1-3): ");
}

int main()
{
    int choice;

    while (1)
    {
        display_menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char username[50], password[50];

            printf("Enter your username: ");
            scanf("%s", username);

            printf("Enter your password: ");
            scanf("%s", password);

            int result = loginUser(username, password);

            if (result == -1)
            {
                printf("Login failed. Invalid username or password.\n");
            }
            else if (result == 1) 
            {
                printf("Login successful. Admin access granted.\n");
                while (1)
                {
                    adminMenu();
                    int adminChoice;
                    scanf("%d", &adminChoice);

                    switch (adminChoice)
                    {
                    case 1:
                        printf("Enter the username to view balance: ");
                        scanf("%s", username);
                        viewBalance(username);
                        break;
                    case 2:
                        printf("Enter the username to modify balance: ");
                        scanf("%s", username);
                        printf("Enter the amount to add or subtract (use negative for subtraction): ");
                        float amount;
                        scanf("%f", &amount);
                        modifyBalance(username, amount);
                        break;
                    case 3:
                        printf("Logging out...\n");
                        return 0; 
                    default:
                        printf("Invalid option. Try again.\n");
                        break;
                    }
                }
            }
            else 
            {
                printf("Login successful. User access granted.\n");
                while (1)
                {
                    userMenu(username);
                    int userChoice;
                    scanf("%d", &userChoice);

                    switch (userChoice)
                    {
                    case 1:
                        viewBalance(username);
                        break;
                    case 2:
                        printf("Logging out...\n");
                        return 0; 
                    default:
                        printf("Invalid option. Try again.\n");
                        break;
                    }
                }
            }
        }
        break;
        case 2:
            registerUser();
            break;
        case 3:
            printf("Exiting..\n");
            return 0;
        default:
            printf("Invalid choice, please select again.\n");
            break;
        }
    }

    return 0;
}
