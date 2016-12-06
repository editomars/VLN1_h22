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
    vector<velar> lesaVelar();
    vector<tolvufolk> lesaFolk() const;

    void baetaVidFolk(string fNafn, string mNafn, string eNafn, char kyn, int fAr, int dAr);
    void baetaVidVel(string nafn, int bAr, bool byggd, string tegund);
    void eydaFolk(int id);
private:
    QSqlDatabase _db;
    vector<tolvufolk> selectFolk(string sql) const;
    vector<velar> selectVelar(string sql) const;
    void udiSkipun(string sql); //UPDATE, DELETE, INSERT fólk
};

#endif // SQLTENGING_H
