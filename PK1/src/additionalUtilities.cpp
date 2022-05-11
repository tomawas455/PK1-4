#include "additionalUtilities.h"
#include <iostream>

std::string &ltrim(std::string &str,const std::string characters)
{
    str.erase(0, str.find_first_not_of(characters));
    return str;
}

std::string &rtrim(std::string &str,const std::string characters)
{
    str.erase(str.find_last_not_of(characters)+1);
    return str;
}

std::string &trim(std::string &str,const std::string characters)
{
    return ltrim(rtrim(str));
}

bool startsWith(std::string &text,std::string prefix)
{
    return !text.rfind(prefix,0);
}

std::string toLowercase(std::string &text)
{
    for(char &c: text)
        c=toLowercase(c);
    return text;
}

char toLowercase(char c)
{
    if(c>='A'&&c<='Z')
        return c+32;
    return c;
}

std::ifstream openFile(std::string &filename)
{
    std::ifstream file;
    file.open(filename);
    if(!file)
        std::cout<<"file \""<<filename<<"\" does not exist"<<std::endl;
    return file;
}

std::string getDataFromFile(std::ifstream &file)
{
    std::string data;
    getline(file,data);
    return trim(data);
}
