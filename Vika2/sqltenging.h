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
    vector<tolvufolk> lesaFolk();

    void baetaVidTolvuFolk(string fNafn, string mNafn, string eNafn, char kyn, int fAr, int dAr);
    void baetaVidTolvuVel(string nafn, int bAr, bool byggd, string tegund);
private:
    QSqlDatabase _db;
};

#endif // SQLTENGING_H
