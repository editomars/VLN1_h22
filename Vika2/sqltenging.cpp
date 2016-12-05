#include "sqltenging.h"

sqltenging::sqltenging()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "vln1.sqlite";
    db.setDatabaseName(dbName);
    db.open();
}

vector<tolvufolk> sqltenging::lesa()
{
    vector<tolvufolk> t;
    QSqlQuery query(db);

    query.exec("SELECT * FROM TolvuFolk");

    while(query.next()){
        string name = query.value("name").toString().toStdString();
        string kyn = query.value("kyn").toString().toStdString();
        int faedingarar = query.value("faedingarar").toUInt();
        int danarar = query.value("danarar").toUInt();

        t.push_back(tolvufolk(name, kyn, faedingarar, danarar));
    }

    return t;
}
