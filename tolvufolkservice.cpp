#include "tolvufolkservice.h"

tolvufolkService::tolvufolkService()
{

}

//Sort name by ascending order
struct nafnHaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getNafn() < j.getNafn());
    }
};
//Sort name by descending order
struct nafnLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getNafn() > j.getNafn());
    }
};
//Sort age by ascending order
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


vector<tolvufolk> tolvufolkService::getTolvufolk(bool lesaUrGagnagrunni)
{
    if (lesaUrGagnagrunni)
        _folk = _dataaccess.lesaSkra();
    return _folk;
}

tolvufolk tolvufolkService::getSingleTolvufolk(int ndx)
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

void tolvufolkService::updateTolvufolkSingle(int nr, string name, string kyn, int fYear, int dYear)
{
    _folk[nr].uppfNafn(name);
    _folk[nr].uppfGender(kyn);
    _folk[nr].uppfFaedingarar(fYear);
    _folk[nr].uppfDanarar(dYear);
}

void tolvufolkService::clearTolvufolk()

{
    _folk.clear();
}

void tolvufolkService::radaNafniHaekkandi()
{
    nafnHaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::radaNafniLaekkandi()
{
    nafnLaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::radaAldriHaekkandi()
{
    aldurHaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}
void tolvufolkService::radaAldriLaekkandi()
{
    aldurLaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}
void tolvufolkService::radaFaedinguHaekkandi()
{
    faedingHaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}
void tolvufolkService::radaFaedinguLaekkandi()
{
    faedingLaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}
void tolvufolkService::radaDaudaHaekkandi()
{
    daudiHaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}
void tolvufolkService::radaDaudaLaekkandi()
{
    daudiLaekkandi temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::eydaStakiTolvufolk(int nr)
{
    _folk.erase(_folk.begin() + nr);
}
