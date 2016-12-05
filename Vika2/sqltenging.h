#ifndef SQLTENGING_H
#define SQLTENGING_H

#include <QtSql>
#include <vector>
#include <string>
#include "tolvufolk.h"

class sqltenging
{
public:
    sqltenging();

    void baetaVidTolvuFolk(string fNafn, string mNafn, string eNafn, char kyn, int fAr, int dAr);
    void baetaVidTolvuVel(string nafn, int bAr, bool byggd, string tegund);

    vector<tolvufolk> lesa();
private:
    QSqlDatabase _db;
    char* str_to_cstr(string str) const;
};

#endif // SQLTENGING_H
