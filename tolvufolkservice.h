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
    tolvufolk getStaktTolvufolk(int ndx); //Sækir eitt stak af tolvufolki
    void baetaVidTolvufolk(const tolvufolk& t); //Bætir við einu tilviki af tolvufolk í vectorinn (ekki í gagnagrunn)
    void vidbotarTolvufolk(const tolvufolk& t); //Bætir við einu tilvik af tolvufolk (append í gagnagrunn)
    void vidbotarTolvufolk(); //Bætir við vector af tolvufolk (append í gagnagrunn)
    void yfirskrifaTolvufolk(const tolvufolk& t); //Yfirskrifar gögnin á undan með einu tilviki af tolvufólk
    void yfirskrifaTolvufolk(); //Yfiskrifar gögnin á undan með nýjum gögnum, vector af fólki
    void uppfaeraTolvufolk(const vector<tolvufolk>& t); //yfirskrifar vectorinn, ekki gagnagrunn
    void eydaTolvufolk(); //Eyðir öllum gögnum
    void eydaStakiTolvufolk(int nr); //Eyðir stykki af tölvufólk í vector
    void uppfaeraStakTolvufolk(int nr, string nafn, string kyn, int fAr, int dAr); //Uppfærir eitt stak í vector
    void hreinsaTolvufolk(); //Hreinsar öll gögn úr vector
    vector<tolvufolk> leitaEftirNafniTolvufolk(string nafn); //Skilar vector flokkað(filtered) eftir nafni
    vector<tolvufolk> leitaEftirAldriTolvufolk(int aldur); //skilar vector flokkað(filtered) eftir aldri
    vector<tolvufolk> leitaEftirArtaliTolvufolk(int ar, bool f); //bool = true til að leita að fæðingarári, false fyrir dánarár

    vector<tolvufolk> rada(string flokkur, string rod); //Skilar vector sem er raðaður eftir flokk og rod á að vera "asc" eða "desc" fyrir ascending og descending
private:
    skraarvinnsla _dataaccess;
    vector<tolvufolk> _folk;

    //raða föll
    vector<tolvufolk> radaNafniHaekkandi();
    vector<tolvufolk> radaNafniLaekkandi();
    vector<tolvufolk> radaAldriHaekkandi();
    vector<tolvufolk> radaAldriLaekkandi();
    vector<tolvufolk> radaFaedinguHaekkandi();
    vector<tolvufolk> radaFaedinguLaekkandi();
    vector<tolvufolk> radaDaudaHaekkandi();
    vector<tolvufolk> radaDaudaLaekkandi();
};

#endif // TOLVUFOLKSERVICE_H
