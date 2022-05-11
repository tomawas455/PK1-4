#include "processCircuit.h"
#include "circuitBuilder.h"
#include "circuitChecker.h"
#include "circuitCalculator.h"
#include "cableContainerManager.h"
#include <iostream>

void processCircuit(std::string &circuitFilename,std::string &statusFilename,std::string &outputFilename)
{
    gate *gates=NULL;
    cable *cables=NULL;
    cableContainer *IO[]={NULL,NULL};
    std::ifstream files[2];
    getFiles(files,circuitFilename,statusFilename);
    if(filesOk(files))
        tryProcessingCircuit(files,gates,cables,IO,outputFilename);
    closeFiles(files);
    deleteElements(gates,cables,IO);
}

void getFiles(std::ifstream *files,std::string &circuitFilename,std::string &statusFilename)
{
    files[0]=openFile(circuitFilename);
    files[1]=openFile(statusFilename);
}

bool filesOk(std::ifstream *files)
{
    if(!files[0]||!files[1])
        return false;
    return true;
}

void tryProcessingCircuit(std::ifstream *files,gate *&gates,cable *&cables,cableContainer **IO,std::string &outputFilename)
{
    try
    {
        loadCircuitFromFile(files[0],gates,cables,IO);
        checkCircuit(gates,IO);
        calculateCircuitFromFile(files[1],gates,cables,IO,outputFilename);
    }
    catch(std::string exceptionText)
    {std::cout<<exceptionText<<std::endl;}
}

void closeFiles(std::ifstream *files)
{
    files[0].close();
    files[1].close();
}

void deleteElements(gate *&gates,cable *&cables,cableContainer **IO)
{
    deleteGates(gates);
    deleteCables(cables);
    for(int i=0;i<2;i++)
        removeCableContainers(IO[i]);
}

void deleteGates(gate *&gates)
{
    gate *working=gates;
    while(working)
    {
        working=working->next;
        delete gates;
        gates=working;
    }
}

void deleteCables(cable *&cables)
{
    cable *working=cables;
    while(working)
    {
        working=working->next;
        delete cables;
        cables=working;
    }
}
