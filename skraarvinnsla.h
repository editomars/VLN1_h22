#ifndef SKRAARVINNSLA_H
#define SKRAARVINNSLA_H

#include <vector>
#include "tolvufolk.h"

class skraarvinnsla
{
public:
    skraarvinnsla();
    void writeToFile(tolvufolk folk);
    vector<tolvufolk> readToFile();
};

#endif // SKRAARVINNSLA_H
