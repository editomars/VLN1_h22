#include "sqltenging.h"

sqltenging::sqltenging()
{
    _db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbName = "vln1.sqlite";
    _db.setDatabaseName(dbName);
    _db.open();
}
// VELAR
vector<velar> sqltenging::lesaVelar()
{
    string sql = "SELECT * FROM TolvuVelar";

    return selectVelar(sql);
}

void sqltenging::baetaVidVel(string nafn, int bAr, bool byggd, string tegund)
{
    string sql = "INSERT INTO TolvuVelar(Nafn, Byggingarar, Byggd, Tegund)"
                  "VALUES('" + nafn + "'," + to_string(bAr) + "," + to_string(byggd) + ",'" + tegund + "')";
    udiSkipun(sql);
}

void sqltenging::uppfaeraVel(int id, string nafn, int bAr, bool byggd, string tegund)
{
    string sql = "UPDATE TolvuVelar "
                 "SET nafn = '" +  nafn + "'"
                 ", byggingarar = " + to_string(bAr) +
                 ", byggd = " + to_string(byggd) +
                 ", tegund = '" + tegund + "'"
                 "WHERE ID = " + to_string(id);

    udiSkipun(sql);
}



// FOLK
vector<tolvufolk> sqltenging::lesaFolk() const
{
    string sql = "SELECT * FROM TolvuFolk";

    return selectFolk(sql);
}

void sqltenging::baetaVidFolk(string fNafn, string eNafn, char kyn, int fAr, int dAr)
{
    string sql = "INSERT INTO TolvuFolk(ForNafn, EftirNafn, Kyn, FaedingarAr, DanarAr)"
                  "VALUES('" + fNafn + "','" + eNafn + "','" + kyn + "'," + to_string(fAr) + "," + to_string(dAr) + ")";
    udiSkipun(sql);
}
void sqltenging::eydaFolk(int id)
{

    string sql = "DELETE FROM TolvuFolk WHERE ID = " + to_string(id);
    udiSkipun(sql);
}

void sqltenging::uppfaeraFolk(int id, string fNafn, string eNafn, char kyn, int fAr, int dAr)
{
    string sql = "UPDATE TolvuFolk "
                 "SET fornafn = '" +  fNafn + "'"
                 ", eftirnafn = '" + eNafn + "'"
                 ", kyn = '" + kyn + "'"
                 ", faedingarAr = " + to_string(fAr) +
                 ", danarAr = " + to_string(dAr) + " "
                 "WHERE ID = " + to_string(id);

    udiSkipun(sql);
}

void sqltenging::tortimaFolki()
{
    string terminator = "DELETE FROM tolvufolk";
    udiSkipun(terminator);
}


// Private Functions
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
        string eftirnafn = query.value("eftirnafn").toString().toStdString();
        char kyn = query.value("kyn").toString().toStdString()[0];
        int faedingarar = query.value("faedingarar").toUInt();
        int danarar = query.value("danarar").toUInt();

        t.push_back(tolvufolk(id, fornafn, eftirnafn, kyn, faedingarar, danarar));
    }

    return t;
}

vector<velar> sqltenging::selectVelar(string sql) const
{
    vector<velar> v;
    QSqlQuery query(_db);
    char* cstr = new char[sql.length()+1];
    strcpy(cstr, sql.c_str());
    query.exec(cstr);

    while(query.next())
    {
        int id = query.value("id").toUInt();
        string nafn = query.value("Nafn").toString().toStdString();
        int ar = query.value("byggingarar").toUInt();
        bool byggd = query.value("byggd").toBool();
        string tegund = query.value("tegund").toString().toStdString();

        v.push_back(velar(id, nafn, ar, tegund, byggd));
    }

    return v;
}

void sqltenging::udiSkipun(string sql)
{
    char* cstr = new char[sql.length()+1];
    strcpy(cstr, sql.c_str());
    QSqlQuery query(_db);
    query.exec(cstr);
    delete[] cstr;
}
// End of private functions
