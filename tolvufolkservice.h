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
private:
    skraarvinnsla _dataaccess;
};

#endif // TOLVUFOLKSERVICE_H
