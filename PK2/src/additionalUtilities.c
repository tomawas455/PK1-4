#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "additionalUtilities.h"
#if defined WIN32  || defined _WIN32  || defined __WIN32__ || defined __NT__
#include <conio.h>
#include "dirent.h"
#define CLEAR_COMMAND "cls"
#else
#include <dirent.h>
#include <stdio.h>
#include <termios.h>
#define CLEAR_COMMAND "clear"

static struct termios old, current;
void initTermios(void)
{
    tcgetattr(0, &old); /* grab old terminal i/o settings */
    current = old; /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    current.c_lflag &= ~ECHO; /* set no echo mode */
    tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}
char getch(void)
{
    char ch;
    initTermios();
    ch = getchar();
    resetTermios();
    return ch;
}
#endif

char _getch(void)
{
    return tolower(getch());
}

void clearScreen(void)
{
    system(CLEAR_COMMAND);
}

int getFilesNames(char **names,char *path)
{
    free(*names);
    *names=NULL;
    int amount=0;
    DIR *dir=opendir(path);
    if(dir)
    {
        struct dirent *f;
        while((f=readdir(dir))!=NULL)
            if(strcmp(f->d_name,".")&&strcmp(f->d_name,".."))
            {
                *names=realloc(*names,MAX_FILENAME_LENGTH*sizeof(char)*(++amount));
                strcpy((*names+(amount-1)*MAX_FILENAME_LENGTH),f->d_name);
            }
        closedir(dir);
    }
    return amount;
}

void _continue(void)
{
    printf("(press anything to continue...)\n");
    _getch();
}

void makeLowercase(char *text)
{
    int len=strlen(text);
    while(*text!='\0')
    {
        *text=tolower(*text);
        text++;
    }
}

void freeWheel(wheelField *wheel)
{
    wheelField *tmp;
    while(wheel)
    {
        tmp=wheel->next;
        free(wheel);
        wheel=tmp;
    }
}
