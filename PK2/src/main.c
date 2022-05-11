#include <stdlib.h>
#include <time.h>
#include "additionalUtilities.h"
#include "structures.h"
#include "mainMenu.h"
#include "initializeGame.h"
#include "playGame.h"

int main(void)
{
    gameStates state=MENU_STATE;
    wheelField *wheel=NULL;
    int maxWeight=0;
    char password[200];
    srand(time(NULL));
    while(state!=EXIT_STATE)
    {
        switch(state)
        {
            case MENU_STATE:
                state=mainMenu();
                break;
            case INITIALIZE_GAME_STATE:
                state=initializeGame(&wheel,&maxWeight,password);
                break;
            case GAME_STATE:
                playGame(wheel,maxWeight,password);
                state=MENU_STATE;
                break;
        }
    }
    if(wheel)
        freeWheel(wheel);
    return 0;
}
