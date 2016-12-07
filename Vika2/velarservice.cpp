#include "velarservice.h"

velarService::velarService()
{

}
//----------------------- Svæði fyrir public föll byrjar ----------------------

//Get föll
vector<velar> velarService::getVelar() const
{
    return _dataaccess.lesaVelar(-1);
}

velar velarService::getStaktVelar(int id) const
{
    return _dataaccess.lesaVelar(id)[0];
}

vector<velar> velarService::getVelarVensl(int folk_id) const
{
    return _dataaccess.lesaVelarVenslad(folk_id);
}

int velarService::getSize() const
{
    return _dataaccess.saekjaSize("velar");
}

vector<velar> velarService::rada(string flokkur, string rod)
{
    return _dataaccess.lesaVelarSorted(flokkur,rod);
}

//Föll sem breyta gagnagrunni

void velarService::baetaVidVelar(string vNafn, int bAr, bool byggd, string tegund)
{
    _dataaccess.baetaVidVel(vNafn, bAr, byggd, tegund);
}

void velarService::uppfaeraVelar(int id, string nafn, int bAr, bool byggd, string tegund)
{
    _dataaccess.uppfaeraVel(id,nafn,bAr,byggd,tegund);
}

void velarService::eydaStakiVel(int id)
{
    _dataaccess.eydaVel(id);
}

void velarService::tortimaTolvuVelar()
{
    _dataaccess.tortimaVelum();

}

vector<velar> velarService::rada(string flokkur, string rod) const
{
    return _dataaccess.lesaVelarSorted(flokkur, rod);
}

vector<velar> velarService::leitaStreng(string flokkur, string leitarord, char pos)
{
    return _dataaccess.leitaVelar(flokkur, leitarord, pos);
}

vector<velar> velarService::leitaHeiltolu(string flokkur, char type, int leitarord)
{
    return _dataaccess.leitaVelar(flokkur, type, leitarord);
}

vector<velar> velarService::leitaHeiltolubil(string flokkur, int laegraBil, int haerraBil)
{
    return _dataaccess.leitaVelar(flokkur, laegraBil, haerraBil);
}
