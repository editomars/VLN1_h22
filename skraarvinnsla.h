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
    void appendToFile(const tolvufolk& folk);
    void writeToFile(const tolvufolk& folk);
    vector<tolvufolk> readToFile() const;
    void deleteFile();
};

#endif // SKRAARVINNSLA_H
