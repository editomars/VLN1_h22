#include "tolvufolkservice.h"

tolvufolkService::tolvufolkService()
{

}

struct ascending
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getNafn() < j.getNafn());
    }
};
struct descending
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getNafn() > j.getNafn());
    }
};

vector<tolvufolk> tolvufolkService::getTolvufolk(bool lesaUrGagnagrunni)
{
    if (lesaUrGagnagrunni)
        _folk = _dataaccess.lesaSkra();
    return _folk;
}

void tolvufolkService::eydaTolvufolk()
{
    _dataaccess.eydaSkra();
}

void tolvufolkService::vidbotarTolvufolk(const tolvufolk& t)
{
    _dataaccess.baetaVidIskra(t);
}

void tolvufolkService::vidbotarTolvufolk(const vector<tolvufolk>& folk)
{
    for (size_t i = 0; i < folk.size(); ++i)
    {
        _dataaccess.baetaVidIskra(folk[i]);
    }
}

void tolvufolkService::yfirskrifaTolvufolk(const tolvufolk& t)
{
    _dataaccess.skrifaIskra(t);
}

void tolvufolkService::yfirskrifaTolvufolk(const vector<tolvufolk>& folk)
{
    eydaTolvufolk();
    vidbotarTolvufolk(folk);
}

void tolvufolkService::baetaVidTolvufolk(const tolvufolk &t)
{
    _folk.push_back(t);
}

void tolvufolkService::radaEftirHaekkandi()
{
    ascending temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::radaEftirLaekkandi()
{
    descending temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::eydaStakiTolvufolk(int nr)
{
    _folk.erase(_folk.begin() + nr);
}
