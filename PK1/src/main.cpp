/** @file */
#include "commandlineParser.h"
#include "processCircuit.h"
#include <string>
#include <iostream>

/** Funkcja main.
 * @param argsAmount liczba argumentów przekazanych do programu.
 * @param arguments argumenty przekazane do programu.
 */
int main(int argsAmount,char **arguments)
{
    std::string cfile,sfile,ofile;
    if(parseCommandline(argsAmount,arguments,cfile,sfile,ofile))
        processCircuit(cfile,sfile,ofile);
    return 0;
}
