#include "sqltenging.h"

sqltenging::sqltenging()
{
    _db = QSqlDatabase::database();
    if (!_db.isOpen())
    {
        _db = QSqlDatabase::addDatabase("QSQLITE");
        QString dbName = "vln1.sqlite";
        _db.setDatabaseName(dbName);
        _db.open();
    }
}
// VELAR
vector<velar> sqltenging::lesaVelar(int id) const
{
    string sql = "SELECT * FROM TolvuVelar";

    if (id != -1){
        sql += " WHERE id = " + to_string(id);
    }

    return selectVelar(sql);
}

vector<velar> sqltenging::lesaVelarSorted(string flokkur, string rod) const
{
    string sql = "SELECT * FROM TolvuVelar "
            "ORDER BY " + flokkur + " " + rod;

    return selectVelar(sql);
}

vector<velar> sqltenging::leitaVelar(string flokkur, string leitarord, char pos)
{
    string sql = "SELECT * FROM TolvuVelar "
            "WHERE " + flokkur + " LIKE ";

    if (pos == 'b'){
        sql += "'" + leitarord + "%'";
    }else if (pos == 'e'){
        sql += "'%" + leitarord + "'";
    }else{
        sql += "'%" + leitarord + "%'";
    }

    return selectVelar(sql);
}

vector<velar> sqltenging::leitaVelar(string flokkur, char type, int leitarord)
{
    string sql = "SELECT * FROM TolvuVelar "
            "WHERE " + flokkur + " " + type + " " + to_string(leitarord);

    return selectVelar(sql);
}

vector<velar> sqltenging::leitaVelar(string flokkur, int laegraBil, int haerraBil)
{
    string sql = "SELECT * FROM TolvuVelar "
            "WHERE " + flokkur + " BETWEEN " + to_string(laegraBil) + " AND " + to_string(haerraBil);

    return selectVelar(sql);
}

void sqltenging::baetaVidVel(string nafn, int bAr, bool byggd, string tegund)
{
    string sql = "INSERT INTO TolvuVelar(Nafn, Byggingarar, Byggd, Tegund)"
                  "VALUES('" + nafn + "'," + to_string(bAr) + "," + to_string(byggd) + ",'" + tegund + "')";
    udiSkipun(sql);
}

