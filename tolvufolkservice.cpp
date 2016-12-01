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
        return (i.getNafn() < j.getNafn());
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

vector<tolvufolk> tolvufolkService::getTolvufolk(bool lesaUrGagnagrunni)
{
    if (lesaUrGagnagrunni)
        _folk = _dataaccess.lesaSkra();
    return _folk;
}

tolvufolk tolvufolkService::getStaktTolvufolk(int ndx)
{
    return _folk[ndx];
}

void tolvufolkService::eydaTolvufolk()
{
    _dataaccess.eydaSkra();
}

void tolvufolkService::vidbotarTolvufolk(const tolvufolk& t)
{
    _dataaccess.baetaVidIskra(t);
}

void tolvufolkService::vidbotarTolvufolk()
{
    for (size_t i = 0; i < _folk.size(); ++i)
    {
        _dataaccess.baetaVidIskra(_folk[i]);
    }
}

void tolvufolkService::yfirskrifaTolvufolk(const tolvufolk& t)
{
    _dataaccess.skrifaIskra(t);
}

void tolvufolkService::yfirskrifaTolvufolk()
{
    eydaTolvufolk();
    vidbotarTolvufolk();
}

void tolvufolkService::baetaVidTolvufolk(const tolvufolk &t)
{
    _folk.push_back(t);
}

void tolvufolkService::uppfaeraTolvufolk(const vector<tolvufolk>& t)
{
    _folk = t;
}

void tolvufolkService::uppfaeraStakTolvufolk(int nr, string name, string kyn, int fYear, int dYear)
{
    _folk[nr].uppfNafn(name);
    _folk[nr].uppfGender(kyn);
    _folk[nr].uppfFaedingarar(fYear);
    _folk[nr].uppfDanarar(dYear);
}

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

void tolvufolkService::hreinsaTolvufolk()

{
    _folk.clear();
}


void tolvufolkService::eydaStakiTolvufolk(int nr)
{
    _folk.erase(_folk.begin() + nr);
}

vector<tolvufolk> tolvufolkService::rada(string flokkur, string rod)
{
    if (flokkur == "nafn")
    {
        if (rod == "asc")
        {
            return radaNafniHaekkandi();
        }
        else if (rod == "desc")
        {
            return radaNafniLaekkandi();
        }
    }
    else if (flokkur == "aldur")
    {
        if (rod == "asc")
        {
            return radaAldriHaekkandi();
        }
        else if (rod == "desc")
        {
            return radaAldriLaekkandi();
        }
    }
    else if (flokkur == "faedingarar")
    {
        if (rod == "asc")
        {
            return radaFaedinguHaekkandi();
        }
        else if (rod == "desc")
        {
            return radaFaedinguLaekkandi();
        }
    }
    else if (flokkur == "danarar")
    {
        if (rod == "asc")
        {
            return radaDaudaHaekkandi();
        }
        else if (rod == "desc")
        {
            return radaDaudaLaekkandi();
        }
    }
    return _folk;
}

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
