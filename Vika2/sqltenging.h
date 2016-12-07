#ifndef SQLTENGING_H
#define SQLTENGING_H

#include <QtSql>
#include <vector>
#include <string>
#include "tolvufolk.h"
#include "velar.h"

class sqltenging
{
public:
    sqltenging();

    // Functions for Vélar
    vector<velar> lesaVelar(int id) const; //id = -1 ef sækja allan pakkann, annars sækir bara vector með 1 stykki
    void baetaVidVel(string nafn, int bAr, bool byggd, string tegund);
    void eydaVel(int id);
    void uppfaeraVel(int id, string nafn, int bAr, bool byggd, string tegund);
    void tortimaVelum();

    // Functions for Fólk
    vector<tolvufolk> lesaFolk(int id) const; //id = -1 ef sækja allan pakkann, annars sækir bara eitt stak
    void baetaVidFolk(string fNafn, string eNafn, char kyn, int fAr, int dAr);
    void eydaFolk(int id);
    void uppfaeraFolk(int id, string fNafn, string eNafn, char kyn, int fAr, int dAr);
    void tortimaFolki();


    int saekjaSize(string flokkur) const; //Skilar fjölda véla eða fólks (flokkur == "folk" eda "velar")
    // Functions for relations


private:
    QSqlDatabase _db;
    vector<tolvufolk> selectFolk(string sql) const;
    vector<velar> selectVelar(string sql) const;
    void udiSkipun(string sql); //UPDATE, DELETE, INSERT fólk
};

#endif // SQLTENGING_H
