#ifndef VELARSERVICE_H
#define VELARSERVICE_H

#include "sqltenging.h"
#include "velar.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class velarService
{
public:
    velarService();

    //Get föll
    vector<velar> getVelar() const; //Skilar vectornum af gögnum sem notandi er að nota
    velar getStaktVelar(int ndx) const; //Sækir eitt stak af velum
    int getSize() const; //Skilar stærð af vector gögnum

    //Föll sem tengja við Gagnagrunn
    void saekjaGogn(); //Sækir gögn í gagnaggrunn
    void vidbotarVelar(); //Bætir við vector af velar (append í gagnagrunn)
    void vidbotarVelar(const velar& v); //Bætir við einu tilvik af velar (append í gagnagrunn)
    void yfirskrifaVelar(); //Yfiskrifar gögnin á undan með nýjum gögnum, notar private breytuna _velar
    void yfirskrifaVelar(const velar& v); //Yfirskrifar gögnin á undan með einu tilviki af velar
    void eydaVelar(); //Eyðir öllum gögnum

    //Föll sem breyta vector en ekki gagnagrunn
    void baetaVidVelar(string vNafn, int bAr, bool byggd, string tegund); //Bætir við einu tilviki af velar í vectorinn (ekki í gagnagrunn)
    void uppfaeraVelar(const vector<velar>& v); //yfirskrifar vectorinn, ekki gagnagrunn
    void eydaStakiVelar(int id); //Eyðir stykki af tölvufólk í vector
    void uppfaeraStakVelar(int id, string vNafn, int bAr, string tegund, bool byggd); //Uppfærir eitt stak í vector
    void hreinsaVelar(); //Hreinsar öll gögn úr vector
private:
    sqltenging _dataaccess;
    vector<velar> _velar;
};

#endif // VELARSERVICE_H
