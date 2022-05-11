#include <stdio.h>
#include "mainMenu.h"
#include "additionalUtilities.h"

gameStates mainMenu(void)
{
    char *options[MENU_OPTIONS]={"Start","Exit"};
    int selectedOption=0;
    char pressed;
    do
    {
        printMenu(selectedOption,options);
        pressed=_getch();
        if(!changeSelected(pressed,&selectedOption)&&pressed==10)
            return exitMenu(selectedOption);
    }while(pressed!=10||selectedOption!=MENU_OPTIONS-1);
    return EXIT_STATE;
}

void printMenu(int selectedOption,char *options[MENU_OPTIONS])
{
    clearScreen();
    printf("WHEEL OF FORTUNE\n\n");
    for(int i=0;i<MENU_OPTIONS;i++)
    {
        if(selectedOption==i)
            printf("-> ");
        printf("%s\n",options[i]);
    }
    printf("\n(use \"w\" and \"s\" to move up and down)\n");
}

int changeSelected(char pressed,int *selectedOption)
{
    if(pressed=='w')
    {
        if(*selectedOption<=0)
            *selectedOption=MENU_OPTIONS-1;
        else
            (*selectedOption)--;
    }
    else if(pressed=='s')
    {
        if(*selectedOption>=MENU_OPTIONS-1)
            *selectedOption=0;
        else
            (*selectedOption)++;
    }
    else
        return 0;
    return 1;
}

gameStates exitMenu(int selectedOption)
{
    switch(selectedOption)
    {
        case MENU_OPTIONS-1:
            return EXIT_STATE;
        case 0:
            return INITIALIZE_GAME_STATE;
    }
}
