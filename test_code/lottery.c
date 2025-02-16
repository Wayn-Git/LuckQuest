#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 20
#define MIN 1

void PlayLotto() {
    int lotto[6], user[6], matches = 0;
    
    srand(time(NULL)); // Seed random number generator

    // Generate 6 random numbers
    printf("Lotto Numbers: ");
    for (int i = 0; i < 6; i++) {
        lotto[i] = rand() % (MAX - MIN + 1) + MIN;
    }
    printf("\n");

    // Get user input
    printf("Enter 6 numbers: ");
    for (int i = 0; i < 6; i++) {
        scanf("%d", &user[i]);
    }

    // Check for matches
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (user[i] == lotto[j]) {
                matches++;
                break; // Avoid counting duplicates
            }
        }
    }

    printf("You matched %d number(s)!\n", matches);
}

int main() {
    PlayLotto();
    return 0;
}
