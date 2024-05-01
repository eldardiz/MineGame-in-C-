    #include <stdio.h>
    #include <windows.h>
    #include <conio.h>
    #include <time.h>
    #include "advgame.h"

    int currentLevel = 0;
    int main() {


        /*int consoleWidth = 105;
        SplashScreen('*',consoleWidth);
        printf("\n");
        for(int i=0 ; i<=10 ; i++){
            printf("*                                                                                                       *\n");
        }
        printf("*                                   Welcome to the MazeGame!                                            *\n");
        printf("*                                   Loading... Please Wait!                                             *\n");
        for(int i=0 ; i<=10 ; i++){
            printf("*                                                                                                       *\n");

        }

        SplashScreen('*',consoleWidth);
        printf("\n");
        Delay(2);
        system("cls || clear");
*/
        struct ChoosenCharacter karakter;
        GameBegin(&karakter);
        ChooseYourClass(&karakter);
        initializeMines();

        initializePlayerPosition(&karakter, MazeMap[currentLevel]);

        char choice;
        while (1) {
        do {
            clearScreen();
            printMapWithMotionEffect(&karakter, MazeMap[currentLevel]);

            checkMineCollisions(&karakter);
            if (isGameOver(&karakter)) {
                printf("Game Over! Your adventure has come to an end.\n");
                break;
            }


        if (hasReachedExit(&karakter, MazeMap[currentLevel])) {
        printf("Congratulations! You've finished level %d.\n", currentLevel + 1);


        if (currentLevel < 2) {
            displayWelcomeMessage(currentLevel + 1);
            printf("Welcome to the new level! Press any key to begin!\n");


            currentLevel++;
            initializePlayerPosition(&karakter, MazeMap[currentLevel]);
            resetPlayerHealth(&karakter);

        } else {
            printf("You've completed all levels! Game Over.\n");
            break;
        }
        }


            printf("\nChoose a direction (W/A/S/D to move, uppercase Q to quit): ");
            choice = getch();   //reading a character directly from a keyboard (conio.h biblioteka)
            char uppercaseChoice = toupper(choice); //windows.h biblioteka

            if (uppercaseChoice == 'W' || uppercaseChoice == 'A' || uppercaseChoice == 'S' || uppercaseChoice == 'D') {
                movePlayer(&karakter, uppercaseChoice, MazeMap[currentLevel]);
            } else if (uppercaseChoice != 'Q') {
                printf("Invalid choice. Please enter W, A, S, D, or Q.\n");
            }

            clearInputBuffer();
            clearScreen();

        } while (choice != 'Q');

        printf("Thanks for playing, %s!\n\n\n", karakter.name);
        printf("MineGame made by Eldar Dizdarevic\n");

        printf("Do you want to play again? (Type 'yes' to play again): ");
        char playAgain[10];
        scanf("%9s", playAgain);

        if (strcmp(playAgain, "yes") != 0) {
            break;
        }
        resetGame(&karakter);
        clearInputBuffer();
    }

    return 0;
}
