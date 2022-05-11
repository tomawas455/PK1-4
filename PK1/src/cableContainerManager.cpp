#include "cableContainerManager.h"

void addCableContainer(cableContainer *&containers,cable *&cableToAdd)
{
    cableContainer *working=containers;
    bool added;
    do
    {
        added=addedContainer(containers,working,cableToAdd);
        if(!added)
            working=working->next;
    }while(!added);
}

bool addedContainer(cableContainer *&containers,cableContainer *&working,cable *&cableToAdd)
{
    if(!containers)
        containers=createNewCableContainer(cableToAdd);
    else if(!working->next)
        working->next=createNewCableContainer(cableToAdd);
    else
        return false;
    return true;
}

cableContainer *createNewCableContainer(cable *&cableToAdd)
{
    cableContainer *newContainer=new cableContainer;
    newContainer->connectedCable=cableToAdd;
    newContainer->next=NULL;
    return newContainer;
}

void removeCableContainers(cableContainer *&container)
{
    cableContainer *working=container;
    while(working)
    {
        working=working->next;
        delete container;
        container=working;
    }
}
