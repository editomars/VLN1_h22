#ifndef SQLTENGING_H
#define SQLTENGING_H

#include <QtSql>
#include <vector>
#include "tolvufolk.h"

class sqltenging
{
public:
    sqltenging();
    vector<tolvufolk> lesa();
private:
    QSqlDatabase db;
};

#endif // SQLTENGING_H
