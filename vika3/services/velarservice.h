#ifndef VELARSERVICE_H
#define VELARSERVICE_H

#include "sql/sqltenging.h"
#include "models/velar.h"
#include <vector>
#include <iostream>

using namespace std;

class velarService
{
public:
    velarService();

    //Get föll
    vector<velar> getVelar() const; //Skilar vectornum af gögnum sem notandi er að nota
    velar getStaktVelar(int ndx) const; //Sækir eitt stak af velum
    vector<velar> getVelarVensl(int folk_id) const; //Skilar öllum vélum venslaðar við eitthverja persónu
    int getSize() const; //Skilar stærð af vector gögnum
    vector<velar> rada(string flokkur, string rod); //Skilar vector sem er raðaður eftir flokk og rod á að vera "asc" eða "desc" fyrir ascending og descending


    //Föll sem breyta Gagnagrunn
    void baetaVidVelar(string vNafn, int bAr, bool byggd, string tegund); //Bætir við einu tilviki af velar í vectorinn (ekki í gagnagrunn)
    void uppfaeraVelar(int id, string nafn, int bAr, bool byggd, string tegund);
    void eydaStakiVel(int id);
    void tortimaTolvuVelar();
    void venslaVidVel(int folkID, int velID); // venslar folk_id vid vel_id
    void eydaStakiVensl(int folkID, int velID); //Eyðir staki af venslum

    //Föll sem skila umbreyttum gögnum
    vector<velar> rada(string flokkur, string rod) const;
    vector<velar> leitaStreng(string flokkur, string leitarord, char pos); //Skilar vector sem er flokkaður(filteraður) ef flokka á strengjaflokk (nafn eða kyn)
    vector<velar> leitaHeiltolu(string flokkur, char type, int leitarord); //Skilar vector sem er flokkar(filteraður) ef flokka á integer flokk (faedingarar, danarar eða aldur), type er < > = til að fá stærra, minna eða jafnt og
    vector<velar> leitaHeiltolubil(string flokkur, int laegraBil, int haerraBil); //Skilar vector sem er filteraður á heiltölubili
    vector<velar> leitaBool(string flokkur, int erSatt); //Skilar öllum sönnu eða ósönnu úrtökonum

private:
    sqltenging _dataaccess;
};

#endif // VELARSERVICE_H
