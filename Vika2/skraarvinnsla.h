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

    void baetaVid(const tolvufolk& folk); //Bætir tilviki af tölvufólki aftast í textaskrá
    void skrifa(const tolvufolk& folk); //Yfirskrifar textaskrá með tilviki af tolvufólki
    vector<tolvufolk> lesa() const; //Les textaksrá og skilar sem vector
    void eyda(); //Eyðir textaskrá
};

#endif // SKRAARVINNSLA_H
