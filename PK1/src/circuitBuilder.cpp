#include "circuitBuilder.h"
#include <iostream>
#include "ioAdder.h"
#include "cableCreator.h"
#include "gateCreator.h"
#include "additionalUtilities.h"
#include "cableContainerManager.h"

void loadCircuitFromFile(std::ifstream &file,gate *&gates,cable *&cables,cableContainer **IO)
{
    std::string data;
    while(!file.eof())
    {
        data=getDataFromFile(file);
        if(data=="") continue;
        createCablesAndGateFromData(gates,cables,IO,data);
    }
}

void createCablesAndGateFromData(gate *&gates,cable *&cables,cableContainer **IO,std::string &data)
{
    cableContainer *gateConnectors=NULL;
    int space=data.find(" ");
    createCables(cables,gateConnectors,data.substr(space+1));
    createGate(gates,gateConnectors,IO,data.substr(0,space));
}

void createGate(gate *&gates,cableContainer *&gateConnectors,cableContainer **IO,std::string gateName)
{
    std::string error="";
    if(gateName=="IN:")
        addIO(IO[0],gateConnectors);
    else if(gateName=="OUT:")
        addIO(IO[1],gateConnectors);
    else
    {
        error=tryToCreateGate(gates,gateConnectors,gateName);
        removeCableContainers(gateConnectors);
    }
    if(error!="") throw error;
}

std::string tryToCreateGate(gate *&gates,cableContainer *&gateConnectors,std::string &gateName)
{
    std::string error="";
    try
    {
        createAndPlaceGate(gates,gateConnectors,gateName);
    }
    catch(std::string exc)
    {error=exc;}
    return error;
}
