#ifndef SQLTENGING_H
#define SQLTENGING_H

#include <QtSql>
#include <vector>
#include "tolvufolk.h"
#include "velar.h"

class sqltenging
{
public:
    sqltenging();
    vector<velar> lesaVelar();
    vector<tolvufolk> lesaFolk();
private:
    QSqlDatabase db;
};

#endif // SQLTENGING_H
