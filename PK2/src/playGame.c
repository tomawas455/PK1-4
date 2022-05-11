#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "playGame.h"
#include "additionalUtilities.h"
#include "gameHelpers.h"

void playGame(wheelField *wheel,int maxWeight,char *password)
{
    int accounts[CONTESTANTS_AMOUNT]={0,0,0},i=0,lettersLeft;
    char names[CONTESTANTS_AMOUNT][CONTESTANTS_NAME_MAX]={"you","bot1","bot2"};
    char *hiddenPassword=hidePassword(password);
    char alphabet[2][CONSONANTS]={"aeiouy","bcdfghjklmnprstvwxz"};
    while(strcmp(hiddenPassword,password)&&(lettersLeft=getTextLettersAmount(alphabet[1],' ')))
    {
        clearScreen();
        printf("password: %s\n",hiddenPassword);
        printContestants(accounts,names,i);
        action(hiddenPassword,password,accounts+i,wheel,maxWeight,alphabet,names[i],i);
        i=(i>=2?0:i+1);
    }
    free(hiddenPassword);
    printWinners(accounts,names,password,lettersLeft);
}

void action(char *hiddenPassword,char *password,int *account,wheelField *wheel,int maxWeight,char (*alphabet)[CONSONANTS],char *whom,int isBot)
{
    actionStates actionState=SPIN;
    wheelField *field;
    do
    {
        switch(actionState)
        {
            case SPIN:
                field=spinWheel(wheel,maxWeight);
                actionState=DECIDE;
                break;
            case DECIDE:
                actionState=actionDecision(hiddenPassword,password,account,field,whom,alphabet[1],isBot);
                break;
            case VOWEL:
                actionState=vowelGuess(hiddenPassword,password,account,alphabet[0]);
                break;
            case SOLVE:
                letSolvePuzzle(hiddenPassword,password,isBot);
                actionState=EXIT;
                break;
        }
    }while(actionState!=EXIT&&strcmp(password,hiddenPassword));
}

wheelField* spinWheel(wheelField *wheel,int weight)
{
    printf("press anything to spin the wheel\n");
    _getch();
    clearScreen();
    int picked=rand()%weight;
    wheelField *prev;
    while(picked>=0)
    {
        picked-=wheel->weight;
        prev=wheel;
        wheel=wheel->next;
    }
    printf("wheel stopped at: %s\n\n",prev->name);
    return prev;
}

actionStates actionDecision(char *hiddenPassword,char *password,int *account,wheelField *field,char *whom,char *alphabet,int isBot)
{
    switch(field->value)
    {
        case -2:
            bankrupt(account,whom);
            break;
        case -1:
            stop(whom);
            break;
        default:
            return guess(hiddenPassword,password,account,field,whom,alphabet,isBot);
    }
    return EXIT;
}

void bankrupt(int *account,char *whom)
{
    printf("%s go bankrupt, sorry!\n",whom);
    *account=0;
    _continue();
}

void stop(char *whom)
{
    printf("%s don't have a chance to guess, sorry\n",whom);
    _continue();
}

actionStates guess(char *hiddenPassword,char *password,int *account,wheelField *field,char *whom,char *alphabet,int isBot)
{
    if(!getTextLettersAmount(alphabet,' '))
        return EXIT;
    printf("password: %s\n\n",hiddenPassword);
    int hits=makeGuess(hiddenPassword,password,field->value,account,alphabet,whom,isBot);
    if(!hits)
        return EXIT;
    clearScreen();
    printf("password: %s\n\n",hiddenPassword);
    printf("%s have got $%d and in total have $%d\n\n",whom,(field->value)*hits,*account);
    return nextGuess(hiddenPassword,password,whom,isBot);
}

int makeGuess(char *hiddenPassword,char *password,int hitValue,int *account,char *alphabet,char *whom,int isBot)
{
    char guess=isBot?getRandomGuess(alphabet,whom):getPlayerGuess(alphabet);
    if(guess=='\0')
        return 0;
    printf("guessed letter: \"%c\"\n",guess);
    _continue();
    int hits=checkAgainstPassword(hiddenPassword,password,guess);
    *account+=hitValue*hits;
    return hits;
}

