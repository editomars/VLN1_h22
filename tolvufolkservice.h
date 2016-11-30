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
    tolvufolk getSingleTolvufolk(int ndx); //Sækir eitt stak af tolvufolki
    void baetaVidTolvufolk(const tolvufolk& t); //Bætir við einu tilviki af tolvufolk í vectorinn (ekki í gagnagrunn)
    void vidbotarTolvufolk(const tolvufolk& t); //Bætir við einu tilvik af tolvufolk (append í gagnagrunn)
    void vidbotarTolvufolk(); //Bætir við vector af tolvufolk (append í gagnagrunn)
    void yfirskrifaTolvufolk(const tolvufolk& t); //Yfirskrifar gögnin á undan með einu tilviki af tolvufólk
    void yfirskrifaTolvufolk(); //Yfiskrifar gögnin á undan með nýjum gögnum, vector af fólki
    void eydaTolvufolk(); //Eyðir öllum gögnum
    void eydaStakiTolvufolk(int nr); //Eyðir stykki af tölvufólk í vector
    void updateTolvufolkSingle(int nr, string name, string kyn, int fYear, int dYear); //Uppfærir eitt stak í vector
    void clearTolvufolk(); //Hreinsar öll gögn úr vector
    void radaNafniHaekkandi();
    void radaNafniLaekkandi();
    void radaAldriHaekkandi();
    void radaAldriLaekkandi();
    void radaFaedinguHaekkandi();
    void radaFaedinguLaekkandi();
    void radaDaudaHaekkandi();
    void radaDaudaLaekkandi();


private:
    skraarvinnsla _dataaccess;
    vector<tolvufolk> _folk;
};

#endif // TOLVUFOLKSERVICE_H
