#include "gatesLogic.h"

bool NEG(gate *&calculationGate)
{
    bool status=!calculationGate->connectors[0]->status;
    calculationGate->connectors[2]->status=status;
    return status;
}

bool AND(gate *&calculationGate)
{
    bool status=(calculationGate->connectors[0]->status\
                &&calculationGate->connectors[1]->status);
    calculationGate->connectors[2]->status=status;
    return status;
}

bool NAND(gate *&calculationGate)
{
    bool status=!AND(calculationGate);
    calculationGate->connectors[2]->status=status;
    return status;
}

bool OR(gate *&calculationGate)
{
    bool status=(calculationGate->connectors[0]->status\
                ||calculationGate->connectors[1]->status);
    calculationGate->connectors[2]->status=status;
    return status;
}

bool NOR(gate *&calculationGate)
{
    bool status=!OR(calculationGate);
    calculationGate->connectors[2]->status=status;
    return status;
}

bool XOR(gate *&calculationGate)
{
    bool status=((!calculationGate->connectors[0]->status\
                    &&calculationGate->connectors[1]->status)\
                 ||(calculationGate->connectors[0]->status\
                    &&!calculationGate->connectors[1]->status));
    calculationGate->connectors[2]->status=status;
    return status;
}

bool XNOR(gate *&calculationGate)
{
    bool status=!XOR(calculationGate);
    calculationGate->connectors[2]->status=status;
    return status;
}
