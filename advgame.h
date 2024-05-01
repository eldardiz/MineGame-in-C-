#ifndef ADVGAME_H_INCLUDED
#define ADVGAME_H_INCLUDED
#define MAX_MINES 20
#define COLLISION_CHARACTER 'X'
#include <time.h>
#include <windows.h>
extern int currentLevel;
extern int checkpointReached;

void clearScreen() {
    system("cls");
}

void clearInputBuffer() {   //clearing the input buffer for a functions like getch...
    while (_kbhit()) {
        _getch();
    }
}

void SplashScreen(char asterisk, int count){
    for(int i=0;i<count;i++){
        printf("%c",asterisk);
    }
}

void Delay(int seconds){
#ifdef _WIN32
Sleep(seconds * 1000);
#endif // _WIN32
}

struct ChoosenCharacter{
char name[30];
int health;
char choosen_class[30];
int positionX;
int positionY;
};


void GameBegin(struct ChoosenCharacter *link) {
    printf("Hello Player! Welcome to MazeGame\n\n");
    printf("Please enter your name: ");
    scanf("%s", link->name);

    link->positionX = 1;
    link->positionY = 1;
}

void ChooseYourClass(struct ChoosenCharacter *v){
    int choice;
    printf("\nPlease choose your character, %s.\n", v->name);
    printf("For Warrior [level:Easy] enter 1. \n");
    printf("For Ninja [level:Medium] enter 2. \n");
    printf("For Thief [level:Hard] enter 3.\n\n");
    printf("Enter your number:"); scanf("%d", &choice);

    switch(choice){
        case 1:
        printf("You choose a Warrior.\n");
        v->health = 2000;
        strcpy(v->choosen_class, "warrior");
        break;

        case 2:
        printf("You choose a Ninja.\n");
        v->health = 1250;
        strcpy(v->choosen_class, "ninja");
        break;

        case 3:
        printf("You choose a Thief.\n");
        v->health = 800;
        strcpy(v->choosen_class, "thief");
        break;

        default: printf("Wrong Number, please enter a number between 1-3. \n");
    }
}

    char MazeMap[3][20][20] = {
    {
        "####################",
        "#                  #",
        "#  ###   ###   ### #",
        "#    #   #       # #",
        "#    #   #   #   # #",
        "#    #   #####   # #",
        "#        #   #   # #",
        "######   #   ##### #",
        "#        #   #     #",
        "#        #####   ###",
        "#         #  #   # #",
        "#  ######   #   # ##",
        "#        #   #   # #",
        "#   ######   ##### #",
        "#        #   #     #",
        "#        #   #   ###",
        "#   ######   #   # #",
        "#                  E",
        "####################"
    },

    {
        "####################",
        "#             ######",
        "#  ####    ####   ##",
        "#    ##            #",
        "#         ##    #  #",
        "#    #   ##### #  ##",
        "#   ###       ## ###",
        "######   #  ###### #",
        "#        #       ###",
        "#        ######   ##",
        "#  #     #   #  # ##",
        "#  ######   #####  #",
        "#  ###      #   #  #",
        "#   ######   ##### #",
        "#   #        #     #",
        "#   #    #   #   ###",
        "#   ######   #   # #",
        "#            #     E",
        "####################"
    },

    {
        "####################",
        "#   #  #####  #   E#",
        "# # #  ##### #     #",
        "# # #  #####    #  #",
        "# # #           #  #",
        "# # #####  #####   #",
        "# # #       #####  #",
        "#   #  ###  #####  #",
        "# #######  #####   #",
        "# # #              #",
        "#   #  #############",
        "# ###  ##  #####  ##",
        "#   #  ###  ###    #",
        "# ####   #####  ####",
        "#              #####",
        "# ######  ###  #####",
        "# #   #    #      ##",
        "#   #######  ##### #",
        "####################"
    }
};


int hasReachedExit(struct ChoosenCharacter *player, char MazeMap[20][20]) {
    int x = player->positionX;
    int y = player->positionY;

    return MazeMap[y][x] == 'E';
}


void printMap(struct ChoosenCharacter *player, char MazeMap[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == player->positionY && j == player->positionX) {
                printf("[%c]", player->choosen_class[0]);  //Prvo slovo igraca..
            } else {
                printf(" %c ", MazeMap[i][j]);
            }
        }
        printf("\n");
    }
}




