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

    //Get föll
    vector<tolvufolk> getTolvufolk(); //Skilar vectornum af gögnum sem notandi er að nota
    tolvufolk getStaktTolvufolk(int ndx); //Sækir eitt stak af tolvufolki

    //Föll sem tengja við Gagnagrunn
    void saekjaGogn(); //Sækir gögn í gagnaggrunn
    void vidbotarTolvufolk(); //Bætir við vector af tolvufolk (append í gagnagrunn)
    void vidbotarTolvufolk(const tolvufolk& t); //Bætir við einu tilvik af tolvufolk (append í gagnagrunn)
    void yfirskrifaTolvufolk(); //Yfiskrifar gögnin á undan með nýjum gögnum, notar private breytuna _folk
    void yfirskrifaTolvufolk(const tolvufolk& t); //Yfirskrifar gögnin á undan með einu tilviki af tolvufólk
    void eydaTolvufolk(); //Eyðir öllum gögnum

    //Föll sem breyta vector en ekki gagnagrunn
    void baetaVidTolvufolk(const tolvufolk& t); //Bætir við einu tilviki af tolvufolk í vectorinn (ekki í gagnagrunn)
    void uppfaeraTolvufolk(const vector<tolvufolk>& t); //yfirskrifar vectorinn, ekki gagnagrunn
    void eydaStakiTolvufolk(int nr); //Eyðir stykki af tölvufólk í vector
    void uppfaeraStakTolvufolk(int nr, string nafn, string kyn, int fAr, int dAr); //Uppfærir eitt stak í vector
    void hreinsaTolvufolk(); //Hreinsar öll gögn úr vector

    //Föll sem skila umbreyttum gögnum
    vector<tolvufolk> rada(string flokkur, string rod); //Skilar vector sem er raðaður eftir flokk og rod á að vera "asc" eða "desc" fyrir ascending og descending
    vector<tolvufolk> leitaStreng(string flokkur, string leitarord); //Skilar vector sem er flokkaður(filteraður) ef flokka á strengjaflokk (nafn eða kyn)
    vector<tolvufolk> leitaHeiltolu(string flokkur, int leitarord); //Skilar vector sem er flokkar(filteraður) ef flokka á integer flokk (faedingarar, danarar eða aldur)
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

    //Leita föll (filterar)
    vector<tolvufolk> leitaEftirNafniTolvufolk(string nafn); //Skilar vector flokkað(filtered) eftir nafni
    vector<tolvufolk> leitaEftirAldriTolvufolk(int aldur); //skilar vector flokkað(filtered) eftir aldri
    vector<tolvufolk> leitaEftirArtaliTolvufolk(int ar, bool f); //bool = true til að leita að fæðingarári, false fyrir dánarár
    vector<tolvufolk> leitaEftirKyniTolvufolk(string kyn); //Skilar vector flokkað(filtered) eftir kyni
};

#endif // TOLVUFOLKSERVICE_H