void sqltenging::eydaVel(int id)
{

    string sql = "DELETE FROM TolvuVelar WHERE ID = " + to_string(id);
    udiSkipun(sql);

    eydaVensl("vel_id",id);
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

void sqltenging::tortimaVelum()
{
    string terminator = "DELETE FROM TolvuVelar";
    udiSkipun(terminator);
}

// FOLK
vector<tolvufolk> sqltenging::lesaFolk(int id) const
{
    string sql = "SELECT * FROM TolvuFolk";

    if (id != -1){
        sql += " WHERE ID = " + to_string(id);
    }

    return selectFolk(sql);
}

vector<tolvufolk> sqltenging::lesaFolkSorted(string flokkur, string rod)
{
    string sql = "SELECT * FROM TolvuFolk "
            "ORDER BY " + flokkur + " " + rod;

    return selectFolk(sql);
}

vector<tolvufolk> sqltenging::leitaFolk(string flokkur, string leitarord, char pos)
{
    string sql = "SELECT * FROM Tolvufolk "
            "WHERE " + flokkur + " LIKE ";

    if (pos == 'b'){
        sql += "'" + leitarord + "%'";
    }else if (pos == 'e'){
        sql += "'%" + leitarord + "'";
    }else{
        sql += "'%" + leitarord + "%'";
    }

    return selectFolk(sql);
}

vector<tolvufolk> sqltenging::leitaFolk(string flokkur, char type, int leitarord)
{
    string sql = "SELECT * FROM TolvuFolk "
            "WHERE " + flokkur + " " + type + " " + to_string(leitarord);

    return selectFolk(sql);
}

vector<tolvufolk> sqltenging::leitaFolk(string flokkur, int laegraBil, int haerraBil)
{
    string sql = "SELECT * FROM TolvuFolk "
            "WHERE " + flokkur + " BETWEEN " + to_string(laegraBil) + " AND " + to_string(haerraBil);

    return selectFolk(sql);
}

void sqltenging::baetaVidFolk(string nafn, char kyn, int fAr, int dAr)
{
    string sql = "INSERT INTO TolvuFolk(Nafn, Kyn, FaedingarAr, DanarAr)"
                  "VALUES('" + nafn + "','" + kyn + "'," + to_string(fAr) + "," + to_string(dAr) + ")";
    udiSkipun(sql);
}
void sqltenging::eydaFolk(int id)
{

    string sql = "DELETE FROM TolvuFolk WHERE ID = " + to_string(id);
    udiSkipun(sql);

    eydaVensl("folk_id", id);
}

void sqltenging::uppfaeraFolk(int id, string nafn, char kyn, int fAr, int dAr)
{
    string sql = "UPDATE TolvuFolk "
                 "SET nafn = '" +  nafn + "'"
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

int sqltenging::saekjaSize(string flokkur) const
{
    int size = 0;
    string sql = "SELECT COUNT(*) as Size from ";
    if (flokkur == "velar"){
        sql += "TolvuVelar";
    }else if (flokkur == "folk"){
        sql += "TolvuFolk";
    }else{
        size = -1;
    }

    if (size != -1)
    {
        QSqlQuery query(_db);
        query.exec(sql.c_str());
        if (query.next()){
            size = query.value("Size").toUInt();
        }
    }
    return size;
}



//Vensl

void sqltenging::buaTilVensl(int folkID, int velID)
{
    string sql = "INSERT INTO venslfolkvelar(folk_id,vel_id)"
                 "VALUES(" + to_string(folkID) + "," + to_string(velID) + ")";
    udiSkipun(sql);

}


void sqltenging::eydaStakiVensl(int folkID, int velID)
{
    string sql = "DELETE FROM venslfolkvelar "
                 "WHERE folk_id = " + to_string(folkID) + " "
                 "AND vel_id = " + to_string(velID);
    udiSkipun(sql);
}

vector<tolvufolk> sqltenging::lesaFolkVenslad(int velarID) const
{
    string sql = "SELECT f.id, f.nafn, f.kyn, f.faedingarar, f.danarar "
            "FROM tolvufolk f "
            "INNER JOIN venslfolkvelar v ON v.folk_id = f.id "
            "INNER JOIN tolvuvelar t ON v.vel_id = t.id "
            "WHERE t.id = " + to_string(velarID);

    return selectFolk(sql);
}

vector<velar> sqltenging::lesaVelarVenslad(int folkID) const
{
    string sql = "SELECT t.id, t.nafn, t.byggingarar, t.byggd, t.tegund "
            "FROM tolvuvelar t "
            "INNER JOIN venslfolkvelar v ON v.vel_id = t.id "
            "INNER JOIN tolvufolk f ON v.folk_id = f.id "
            "WHERE f.id = " + to_string(folkID);

    return selectVelar(sql);
}

// Private Functions
vector<tolvufolk> sqltenging::selectFolk(string sql) const
{
    vector<tolvufolk> t;
    QSqlQuery query(_db);
    query.exec(sql.c_str());

    while(query.next())
    {
        int id = query.value("id").toUInt();
        string nafn = query.value("nafn").toString().toStdString();
        char kyn = query.value("kyn").toString().toStdString()[0];
        int faedingarar = query.value("faedingarar").toUInt();
        int danarar = query.value("danarar").toUInt();

        t.push_back(tolvufolk(id, nafn, kyn, faedingarar, danarar));
    }

    return t;
}

vector<velar> sqltenging::selectVelar(string sql) const
{
    vector<velar> v;
    QSqlQuery query(_db);
    query.exec(sql.c_str());

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
    QSqlQuery query(_db);
    query.exec(sql.c_str());
}

void sqltenging::eydaVensl(string col, int id)
{
    string sql = "DELETE FROM venslfolkvelar WHERE " + col + " = " + to_string(id);
    udiSkipun(sql);
}
// End of private functions
