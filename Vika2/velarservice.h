#ifndef VELARSERVICE_H
#define VELARSERVICE_H

#include "sqltenging.h"
#include "velar.h"
#include <vector>
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
    void baetaVidVelar(string vNafn, int bAr, bool byggd, string tegund); //Bætir við einu tilviki af velar í vectorinn (ekki í gagnagrunn)
    void uppfaeraVelar(int id, string nafn, int bAr, bool byggd, string tegund);
private:
    sqltenging _dataaccess;
    vector<velar> _velar;
};

#endif // VELARSERVICE_H
