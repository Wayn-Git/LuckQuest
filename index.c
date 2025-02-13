#include <stdio.h>
#include <string.h>

typedef struct
{
    char username[50];
    char password[50];
    int isAdmin;
} User;

void registerUser(){
    FILE *file = fopen("users.dat", "ab");
    if (!file) {
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

    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("User registered successfully.\n");
}

int loginUser(char *username, char *password){
    FILE *file = fopen("users.dat", "rb");
    if (!file) {
        printf("Error opening file for reading.\n");
        return -1;
    }

    User user;
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            fclose(file);
            return user.isAdmin;  
        }
    }
    fclose(file);
    return -1;  
}

void display_menu() {
    printf("\n===============================\n");
    printf("  Login or Register\n");
    printf("===============================\n\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("===============================\n\n");
    printf("Select an option (1-3): ");
}

int main() {
    int choice;
    
    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    char username[50], password[50];

                    printf("Enter your username: ");
                    scanf("%s", username);

                    printf("Enter your password: ");
                    scanf("%s", password);

                    int result = loginUser(username, password);

                    if (result == -1) {
                        printf("Login failed. Invalid username or password.\n");
                    } else if (result == 1) {
                        printf("Login successful. Admin access granted.\n");
                    } else {
                        printf("Login successful. User access granted.\n");
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
