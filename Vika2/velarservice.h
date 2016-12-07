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

    //Föll sem breyta Gagnagrunn
    void baetaVidVelar(string vNafn, int bAr, bool byggd, string tegund); //Bætir við einu tilviki af velar í vectorinn (ekki í gagnagrunn)
    void uppfaeraVelar(int id, string nafn, int bAr, bool byggd, string tegund);
    void eydaStakiVel(int id);
    void tortimaTolvuVelar();

    //leitaFöll
    vector<velar> leitaVelarNafn (string nafn);
    vector<velar> leitaVelarBar (int bAr);
    vector<velar> leitaVelarTegund (string tegund);
    vector<velar> leitaVelarByggd (bool byggd);


private:
    sqltenging _dataaccess;
    vector<velar> _velar;
};

#endif // VELARSERVICE_H