void movePlayer(struct ChoosenCharacter *player, char direction, char MazeMap[20][20]) {
    switch (direction) {
        case 'W':
            if (player->positionY > 0 && MazeMap[player->positionY - 1][player->positionX] != '#') {
                player->positionY--;
            }
            break;
        case 'A':
            if (player->positionX > 0 && MazeMap[player->positionY][player->positionX - 1] != '#') {
                player->positionX--;
            }
            break;
        case 'S':
            if (player->positionY < 19 && MazeMap[player->positionY + 1][player->positionX] != '#') {
                player->positionY++;
            }
            break;
        case 'D':
            if (player->positionX < 19 && MazeMap[player->positionY][player->positionX + 1] != '#') {
                player->positionX++;
            }
            break;
        default:
            break;
    }
}


void initializePlayerPosition(struct ChoosenCharacter *player, char MazeMap[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (MazeMap[i][j] == ' ') {
                //Postavi playera na mapu.
                player->positionX = j;
                player->positionY = i;
                return;
            }
        }
    }
}

struct Mine {
    int positionX;
    int positionY;
    int triggered;
};

struct Mine mines[MAX_MINES];

void initializeMines() {
    for (int i = 0; i < MAX_MINES; i++) {
        //Rand pozicije mina na mapi
        mines[i].positionX = rand() % 20;
        mines[i].positionY = rand() % 20;
        mines[i].triggered = 0;
    }
}

void checkMineCollisions(struct ChoosenCharacter *player) {
    extern int currentLevel;
    for (int i = 0; i < MAX_MINES; i++) {
        if (player->positionX == mines[i].positionX && player->positionY == mines[i].positionY && !mines[i].triggered) {
            player->health -= 200;
            mines[i].triggered = 1;

            //Sacuvaj trenutni map state prije kolizije sa minom
            char originalMap[20][20];
            for (int y = 0; y < 20; y++) {
                for (int x = 0; x < 20; x++) {
                    originalMap[y][x] = MazeMap[currentLevel][y][x];
                }
            }
            clearScreen();

            printMapWithMotionEffect(player, MazeMap[currentLevel]);

            //Restoraj mapu poslije kolizije
            for (int y = 0; y < 20; y++) {
                for (int x = 0; x < 20; x++) {
                    MazeMap[currentLevel][y][x] = originalMap[y][x];
                }
            }

            printf("You stepped on a mine! Be careful. Health: %d\n", player->health); //prikaz hp-a nakon kolizije

            Delay(2);
        }
    }
}


int hasCompletedLevel(struct ChoosenCharacter *player) {
    return hasReachedExit(player, MazeMap[currentLevel]);
}


int isGameOver(struct ChoosenCharacter *player) {
    return player->health <= 0;
}

void resetPlayerHealth(struct ChoosenCharacter *player) {

    if (strcmp(player->choosen_class, "warrior") == 0) {         //strcmp -> string compare.
        player->health = 2000;
    } else if (strcmp(player->choosen_class, "ninja") == 0) {
        player->health = 1250;
    } else if (strcmp(player->choosen_class, "thief") == 0) {
        player->health = 800;
    }
}

void resetGame(struct ChoosenCharacter *player) {
    initializePlayerPosition(player, MazeMap[0]);
    resetPlayerHealth(player);

    currentLevel = 0;
}

void printMapWithMotionEffect(struct ChoosenCharacter *player, char MazeMap[20][20]) {

    int visibleRange = 2;

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (j >= player->positionX - visibleRange &&
                j <= player->positionX + visibleRange &&
                i >= player->positionY - visibleRange &&
                i <= player->positionY + visibleRange) {

                if (i == player->positionY && j == player->positionX) {
                    printf("[%c]", player->choosen_class[0]);
                } else {
                    printf(" %c ", MazeMap[i][j]);
                }
            } else {
                printf("   ");
            }
        }
        printf("\n");
    }
}

void displayWelcomeMessage(int level) {
    char welcomeMessage[50];
    sprintf(welcomeMessage, "Welcome to Level %d, please wait...", level + 1);

    //Animacija s tackama
    for (int i = 0; i < 3; i++) {
        printf("%s", welcomeMessage);
        for (int j = 0; j < 3; j++) {
            printf(".");
            Delay(1);
        }
        clearScreen();
    }
    printf("%s\n", welcomeMessage);
}




#endif // ADVGAME_H_INCLUDED
