#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void CoinFlip(float prob_num1) {
 
    float random_value = (float) rand() / RAND_MAX;

  
    if (random_value < prob_num1) {
        printf("You Win: Heads\n");
    } else {
        printf("You Lost: Tails\n");
    }
}


int main() {
    srand(time(NULL)); 

    float prob_num1 = 0.50;  
    CoinFlip(prob_num1);  

    return 0;
}