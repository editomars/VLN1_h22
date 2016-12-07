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

int velarService::getSize() const
{
    return _dataaccess.saekjaSize("velar");
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
vector<velar> velarService::leitaVelarNafn(string nafn)
{
    vector<velar> t;
    for (size_t i = 0; i < _velar.size(); ++i)
    {
        if (_velar[i].getVelaNafn() == nafn)
        {
            t.push_back(_velar[i]);
        }
    }
    return t;
}
vector<velar> velarService::leitaVelarBar(int bAr)
{
    vector<velar> t;
    for (size_t i = 0; i < _velar.size(); ++i)
    {
        if (_velar[i].getByggingarAr() == bAr)
        {
            t.push_back(_velar[i]);
        }
    }
    return t;
}
vector<velar> velarService::leitaVelarTegund (string tegund)
{
    vector<velar> t;
    for (size_t i = 0; i < _velar.size(); ++i)
    {
        if (_velar[i].getTegund() == tegund)
        {
            t.push_back(_velar[i]);
        }
    }
    return t;
}
vector<velar> velarService::leitaVelarByggd (bool byggd)
{
    vector<velar> t;
    for (size_t i = 0; i < _velar.size(); ++i)
    {
        if (_velar[i].getByggd() == byggd)
        {
            t.push_back(_velar[i]);
        }
    }
    return t;
}
