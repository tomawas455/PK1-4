#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameHelpers.h"
#include "additionalUtilities.h"

char* hidePassword(char *password)
{
    int passwordLength=strlen(password);
    char *hiddenPassword=malloc(sizeof(char)*(passwordLength+1));
    hiddenPassword[passwordLength]='\0';
    for(int i=0;i<passwordLength;i++)
        hiddenPassword[i]=(password[i]==' '?' ':'_');
    return hiddenPassword;
}

void printContestants(int *accounts,char (*players)[CONTESTANTS_NAME_MAX],int turn)
{
    printf("\n");
    for(int i=0;i<3;i++)
        printf("%s have: $%d%s\n",players[i],accounts[i],turn==i?" <<<":"\0");
}

int getTextLettersAmount(char *text,char empty)
{
    int amount=0;
    while(*text!='\0')
        if(*(text++)!=empty)
            amount++;
    return amount;
}

char getLetterOnPosition(char *text,int position)
{
    int i=0;
    while(*text!='\0')
        if(*(text)!=' '&&i++==position)
        {
            char tmp=*text;
            *text=' ';
            return tmp;
        }
        else
            text++;
    printf("something went wrong, let's continue pretending nothing happened...\n");
    return '\0';
}

void printNotUsedLetters(char *alphabet)
{
    printf("(");
    int first=1;
    while(*alphabet!='\0')
        if(*alphabet++!=' ')
            printf("%s%c",first-->0?"\0":", ",*(alphabet-1));
    printf(")\n");
}

int checkAgainstPassword(char *hiddenPassword,char *password,char guess)
{
    char *letter;
    int hits=0,len=strlen(password);
    while((letter=strchr(password,guess))!=NULL)
    {
        *(hiddenPassword+len-strlen(letter))=guess;
        password=letter+1;
        hits++;
    }
    if(!hits)
    {
        printf("letter \"%c\" does not exist in this word, sorry\n",guess);
        _continue();
    }
    return hits;
}

char getVowelDecision(void)
{
    printf("do you want to guess a vowel?\n(press y for yes, anything else for no)\n");
    char decision=_getch();
    if(decision!='y')
        return '\0';
    return decision;
}

void printWinners(int *accounts,char (*names)[CONTESTANTS_NAME_MAX],char *password,int lettersLeft)
{
    clearScreen();
    if(lettersLeft)
        printf("congratulations");
    else
        printf("game over");
    printf(", password was \"%s\"\n\n",password);
    for(int i=0;i<CONTESTANTS_AMOUNT;i++)
        printf("%s ended with $%d\n",names[i],accounts[i]);
    printf("\n");
    _continue();
}
