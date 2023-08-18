#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Set the troops
void setTroops(int **troopsVals, int numTroops) {
    *troopsVals = (int *)malloc(sizeof(int) * numTroops);
}

//Main function
int main(int argc, char *argv[]) {

    //Flags
    bool maxTroops = false;
    bool verbose = true;

    if ( argc > 2 && strcmp(argv[1], "help") == 0) {
        printf("Usage: ./riskDiceRoll [-m] (Max out troops every roll) [-v] verbose output\n");
        return 0;
    }
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-m") == 0) {
            maxTroops = true;
        }
        if (strcmp(argv[i], "-v") == 0) {
            verbose = false;
        }
    }

    // Seed Random
    srand(time(NULL));

    //Declare total troops
    int attackTroopsTotal = 0;
    int defenseTroopsTotal = 0;
    
    //Determine troops
    while (1) {
        printf("Number of Attack Troops: ");
        scanf("%d", &attackTroopsTotal);
        if (attackTroopsTotal <= 0) {
            printf("Invalid Attack Troops\n");
        } else {
            break;
        }
    }
    
    while (1)
    {
        printf("Number of Defense Troops: ");
        scanf("%d", &defenseTroopsTotal);
        if (defenseTroopsTotal <= 0) {
            printf("Invalid Defense Troops\n");
        } else {
            break;
        }
    }

    bool changeTroopsAttack = true;
    bool changeTroopsDefense = true;
    int *attackTroops = NULL;
    int *defendTroops = NULL;
    int attackingTroops = 0;
    int defendingTroops = 0;

    if (maxTroops) {
        if (3 > (attackTroopsTotal - 1)) {
            attackingTroops = (attackTroopsTotal - 1);
        } else {
            attackingTroops = 3;
        }
        setTroops(&attackTroops, attackingTroops);

        if (2 > defenseTroopsTotal) {
            defendingTroops = defenseTroopsTotal;
        } else {
            defendingTroops = 2;
        }
        setTroops(&defendTroops, defendingTroops);
        changeTroopsAttack = false;
        changeTroopsDefense = false;
    }

    while (1)
    {
        
        if (changeTroopsAttack) {
            while (1) {
                printf("Attack with: ");
                scanf("%d", &attackingTroops);
                if (attackingTroops <= 0 || attackingTroops > (attackTroopsTotal - 1) || attackingTroops > 3) {
                    printf("Invalid Attacking Troops\n");
                    continue;
                }
                setTroops(&attackTroops, attackingTroops);
                break;
            }
            changeTroopsAttack = false;
        }

        if (changeTroopsDefense) {
            while (1) {
                printf("Defend with: ");
                scanf("%d", &defendingTroops);
                if (defendingTroops <= 0 || defendingTroops > defenseTroopsTotal || defendingTroops > 2) {
                    printf("Invalid Defending Troops\n");
                    continue;
                }
                setTroops(&defendTroops, defendingTroops);
                break;
            }
            changeTroopsDefense = false;
        }

        for (int i = 0; i < attackingTroops; i++) {
            attackTroops[i] = rand() % 6 + 1;
        }
        for (int i = 0; i < defendingTroops; i++) {
            defendTroops[i] = rand() % 6 + 1;
        }

        for (int i = 0; i < attackingTroops - 1; i++) {
            for (int j = 0; j < attackingTroops - i - 1; j++) {
                if (attackTroops[j] < attackTroops[j + 1]) {
                    int temp = attackTroops[j];
                    attackTroops[j] = attackTroops[j + 1];
                    attackTroops[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < defendingTroops - 1; i++) {
            for (int j = 0; j < defendingTroops - i - 1; j++) {
                if (defendTroops[j] < defendTroops[j + 1]) {
                    int temp = defendTroops[j];
                    defendTroops[j] = defendTroops[j + 1];
                    defendTroops[j + 1] = temp;
                }
            }
        }

        int low = attackingTroops < defendingTroops ? attackingTroops : defendingTroops;
        int dl = 0;
        int al = 0;
        if (verbose) {
            printf("Attack v. Defense\n");
        }
        for (int i = 0; i < low; i++) {
            if (verbose) {
                printf("%d vs %d\n", attackTroops[i], defendTroops[i]);
            }
            if (attackTroops[i] > defendTroops[i]) {
                dl++;
            } else {
                al++;
            }
        }

        attackTroopsTotal -= al;
        defenseTroopsTotal -= dl;

        if (verbose) {
            printf("Attack Loses: %d Defence Loses: %d\n", al, dl);
            printf("%d Attack troops left\n", attackTroopsTotal);
            printf("%d Defense troops left\n", defenseTroopsTotal);
        }

        if ( attackTroopsTotal == 1 ) {
            printf("Attackers Depleted\n");
            free(attackTroops);
            free(defendTroops);
            return 0;
        }
        if ( defenseTroopsTotal == 0 ) {
            free(attackTroops);
            free(defendTroops);
            printf("Defense Depeleted\nAttack Wins\n");
            return 0;
        }

        while (1) {
            if (maxTroops) {
                break;
            }
            printf("Would you like to change your attack troops (y/n): ");
            char input;
            scanf(" %c", &input);
            if (input == 'y' || input == 'Y') {
                changeTroopsAttack = true;
                free(attackTroops);
                break;
            } else if (input == 'n' || input == 'N') {
                break;
            } else {
                printf("Invalid Input\n");
            }
            break;
        }

        while (1) {
            if (maxTroops) {
                if ( defenseTroopsTotal == 1 ) {
                    free(defendTroops);
                    setTroops(&defendTroops, 1);
                    defendingTroops = 1;
                }
                break;
            }
            printf("Would you like to change your defense troops (y/n): ");
            char input;
            scanf(" %c", &input);
            if (input == 'y' || input == 'Y') {
                changeTroopsDefense = true;
                free(defendTroops);
                break;
            } else if (input == 'n' || input == 'N') {
                if ( defenseTroopsTotal == 1 ) {
                    free(defendTroops);
                    setTroops(&defendTroops, 1);
                    defendingTroops = 1;
                }
                break;
            } else {
                printf("Invalid Input\n");
            }
            break;
        }
    }
    return 0;
}
