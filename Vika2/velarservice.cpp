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
    _velar = _dataVaccess.lesaVelar();
}


void velarService::vidbotarVelar()
{
    for (size_t i = 0; i < _velar.size(); ++i)
    {
        //_dataVaccess.baetaVid(_velar[i]);
    }
}

void velarService::vidbotarVelar(const velar& v)
{
    //_dataVaccess.baetaVid(t);
}

void velarService::yfirskrifaVelar()
{
    eydaVelar();
    vidbotarVelar();
}

void velarService::yfirskrifaVelar(const velar& v)
{
    //_dataVaccess.skrifa(t);
}

void velarService::eydaVelar()
{
    //_dataVaccess.eyda();
}

//Föll sem breyta vector, en ekki gagnagrunn
void velarService::baetaVidVelar(const velar &v)
{
    _velar.push_back(v);
}

void velarService::uppfaeraVelar(const vector<velar>& v)
{
    _velar = v;
}

void velarService::eydaStakiVelar(int nr)
{
    _velar.erase(_velar.begin() + nr);
}

void velarService::uppfaeraStakVelar(int id, string vNafn, int bAr, string tegund, bool byggd)
{
    //_velar[nr].uppfNafn(name);
    //_velar[nr].uppfGender(kyn);
    //_velar[nr].uppfFaedingarar(fYear);
    //_velar[nr].uppfDanarar(dYear);
}

void velarService::hreinsaVelar()

{
    _velar.clear();
}