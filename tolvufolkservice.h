#ifndef TOLVUFOLKSERVICE_H
#define TOLVUFOLKSERVICE_H

#include "skraarvinnsla.h"
#include "tolvufolk.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class tolvufolkService
{
public:
    tolvufolkService();
<<<<<<< HEAD
    vector<tolvufolk> getTolvufolk();
    void addTolvufolk(const tolvufolk& t);
    void addTolvufolk(const vector<tolvufolk>& folk);
    void deleteTolvufolk();
    vector<tolvufolk> sortByName();
    void displayVector(vector<tolvufolk> folk);
=======
    vector<tolvufolk> getTolvufolk(bool readFromDatabase); //Skilar vectornum af gögnum sem notandi er að nota, vantar params
    void addTolvufolk(const tolvufolk& t); //Bætir við einu tilviki af tolvufolk í vectorinn (ekki í gagnagrunn)
    void appendTolvufolk(const tolvufolk& t); //Bætir við einu tilvik af tolvufolk (append í gagnagrunn)
    void appendTolvufolk(const vector<tolvufolk>& folk); //Bætir við vector af tolvufolk (append í gagnagrunn)
    void writeTolvufolk(const tolvufolk& t); //Yfirskrifar gögnin á undan með einu tilviki af tolvufólk
    void writeTolvufolk(const vector<tolvufolk>& folk); //Yfiskrifar gögnin á undan með nýjum gögnum, vector af fólki
    void deleteTolvufolk(); //Eyðir gögnum
    void sortByName();
>>>>>>> 84f0b8959643ec8d1815939c546d517d452940d9
private:
    skraarvinnsla _dataaccess;
    vector<tolvufolk> _folk;
};

#endif // TOLVUFOLKSERVICE_H
