#include "ioAdder.h"

void addIO(cableContainer *&connectors,cableContainer *&connectorsToAdd)
{
    if(!emptyConnectors(connectors,connectorsToAdd))
        while(connectorsToAdd)
            addConnector(connectors,connectorsToAdd);
}

bool emptyConnectors(cableContainer *&connectors,cableContainer *&connectorsToAdd)
{
    if(!connectors)
    {
        connectors=connectorsToAdd;
        return true;
    }
    return false;
}

void addConnector(cableContainer *&connectors,cableContainer *&connectorToAdd)
{
    cableContainer *previous=NULL,*working=connectors;
    bool added;
    do
    {
        added=addedIO(previous,working,connectorToAdd);
        updateContainers(added,previous,working);
    }while(!added);
}

bool addedIO(cableContainer *&previous,cableContainer *&working, cableContainer *&connectorToAdd)
{
    if(!working)
        addNewConnector(previous,connectorToAdd);
    else if(working->connectedCable==connectorToAdd->connectedCable)
        updateAndDeleteConnector(connectorToAdd);
    else return false;
    return true;
}

void addNewConnector(cableContainer *&previous,cableContainer *&connectorToAdd)
{
    previous->next=connectorToAdd;
    connectorToAdd=connectorToAdd->next;
    previous->next->next=NULL;
}

void updateAndDeleteConnector(cableContainer *&connector)
{
    cableContainer *x=connector;
    connector=connector->next;
    delete x;
}

void updateContainers(bool &noUpdate,cableContainer *&previous,cableContainer *&working)
{
    if(!noUpdate)
    {
        previous=working;
        working=working->next;
    }
}
