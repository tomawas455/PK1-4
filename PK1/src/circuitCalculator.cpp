#include "circuitCalculator.h"
#include <stdexcept>
#include <iostream>
#include "cableContainerManager.h"
#include "gatesLogic.h"

void calculateCircuitFromFile(std::ifstream &file,gate *&gates,cable *&cables,cableContainer **IO,std::string &outputFilename)
{
    std::string data;
    std::streambuf *buf;
    std::ofstream ofile;
    setOutputFileBuf(outputFilename,ofile,buf);
    std::ostream outputStream(buf);
    while(!file.eof())
    {
        data=getDataFromFile(file);
        if(data=="") continue;
        calculateCircuit(gates,cables,IO,data,outputStream);
    }
}

void setOutputFileBuf(std::string &filename,std::ofstream &file,std::streambuf *&buf)
{
    if(outputFileHasName(filename,buf))
    {
        file.open(filename);
        buf=file.rdbuf();
    }
}

bool outputFileHasName(std::string &filename,std::streambuf *&buf)
{
    if(filename=="")
    {
        std::cout<<"missing output file - will print answer to standard output:";
        std::cout<<std::endl<<std::endl;
        buf=std::cout.rdbuf();
        return false;
    }
    return true;
}

void calculateCircuit(gate *&gates,cable *&cables,cableContainer **IO,std::string &data,std::ostream &ofile)
{
    try{setCircuitIns(IO[0],data);}
    catch(std::string exc)
    {
        std::cout<<exc<<std::endl;
        ofile<<exc<<std::endl;
        return;
    }
    calculateGatesOuts(gates);
    printToFile(IO,data,ofile);
}

void setCircuitIns(cableContainer *&ins,std::string &data)
{
    int space,cableNumber;
    bool status;
    std::string workingData=data;
    do
    {
        space=workingData.find(" ");
        try{getCableNumberAndStatus(workingData,space,cableNumber,status);}
        catch(std::string exc){throw exc+" in line \""+data+"\"";}
        setCableStatus(ins,cableNumber,status);
    }while(space!=std::string::npos);
}

void getCableNumberAndStatus(std::string &data,int &space,int &cableNumber,bool &status)
{
    int colon=data.find(":");
    try
    {
        cableNumber=std::stoi(data.substr(0,colon));
        status=std::stoi(data.substr(colon+1));
    }
    catch(std::invalid_argument &exc)
    {throw std::string("something is wrong");}
    data=data.substr(space+1);
}

void setCableStatus(cableContainer *ins,int &cableNumber,bool &status)
{
    while(ins)
    {
        if(changedCable(ins,cableNumber,status))
            return;
        ins=ins->next;
    }
    throw std::to_string(cableNumber)+" is not correct input to this circuit";
}

bool changedCable(cableContainer *&working,int &cableNumber,bool &status)
{
    if(working->connectedCable->number==cableNumber)
    {
        working->connectedCable->status=status;
        return true;
    }
    return false;
}

void calculateGatesOuts(gate *gates)
{
    while(gates)
    {
        calculateGate(gates);
        gates=gates->next;
    }
}

void calculateGate(gate *&working)
{
    std::string gateType=working->type;
    if(gateType=="neg")
        NEG(working);
    else if(gateType=="and")
        AND(working);
    else if(gateType=="nand")
        NAND(working);
    else if(gateType=="or")
        OR(working);
    else if(gateType=="nor")
        NOR(working);
    else if(gateType=="xor")
        XOR(working);
    else if(gateType=="xnor")
        XNOR(working);
    else
        throw gateType+" gate does not exist!";
}

void printToFile(cableContainer **IO,std::string &data,std::ostream &ofile)
{
    for(int i=0;i<2;i++)
        printIOStatus(IO[i],ofile);
    ofile<<std::endl;
}

void printIOStatus(cableContainer *connectors,std::ostream &ofile)
{
    while(connectors)
    {
        ofile<<connectors->connectedCable->number<<":";
        ofile<<connectors->connectedCable->status<<" ";
        connectors=connectors->next;
    }
}
