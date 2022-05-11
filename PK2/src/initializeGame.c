#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "initializeGame.h"
#include "additionalUtilities.h"

gameStates initializeGame(wheelField **wheel,int *maxWeight,char *password)
{
    clearScreen();
    clearWheel(wheel,maxWeight);
    if(!createWheel(wheel,maxWeight)||!getPassword(password))
    {
        printf("\nsomething went wrong\n(press any key to return to menu...)\n");
        _getch();
        return MENU_STATE;
    }
    printWheel(*wheel);
    return GAME_STATE;
}

void clearWheel(wheelField **wheel,int *maxWeight)
{
    if(*wheel)
    {
        freeWheel(*wheel);
        *wheel=NULL;
        *maxWeight=0;
    }
}

int createWheel(wheelField **wheel,int *maxWeight)
{
    char *names=NULL,filename[MAX_FILENAME_LENGTH+17];
    int amount=getFilesNames(&names,"data/wheelFields"),success=1;
    for(int i=0;i<amount;i++)
    {
        sprintf(filename,"data/wheelFields/%s",(names+i*MAX_FILENAME_LENGTH));
        success=processFile(filename,wheel,maxWeight);
        if(!success)
            break;
    }
    free(names);
    return success;
}

int processFile(char *filename,wheelField **wheel,int *maxWeight)
{
    FILE *file=fopen(filename,"r");
    if(!file)
    {
        printf("invalid file: %s\n",filename);
        return 0;
    }
    wheelField *tmp=malloc(sizeof(wheelField));
    tmp->next=*wheel;
    *wheel=tmp;
    if(!readFile(file,*wheel))
        return 0;
    *maxWeight+=(*wheel)->weight;
    return 1;
}

int readFile(FILE *file,wheelField *field)
{
    int fail=0;
    char line[200];
    while(fgets(line,sizeof(char)*200,file))
        if(!loadNameAndValue(line,field))
            fail=1;
    fclose(file);
    if(fail||!(field->weight&&field->value)||!setFieldName(field))
        return 0;
    return 1;
}

int loadNameAndValue(char *name,wheelField *field)
{
    int value=0;
    makeLowercase(name);
    getNameAndValue(name,&value);
    if(value&&!setWheelField(field,name,value))
        return 0;
    return 1;
}

void getNameAndValue(char *name,int *value)
{
    char *separator=strchr(name,'=');
    if(separator)
    {
        *value=strtol(separator+1,NULL,10);
        *separator='\0';
    }
}

int setWheelField(wheelField *field,char *name,int value)
{
    if(!strcmp(name,"value"))
        field->value=value;
    else if(!strcmp(name,"weight"))
    {
        if(value>0)
            field->weight=value;
        else
        {
            printf("invalid weight: %d\n",value);
            return 0;
        }
    }
    else
    {
        printf("invalid field: %s\n",name);
        return 0;
    }
    return 1;
}

int setFieldName(wheelField *field)
{
    switch(field->value)
    {
        case -2:
            strcpy(field->name,"bankrupt");
            break;
        case -1:
            strcpy(field->name,"stop");
            break;
        default:
            if(field->value<=0)
            {
                printf("invalid value: %d\n",field->value);
                return 0;
            }
            sprintf(field->name,"$%d",field->value);
    }
    return 1;
}

int getPassword(char *pass)
{
    char filename[MAX_FILENAME_LENGTH+16];
    getPasswordFilename(filename);
    FILE *file=fopen(filename,"r");
    if(!file)
        return 0;
    char *passwords=NULL;
    int passwordsAmount=readPasswordsFromFile(file,&passwords);
    if(!passwordsAmount)
        return 0;
    strcpy(pass,passwords+(rand()%passwordsAmount)*200);
    free(passwords);
    fclose(file);
    return 1;
}

void getPasswordFilename(char *filename)
{
    char *tmp=NULL;
    int amount=getFilesNames(&tmp,"data/passwords");
    sprintf(filename,"data/passwords/%s",tmp+MAX_FILENAME_LENGTH*(rand()%amount));
    free(tmp);
}

int readPasswordsFromFile(FILE *file,char **passwords)
{
    char password[200];
    int passwordsAmount=0;
    while(fgets(password,sizeof(char)*200,file))
    {
        makeLowercase(password);
        char *newline=(password+strlen(password)-1);
        if(*newline=='\n')
            *newline='\0';
        *passwords=realloc(*passwords,200*sizeof(char)*(++passwordsAmount));
        strcpy((*passwords)+(passwordsAmount-1)*200,password);
    }
    return passwordsAmount;
}

void printWheel(wheelField *wheel)
{
    printf("loaded wheel fields:\n\n");
    while(wheel)
    {
        printf("%s: value=%d weight=%d\n",wheel->name,wheel->value,wheel->weight);
        wheel=wheel->next;
    }
    printf("\n");
    _continue();
}