char getRandomGuess(char *alphabet,char *whom)
{
    int maxGuess=getTextLettersAmount(alphabet,' ');
    if(!maxGuess)
    {
        printf("%s cannot pick a letter, because no letter left to guess!\n",whom);
        _continue();
        return '\0';
    }
    return getLetterOnPosition(alphabet,rand()%maxGuess);
}

char getPlayerGuess(char *alphabet)
{
    printf("write a letter you want to guess\n");
    printNotUsedLetters(alphabet);
    char guess=_getch(),*p=strchr(alphabet,guess);
    if(!p)
    {
        printf("you cannot guess that, your turn is skipped\n");
        _continue();
        return '\0';
    }
    *p=' ';
    return guess;
}

actionStates nextGuess(char *hiddenPassword,char *password,char *whom,int isBot)
{
    if(!strcmp(password,hiddenPassword))return EXIT;
    if(isBot)
        return processBotNextGuess(hiddenPassword,whom);
    printf("do you want to spin again?\n(y for yes, anything else for no)\n");
    char decision=_getch();
    clearScreen();
    if(decision=='y')
        return SPIN;
    return VOWEL;
}

actionStates processBotNextGuess(char *hiddenPassword,char *whom)
{
    int chance=100*(double)getTextLettersAmount(hiddenPassword,'_')/strlen(hiddenPassword);
    int choice=rand()%100;
    if(choice<chance)
    {
        _continue();
        return SOLVE;
    }
    printf("%s decides to spin again\n",whom);
    _continue();
    return SPIN;
}

actionStates vowelGuess(char *hiddenPassword,char *password,int *account,char *alphabet)
{
    if(makeVowelGuess(hiddenPassword,password,account,alphabet))
        return EXIT;
    return SOLVE;
}

int makeVowelGuess(char *hiddenPassword,char *password,int *account,char *alphabet)
{
    while(*account>=250)
    {
        if(!strcmp(password,hiddenPassword))
            return 1;
        if(!(getTextLettersAmount(alphabet,' '))||getVowelDecision()=='\0')
            return 0;
        clearScreen();
        printf("password: %s\n\n",hiddenPassword);
        char decision=getPlayerGuess(alphabet);
        if(decision=='\0')
            return 1;
        checkAgainstPassword(hiddenPassword,password,decision);
        *account-=250;
        clearScreen();
        printf("you have paid $250 and in total have $%d\n\n",*account);
        printf("password: %s\n",hiddenPassword);
        _continue();
    }
    return 0;
}

void letSolvePuzzle(char *hiddenPassword,char *password,int isBot)
{
    clearScreen();
    printf("password: %s\n\n",hiddenPassword);
    if(isBot)
        checkBotSolution(hiddenPassword,password);
    else
        letPlayerSolvePuzzle(hiddenPassword,password);
}

void checkBotSolution(char *hiddenPassword,char *password)
{
    printf("contestant decides to guess solution...\n");
    _continue();
    if(!(rand()%BOT_GUESS_CHANCE))
        strcpy(hiddenPassword,password);
    else
    {
        printf("... but failes!\n");
        _continue();
    }
}

void letPlayerSolvePuzzle(char *hiddenPassword,char *password)
{
    int len=strlen(password);
    char *guess=malloc((len+1)*2*sizeof(char));
    printf("do you want to try to solve puzzle?\n(y for yes, anything else for no)\n");
    if(_getch()!='y')
        return;
    printf("what do you think password is?\n");
    fgets(guess,sizeof(char)*2*(len+1),stdin);
    char *p=(guess+strlen(guess)-1);
    if(*p=='\n')
        *p='\0';
    checkPlayerSolution(hiddenPassword,password,guess);
    free(guess);
}

void checkPlayerSolution(char *hiddenPassword,char *password,char *guess)
{
    makeLowercase(guess);
    if(strcmp(guess,password))
    {
        printf("you got it wrong, sorry.");
        _continue();
    }
    else
        strcpy(hiddenPassword,password);
}
