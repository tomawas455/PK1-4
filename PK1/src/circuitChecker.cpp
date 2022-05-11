#include "circuitChecker.h"
#include <string>

void checkCircuit(gate *&gates,cableContainer **IO)
{
    gate *working=gates;
    while(working)
    {
        checkGateOut(working->next,working,IO[0]);
        working=working->next;
    }
}

void checkGateOut(gate *&gates,gate *&workingGate,cableContainer *ins)
{
    checkGateWithCircuitIns(workingGate,ins);
    checkOtherGatesOuts(gates,workingGate);
}

void checkGateWithCircuitIns(gate *&workingGate,cableContainer *ins)
{
    while(ins)
    {
        if(ins->connectedCable==workingGate->connectors[2])
            throw "circuit with number "+std::to_string(ins->connectedCable->number)+" is also output of atleast one gate, change that.";
        ins=ins->next;
    }
}

void checkOtherGatesOuts(gate *gates,gate *&workingGate)
{
    while(gates)
    {
        if(gates->connectors[2]==workingGate->connectors[2])
            throw "connector number "+std::to_string(workingGate->connectors[2]->number)+" is output of two different gates";
        gates=gates->next;
    }
}
