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
    string sql = "SELECT * FROM TolvuFolk";

    return selectFolk(sql);
}

void sqltenging::eydaFolk(int id)
{

    string temp = "DELETE FROM TolvuFolk WHERE ID = " + to_string(id);
    char* cstr = new char[temp.length()+1];
    strcpy(cstr, temp.c_str());
    QSqlQuery query(_db);
    query.exec(cstr);
    delete[] cstr;

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

void sqltenging::baetaVidFolk(string fNafn, string mNafn, string eNafn, char kyn, int fAr, int dAr)
{
    string temp = "INSERT INTO TolvuFolk(ForNafn, MidNafn, EftirNafn, Kyn, FaedingarAr, DanarAr)"
                  "VALUES('" + fNafn + "','" + mNafn + "','" + eNafn + "','" + kyn + "'," + to_string(fAr) + "," + to_string(dAr) + ")";
    char* cstr = new char[temp.length()+1];
    strcpy(cstr, temp.c_str());
    QSqlQuery query(_db);
    query.exec(cstr);
    delete[] cstr;
}

vector<tolvufolk> sqltenging::selectFolk(string sql) const
{
    vector<tolvufolk> t;
    QSqlQuery query(_db);
    char* cstr = new char[sql.length()+1];
    strcpy(cstr, sql.c_str());
    query.exec(cstr);

    while(query.next())
    {
        int id = query.value("id").toUInt();
        string fornafn = query.value("fornafn").toString().toStdString();
        string midnafn = query.value("Midnafn").toString().toStdString();
        string eftirnafn = query.value("eftirnafn").toString().toStdString();
        char kyn = query.value("kyn").toString().toStdString()[0];
        int faedingarar = query.value("faedingarar").toUInt();
        int danarar = query.value("danarar").toUInt();

        t.push_back(tolvufolk(id, fornafn, midnafn, eftirnafn, kyn, faedingarar, danarar));
    }

    return t;
}
