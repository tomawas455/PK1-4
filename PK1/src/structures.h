/** @file */
#ifndef STRUCTURES
#define STRUCTURES
#include <string>

struct cable
{
    int number;
    bool status;
    cable *next;
};

struct cableContainer
{
    cable *connectedCable;
    cableContainer *next;
};

struct gate
{
    std::string type;
    cable *connectors[3];///<in in out
    gate *next;
};
#endif
