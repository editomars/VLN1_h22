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
    vector<tolvufolk> getTolvufolk(bool lesaUrGagnagrunni); //Skilar vectornum af gögnum sem notandi er að nota, vantar params
    void baetaVidTolvufolk(const tolvufolk& t); //Bætir við einu tilviki af tolvufolk í vectorinn (ekki í gagnagrunn)
    void vidbotarTolvufolk(const tolvufolk& t); //Bætir við einu tilvik af tolvufolk (append í gagnagrunn)
    void vidbotarTolvufolk(const vector<tolvufolk>& folk); //Bætir við vector af tolvufolk (append í gagnagrunn)
    void yfirskrifaTolvufolk(const tolvufolk& t); //Yfirskrifar gögnin á undan með einu tilviki af tolvufólk
    void yfirskrifaTolvufolk(const vector<tolvufolk>& folk); //Yfiskrifar gögnin á undan með nýjum gögnum, vector af fólki
    void eydaTolvufolk(); //Eyðir öllum gögnum
    void eydaStakiTolvufolk(int nr); //Eyðir stykki af tölvufólk í vector
    void flokkaEftirNafni();
    void radaEftirHaekkandi();
    void radaEftirLaekkandi();
private:
    skraarvinnsla _dataaccess;
    vector<tolvufolk> _folk;
};

#endif // TOLVUFOLKSERVICE_H
