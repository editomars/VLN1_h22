#include "tolvufolkservice.h"
//Smiður
tolvufolkService::tolvufolkService()
{

}

//----------------------- Svæði fyir sorting struct byrjar ---------------------
//rada aldri haekkandi
struct aldurHaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        int sidastaAri = (i.getDanarar() == -1 ? 2016 : i.getDanarar());
        int sidastaArj = (j.getDanarar() == -1 ? 2016 : j.getDanarar());
        return ((sidastaAri-i.getFaedingarar()) < (sidastaArj-j.getFaedingarar()));
    }
};

struct aldurLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        int sidastaAri = (i.getDanarar() == -1 ? 2016 : i.getDanarar());
        int sidastaArj = (j.getDanarar() == -1 ? 2016 : j.getDanarar());
        return ((sidastaAri-i.getFaedingarar()) > (sidastaArj-j.getFaedingarar()));
    }
};
//----------------------- Svæði fyir sorting struct endar ---------------------

//----------------------- Svæði fyrir public föll byrjar ----------------------

//Get föll

tolvufolk tolvufolkService::getStaktTolvufolk(int id) const
{
    return _dataaccess.lesaFolk(id)[0];
}

vector<tolvufolk> tolvufolkService::getTolvufolk() const
{
    return _dataaccess.lesaFolk(-1);
}

int tolvufolkService::getSize() const
{
    return _dataaccess.saekjaSize("folk");
}

//Föll sem breyta gagnagrunn

void tolvufolkService::baetaVidTolvufolk(string fNafn, string eNafn, char kyn, int fAr, int dAr)
{
    _dataaccess.baetaVidFolk(fNafn, eNafn, kyn, fAr, dAr);
}

void tolvufolkService::tortimaTolvufolk()
{
    _dataaccess.tortimaFolki();
}

void tolvufolkService::eydaStakiTolvufolk(int id)
{
    _dataaccess.eydaFolk(id);
}

void tolvufolkService::uppfaeraStakTolvufolk(int id, string fNafn , string eNafn, char kyn, int fAr, int dAr)
{
    _dataaccess.uppfaeraFolk(id,fNafn,eNafn,kyn,fAr,dAr);
}

//Föll sem skila umbreyttum gögnum
vector<tolvufolk> tolvufolkService::leitaStreng(string flokkur, string leitarord)
{
    if (flokkur == "nafn")
    {
        return leitaEftirNafniTolvufolk(leitarord);
    }
    if (flokkur == "kyn")
    {
        if (leitarord == "m")
            return leitaEftirKyniTolvufolk('m');
        else
            return leitaEftirKyniTolvufolk('f');
    }
    return _folk;
}

vector<tolvufolk> tolvufolkService::leitaHeiltolu(string flokkur, int leitarord)
{
    if (flokkur == "aldur")
    {
        return leitaEftirAldriTolvufolk(leitarord);
    }
    if (flokkur == "faedingarar")
    {
        return leitaEftirArtaliTolvufolk(leitarord, true);
    }
    if (flokkur == "danarar")
    {
        return leitaEftirArtaliTolvufolk(leitarord, false);
    }
    return _folk;
}

vector<tolvufolk> tolvufolkService::rada(string flokkur, string rod)
{
    if (flokkur == "aldur"){
        if (rod == "asc"){
            return radaAldriHaekkandi(_dataaccess.lesaFolk(-1));
        }else if (rod == "desc"){
            return radaAldriLaekkandi(_dataaccess.lesaFolk(-1));
        }
    }
    return _dataaccess.lesaFolkSorted(flokkur,rod);
}
//--------------------------- Svæði fyrir public föll endar ---------------------------------------------

//------------------------ Svæði fyrir private föll byrjar ----------------------------------------------
//Sort föll --private
vector<tolvufolk> tolvufolkService::radaAldriHaekkandi(vector<tolvufolk> gogn)
{
    aldurHaekkandi temp;
    vector<tolvufolk> sorted = gogn;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaAldriLaekkandi(vector<tolvufolk> gogn)
{
    aldurLaekkandi temp;
    vector<tolvufolk> sorted = gogn;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

//Leita föll --private (filter föll)
vector<tolvufolk> tolvufolkService::leitaEftirAldriTolvufolk(int aldur)
{
    vector<tolvufolk> t;
    for (size_t i = 0; i < _folk.size(); ++i)
    {
        int samanburdur = (_folk[i].getDanarar() == -1 ? 2016 : _folk[i].getDanarar());
        if (samanburdur - _folk[i].getFaedingarar() == aldur)
        {
            t.push_back(_folk[i]);
        }
    }
    return t;
}

vector<tolvufolk> tolvufolkService::leitaEftirArtaliTolvufolk(int ar, bool f)
{
    vector<tolvufolk> t;
    for (size_t i = 0; i < _folk.size(); ++i)
    {
        if (f){
            if (_folk[i].getFaedingarar() == ar)
            {
                t.push_back(_folk[i]);
            }
        }

        else
        {
            if (_folk[i].getDanarar() == ar)
            {
                t.push_back(_folk[i]);
            }
        }
    }
    return t;
}

vector<tolvufolk> tolvufolkService::leitaEftirNafniTolvufolk(string nafn)
{
    vector<tolvufolk> t;
    for (size_t i = 0; i < _folk.size(); ++i)
    {
        if (_folk[i].getNafn() == nafn)
        {
            t.push_back(_folk[i]);
        }
    }
    return t;
}

vector<tolvufolk> tolvufolkService::leitaEftirKyniTolvufolk(char kyn)
{
    vector<tolvufolk> t;
    for (size_t i = 0; i < _folk.size(); ++i)
    {
        if (_folk[i].getKyn() == kyn)
        {
            t.push_back(_folk[i]);
        }
    }
    return t;
}
