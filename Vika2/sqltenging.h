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

    // Functions for Vélar
    vector<velar> lesaVelar(int id) const; //sækir vector með 1 stykki
    vector<velar> lesaVelarSorted(string flokkur, string rod) const; //Sækir sorteraðan vector, flokkur = töfluflokkur í gagngarunn og röð er "asc" eða "desc"
    vector<velar> leitaVelar(string flokkur, string leitarord, char pos); //Leitar að leitarord í töfluflokk, pos = 'b' til að leita í byrjun orðs, 'e' í enda, annars hvar sem er í orði
    vector<velar> leitaVelar(string flokkur, char type, int leitarord); //type = '<' til að leita að heilölu minni en leitarord, '>' fyrir stærri en, '=' fyrir jafnt og
    vector<velar> leitaVelar(string flokkur, int laegraBil, int haerraBil); //skilar flokk á ákeðnu heiltölubili
    void baetaVidVel(string nafn, int bAr, bool byggd, string tegund);
    void eydaVel(int id);
    void uppfaeraVel(int id, string nafn, int bAr, bool byggd, string tegund);
    void tortimaVelum();

    // Functions for Fólk
    vector<tolvufolk> lesaFolk(int id) const; //sækir vector með 1 stak
    vector<tolvufolk> lesaFolkSorted(string flokkur, string rod); //Sækir sorteraðan vector, flokkur = töfluflokkur í gagnagrunn og röð er "asc" eða "desc"
    vector<tolvufolk> leitaFolk(string flokkur, string leitarord, char pos); //Leitar að leitarord í töfluflokk, pos = "b" fyrir beginning, "e" fyrir end. Allt annað fyrir any
    vector<tolvufolk> leitaFolk(string flokkur, char type, int leitarord);
    vector<tolvufolk> leitaFolk(string flokkur, int laegraBil, int haerraBil);
    void baetaVidFolk(string nafn, char kyn, int fAr, int dAr);
    void eydaFolk(int id);
    void uppfaeraFolk(int id, string nafn, char kyn, int fAr, int dAr);
    void tortimaFolki();


    int saekjaSize(string flokkur) const; //Skilar fjölda véla eða fólks (flokkur == "folk" eda "velar")
    // Functions for relations
    void buaTilVensl(int folkID, int velID);
    void eydaVenslFolk(int id);
    void eydaVenslVel(int id);
    void eydaStakiVensl(int folkID, int velID);

    vector<tolvufolk> lesaFolkVenslad(int velarID) const; //Sækir fólk venslað við ákveðið vélar ID
    vector<velar> lesaVelarVenslad(int folkID) const; //Sækir velar venslað við ákveðið fólk ID

private:
    QSqlDatabase _db;
    vector<tolvufolk> selectFolk(string sql) const;
    vector<velar> selectVelar(string sql) const;
    void udiSkipun(string sql); //UPDATE, DELETE, INSERT fólk
};

#endif // SQLTENGING_H
