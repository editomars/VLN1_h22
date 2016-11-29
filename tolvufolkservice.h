#ifndef TOLVUFOLKSERVICE_H
#define TOLVUFOLKSERVICE_H

#include "skraarvinnsla.h"
#include "tolvufolk.h"
#include <vector>

class tolvufolkService
{
public:
    tolvufolkService();
    vector<tolvufolk> getTolvufolk() const;
    void addTolvufolk(const tolvufolk& t);
    void addTolvufolk(const vector<tolvufolk>& folk);
private:
    skraarvinnsla _dataaccess;
};

#endif // TOLVUFOLKSERVICE_H
