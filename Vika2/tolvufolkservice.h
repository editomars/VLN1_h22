#ifndef TOLVUFOLKSERVICE_H
#define TOLVUFOLKSERVICE_H

#include "sqltenging.h"
#include "tolvufolk.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class tolvufolkService
{
public:
    tolvufolkService();

    //Get föll
    int getSize() const; //Skilar stærð af vector gögnum
    vector<tolvufolk> getTolvufolk() const; //Skilar vectornum af gögnum sem notandi er að nota
    tolvufolk getStaktTolvufolk(int id) const; //Sækir eitt stak af tolvufolki
    vector<tolvufolk> getTolvufolkVensl(int vel_id) const; //Skilar vector af tölvufólki venslað við eitthverja vél

    //Föll sem bæta við Gagnagrunn
    void baetaVidTolvufolk(string nafn, char kyn, int fAr, int dAr); //Bætir við tolvufolk staki
    void tortimaTolvufolk(); //Eyðir öllum gögnum
    void eydaStakiTolvufolk(int id); //Eyðir stykki af tölvufólk, notar ID
    void uppfaeraStakTolvufolk(int id, string nafn, char kyn, int fAr, int dAr);
    void venslaVidVel(int folk_id, int vel_id); //Venslar folk_id við vel_id

    //Föll sem skila umbreyttum gögnum
    vector<tolvufolk> rada(string flokkur, string rod); //Skilar vector sem er raðaður eftir flokk og rod á að vera "asc" eða "desc" fyrir ascending og descending
    vector<tolvufolk> leitaStreng(string flokkur, string leitarord, char pos); //Skilar vector sem er flokkaður(filteraður) ef flokka á strengjaflokk (nafn eða kyn)
    vector<tolvufolk> leitaHeiltolu(string flokkur, char type, int leitarord); //Skilar vector sem er flokkar(filteraður) ef flokka á integer flokk (faedingarar, danarar eða aldur), type er < > = til að fá stærra, minna eða jafnt og
    vector<tolvufolk> leitaHeiltolubil(string flokkur, int laegraBil, int haerraBil); //Skilar vector sem er filteraður á heiltölubili
private:
    sqltenging _dataaccess;

    //raða föll
    vector<tolvufolk> radaAldriHaekkandi(vector<tolvufolk> gogn);
    vector<tolvufolk> radaAldriLaekkandi(vector<tolvufolk> gogn);

    //Filter föll
    vector<tolvufolk> leitaAldur(char type, int leitarord);
    vector<tolvufolk> leitaAldur(int laegraBil, int haerraBil);
};

#endif // TOLVUFOLKSERVICE_H
