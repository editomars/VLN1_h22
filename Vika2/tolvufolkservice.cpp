#include "tolvufolkservice.h"
//Smiður
tolvufolkService::tolvufolkService()
{

}

//----------------------- Svæði fyir sorting struct byrjar ---------------------
//rada eftir stafrosrod abc..
struct nafnHaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getFornafn() < j.getNafn());
    }
};

//rada eftir stafrosrod cba..
struct nafnLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getNafn() > j.getNafn());
    }
};

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

struct faedingHaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getFaedingarar() < j.getFaedingarar());
    }
};

struct faedingLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getFaedingarar() > j.getFaedingarar());
    }
};

struct daudiHaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        int sidastaAri = (i.getDanarar() == -1 ? 2016 : i.getDanarar());
        int sidastaArj = (j.getDanarar() == -1 ? 2016 : j.getDanarar());
        return (sidastaAri < sidastaArj);
    }
};

struct daudiLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        int sidastaAri = (i.getDanarar() == -1 ? 2016 : i.getDanarar());
        int sidastaArj = (j.getDanarar() == -1 ? 2016 : j.getDanarar());
        return (sidastaAri > sidastaArj);
    }
};

//----------------------- Svæði fyir sorting struct endar ---------------------

//----------------------- Svæði fyrir public föll byrjar ----------------------

//Get föll

tolvufolk tolvufolkService::getStaktTolvufolk(int ndx) const
{
    return _folk[ndx];
}

int tolvufolkService::getSize() const
{
    return _folk.size();
}

//Föll sem tengja við gagnagrunn
vector<tolvufolk> tolvufolkService::getTolvufolk() const
{
    return _dataaccess.lesaFolk();
}

void tolvufolkService::addTolvufolk(string fNafn, string mNafn, string eNafn, char kyn, int fAr, int dAr)
{
    _dataaccess.baetaVidTolvuFolk(fNafn, mNafn, eNafn, kyn, fAr, dAr);
}

void tolvufolkService::yfirskrifaTolvufolk()
{
    //eydaTolvufolk();
    //vidbotarTolvufolk();
}

void tolvufolkService::yfirskrifaTolvufolk(const tolvufolk& t)
{
    //_dataaccess.skrifa(t);
}

void tolvufolkService::eydaTolvufolk()
{
    //_dataaccess.eyda();
}

//Föll sem breyta vector, en ekki gagnagrunn
void tolvufolkService::baetaVidTolvufolk(const tolvufolk &t)
{
    _folk.push_back(t);
}

void tolvufolkService::uppfaeraTolvufolk(const vector<tolvufolk>& t)
{
    _folk = t;
}

void tolvufolkService::eydaStakiTolvufolk(int nr)
{
    _folk.erase(_folk.begin() + nr);
}

void tolvufolkService::uppfaeraStakTolvufolk(int nr, string name, string kyn, int fYear, int dYear)
{
    //_folk[nr].uppfNafn(name);
    //_folk[nr].uppfGender(kyn);
    _folk[nr].uppfFaedingarar(fYear);
    _folk[nr].uppfDanarar(dYear);
}

void tolvufolkService::hreinsaTolvufolk()

{
    _folk.clear();
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
    if (flokkur == "nafn")
    {
        if (rod == "asc")
        {
            return radaNafniHaekkandi();
        }
        if (rod == "desc")
        {
            return radaNafniLaekkandi();
        }
    }
    if (flokkur == "aldur")
    {
        if (rod == "asc")
        {
            return radaAldriHaekkandi();
        }
        if (rod == "desc")
        {
            return radaAldriLaekkandi();
        }
    }
    if (flokkur == "faedingarar")
    {
        if (rod == "asc")
        {
            return radaFaedinguHaekkandi();
        }
        if (rod == "desc")
        {
            return radaFaedinguLaekkandi();
        }
    }
    if (flokkur == "danarar")
    {
        if (rod == "asc")
        {
            return radaDaudaHaekkandi();
        }
        if (rod == "desc")
        {
            return radaDaudaLaekkandi();
        }
    }
    return _folk;
}
//--------------------------- Svæði fyrir public föll endar ---------------------------------------------

//------------------------ Svæði fyrir private föll byrjar ----------------------------------------------
//Sort föll --private
vector<tolvufolk> tolvufolkService::radaNafniHaekkandi()
{
    nafnHaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaNafniLaekkandi()
{
    nafnLaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaAldriHaekkandi()
{
    aldurHaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaAldriLaekkandi()
{
    aldurLaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaFaedinguHaekkandi()
{
    faedingHaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaFaedinguLaekkandi()
{
    faedingLaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}
vector<tolvufolk> tolvufolkService::radaDaudaHaekkandi()
{
    daudiHaekkandi temp;
    vector<tolvufolk> sorted = _folk;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaDaudaLaekkandi()
{
    daudiLaekkandi temp;
    vector<tolvufolk> sorted = _folk;
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
