#include "gateCreator.h"
#include "additionalUtilities.h"

void createAndPlaceGate(gate *&gates,cableContainer *&gateConnectors,std::string data)
{
    gate *newGate=createNewGate(gates,gateConnectors,data);
    placeGate(gates,newGate);
}

gate *createNewGate(gate *&gates,cableContainer *&gateConnectors,std::string &data)
{
    gate *newGate=new gate;
    newGate->type=toLowercase(data);
    addGateConnectors(newGate,gateConnectors);
    return newGate;
}

void addGateConnectors(gate *&newGate,cableContainer *gateConnectors)
{
    for(int i=0;i<3;i++)
    {
        if(fasterOutput(newGate,gateConnectors->next,i))
            continue;
        newGate->connectors[i]=gateConnectors->connectedCable;
        gateConnectors=gateConnectors->next;
    }
}

bool fasterOutput(gate *&newGate,cableContainer *&container,int &i)
{
    if(i==1&&!container)
        return isNeg(newGate,i);
    return false;
}

bool isNeg(gate *&newGate,int &i)
{
    if(newGate->type=="neg")
    {
        newGate->connectors[i]=NULL;
        return true;
    }
    throw newGate->type+" must have 3 connectors - 2x in and 1x out";
}

void placeGate(gate *&gates,gate *&newGate)
{
    gate *previousGate=NULL,*workingGate=gates;
    bool added;
    do{
        added=addedGate(gates,previousGate,newGate,workingGate);
        updateGates(previousGate,workingGate,added);
    }while(!added);
}

bool addedGate(gate *&gates,gate *&previousGate,gate *&newGate,gate *&workingGate)
{
    if(!workingGate||workingGate->connectors[0]==newGate->connectors[2]\
                ||workingGate->connectors[1]==newGate->connectors[2])
    {
        insertGate(gates,previousGate,newGate,workingGate);
        return true;
    }
    return false;
}

void insertGate(gate *&gates,gate *&previousGate,gate *&newGate,gate *&workingGate)
{
    if(previousGate)
        previousGate->next=newGate;
    else
        gates=newGate;
    newGate->next=workingGate;
}

void updateGates(gate *&previousGate,gate *&workingGate,bool &added)
{
    if(!added)
    {
        previousGate=workingGate;
        workingGate=workingGate->next;
    }
}
