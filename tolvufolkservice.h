#ifndef TOLVUFOLKSERVICE_H
#define TOLVUFOLKSERVICE_H

#include "skraarvinnsla.h"
#include "tolvufolk.h"
#include <vector>
#include <algorithm>

using namespace std;

class tolvufolkService
{
public:
    tolvufolkService();
    vector<tolvufolk> getTolvufolk();
    void addTolvufolk(const tolvufolk& t);
    void addTolvufolk(const vector<tolvufolk>& folk);
    //void sortByName(const vector<tolvufolk>& folk);
private:
    skraarvinnsla _dataaccess;
    vector<tolvufolk> _folk;
};

#endif // TOLVUFOLKSERVICE_H
