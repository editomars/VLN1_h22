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
    vector<tolvufolk> getTolvufolk(bool readFromDatabase); //Skilar vectornum af gögnum sem notandi er að nota, vantar params
    void addTolvufolk(const tolvufolk& t); //Bætir við einu tilviki af tolvufolk í vectorinn (ekki í gagnagrunn)
    void appendTolvufolk(const tolvufolk& t); //Bætir við einu tilvik af tolvufolk (append í gagnagrunn)
    void appendTolvufolk(const vector<tolvufolk>& folk); //Bætir við vector af tolvufolk (append í gagnagrunn)
    void writeTolvufolk(const tolvufolk& t); //Yfirskrifar gögnin á undan með einu tilviki af tolvufólk
    void writeTolvufolk(const vector<tolvufolk>& folk); //Yfiskrifar gögnin á undan með nýjum gögnum, vector af fólki
    void deleteTolvufolk(); //Eyðir öllum gögnum
    void deleteSingleTolvufolk(int nr); //Eyðir stykki af tölvufólk í vector
    void sortByName();
private:
    skraarvinnsla _dataaccess;
    vector<tolvufolk> _folk;
};

#endif // TOLVUFOLKSERVICE_H
