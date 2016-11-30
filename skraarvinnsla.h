#ifndef SKRAARVINNSLA_H
#define SKRAARVINNSLA_H

#include <vector>
#include <fstream>
#include "tolvufolk.h"
#include <stdio.h>

class skraarvinnsla
{
public:
    skraarvinnsla();
    void appendToFile(const tolvufolk& folk); //Bætir tilviki af tölvufólki aftast í textaskrá
    void writeToFile(const tolvufolk& folk); //Yfirskrifar textaskrá með tilviki af tolvufólki
    vector<tolvufolk> readToFile() const; //Les textaksrá og skilar sem vector
    void deleteFile(); //Eyðir textaskrá
};

#endif // SKRAARVINNSLA_H
