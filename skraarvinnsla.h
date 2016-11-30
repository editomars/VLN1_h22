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
    void baetaVidIskra(const tolvufolk& folk); //Bætir tilviki af tölvufólki aftast í textaskrá
    void skrifaIskra(const tolvufolk& folk); //Yfirskrifar textaskrá með tilviki af tolvufólki
    vector<tolvufolk> lesaSkra() const; //Les textaksrá og skilar sem vector
    void eydaSkra(); //Eyðir textaskrá
};

#endif // SKRAARVINNSLA_H
