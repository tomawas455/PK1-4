#include "cableCreator.h"
#include <stdexcept>
#include "cableContainerManager.h"

void createCables(cable *&cables,cableContainer *&gateConnectors,std::string data)
{
    int cableNumber,space;
    do{
        space=data.find(" ",data.find_first_not_of(" "));
        cableNumber=getCableNumber(data,space);
        addCable(cables,gateConnectors,cableNumber);
    }while(space!=std::string::npos);
}

int getCableNumber(std::string &data,int &space)
{
    std::string cableNumberString;
    cableNumberString=data.substr(0,space);
    data=data.substr(space+1);
    try{return std::stoi(cableNumberString);}
    catch(std::invalid_argument &exc)
    {throw cableNumberString+" is not a correct cable number, fix your file with circuit";}
}

void addCable(cable *&cables,cableContainer *&gateConnectors,int &cableNumber)
{
    cable *previousCable=NULL,*workingCable=cables;
    bool added;
    do{
        added=addedCable(cables,previousCable,workingCable,gateConnectors,cableNumber);
        updateCables(previousCable,workingCable,added);
    }while(!added);
}

bool addedCable(cable *&cables,cable *&previousCable,cable *&workingCable,cableContainer *&gateConnectors,int &cableNumber)
{
    if(!workingCable||workingCable->number==cableNumber)
    {
        placeCable(cables,previousCable,workingCable,gateConnectors,cableNumber);
        return true;
    }
    return false;
}

void placeCable(cable *&cables,cable *&previousCable,cable *&newCable,cableContainer *&gateConnectors,int &cableNumber)
{
    if(!cableIsPlaced(newCable,cableNumber))
        insertNewCable(cables,previousCable,newCable);
    addCableContainer(gateConnectors,newCable);
}

bool cableIsPlaced(cable *&newCable,int &cableNumber)
{
    if(!newCable)
    {
        newCable=createNewCable(cableNumber);
        return false;
    }
    return true;
}

cable *createNewCable(int &cableNumber)
{
    cable *newCable=new cable;
    newCable->number=cableNumber;
    newCable->status=false;
    newCable->next=NULL;
    return newCable;
}

void insertNewCable(cable *&cables,cable *&previousCable,cable *&newCable)
{
    if(previousCable)
        previousCable->next=newCable;
    else
        cables=newCable;
}

void updateCables(cable *&previousCable,cable *&workingCable,bool &added)
{
    if(!added)
    {
        previousCable=workingCable;
        workingCable=workingCable->next;
    }
}
