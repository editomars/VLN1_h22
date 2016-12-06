#include "velarservice.h"

velarService::velarService()
{

}
//----------------------- Svæði fyrir public föll byrjar ----------------------

//Get föll
vector<velar> velarService::getVelar() const
{
    return _velar;
}

velar velarService::getStaktVelar(int ndx) const
{
    return _velar[ndx];
}

int velarService::getSize() const
{
    return _velar.size();
}

//Föll sem tengja við gagnagrunn
void velarService::saekjaGogn()
{
    _velar = _dataaccess.lesaVelar();
}


void velarService::baetaVidVelar(string vNafn, int bAr, bool byggd, string tegund)
{
    _dataaccess.baetaVidVel(vNafn, bAr, byggd, tegund);
    saekjaGogn();
}

void velarService::uppfaeraVelar(int id, string nafn, int bAr, bool byggd, string tegund)
{
    _dataaccess.uppfaeraVel(id,nafn,bAr,byggd,tegund);
    saekjaGogn();
}

void velarService::eydaStakiVel(int id)
{
    _dataaccess.eydaVel(id);
    saekjaGogn();
}

void velarService::tortimaTolvuVelar()
{
    _dataaccess.tortimaVelum();

}
