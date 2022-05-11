#include "commandlineParser.h"
#include <iostream>

bool parseCommandline(int &argsAmount,char **arguments,std::string &cFile,std::string &sFile,std::string &oFile)
{
    getFiles(argsAmount,arguments,cFile,sFile,oFile);
    if(!correctFiles(cFile,sFile))
        return false;
    return true;
}

void getFiles(int &argsAmount,char **arguments,std::string &cFile,std::string &sFile,std::string &oFile)
{
    std::string *filenames[]={&cFile,&sFile,&oFile};
    std::string options[]={"-u","-i","-o"};
    std::string *currentFile=NULL;
    for(int i=1;i<argsAmount;i++)
    {
        std::string argument(arguments[i]);
        if(!editedFile(currentFile,argument))
            setFileToEdit(filenames,options,currentFile,argument);
    }
}

bool editedFile(std::string *&currentFile,std::string &text)
{
    if(currentFile)
    {
        *currentFile=text;
        currentFile=NULL;
        return true;
    }
    return false;
}

void setFileToEdit(std::string *filenames[],std::string options[3],std::string *&currentFile,std::string &argument)
{
    for(int j=0;j<3;j++)
        if(argument==options[j])
            currentFile=filenames[j];
}

bool correctFiles(std::string &cFile,std::string &sFile)
{
    if(cFile==""||sFile=="")
    {
        std::cout<<"arguments missing file with circuit or with inputs"<<std::endl;
        return false;
    }
    return true;

}
