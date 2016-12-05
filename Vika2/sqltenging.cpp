#include "sqltenging.h"

sqltenging::sqltenging()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "vln1.sqlite";
    _db.setDatabaseName(dbName);
    _db.open();
}

vector<tolvufolk> sqltenging::lesaFolk() const
{
    vector<tolvufolk> t;
    QSqlQuery query(_db);

    query.exec("SELECT * FROM TolvuFolk");

    while(query.next()){
        int id = query.value("id").toUInt();
        string fornafn = query.value("fornafn").toString().toStdString();
        string midnafn = query.value("Midnafn").toString().toStdString();
        string eftirnafn = query.value("eftirnafn").toString().toStdString();
        char kyn = query.value("kyn").toString().toStdString()[0];
        int faedingarar = query.value("faedingarar").toUInt();
        int danarar = query.value("danarar").toUInt();

        t.push_back(tolvufolk(id, fornafn, midnafn, eftirnafn, kyn, faedingarar, danarar));
        //tolvufolk(id, fornafn, midnafn, eftirnafn, kyn, fAr, dAr);
    }

    return t;
}

vector<velar> sqltenging::lesaVelar()
{
    vector<velar> v;
    QSqlQuery query(_db);

    query.exec("SELECT * FROM TolvuVelar");


    while(query.next()){
        /*
        string fornafn = query.value("fornafn").toString().toStdString();
        string eftirnafn = query.value("eftirnafn").toString().toStdString();
        string kyn = query.value("kyn").toString().toStdString();
        int faedingarar = query.value("faedingarar").toUInt();
        int danarar = query.value("danarar").toUInt();
        */

        //t.push_back(tolvufolk(fornafn + " " + eftirnafn, kyn, faedingarar, danarar));
        //tolvufolk(id, fornafn, midnafn, eftirnafn, kyn, fAr, dAr);

    }

    return v;
}

void sqltenging::baetaVidTolvuFolk(string fNafn, string mNafn, string eNafn, char kyn, int fAr, int dAr)
{
    string temp = "INSERT INTO TolvuFolk(ForNafn, MidNafn, EftirNafn, Kyn, FaedingarAr, DanarAr)"
                  "VALUES('" + fNafn + "','" + mNafn + "','" + eNafn + "','" + kyn + "'," + to_string(fAr) + "," + to_string(dAr) + ")";
    char* cstr = new char[temp.length()+1];
    strcpy(cstr, temp.c_str());
    QSqlQuery query(_db);
    query.exec(cstr);
    delete[] cstr;
}
