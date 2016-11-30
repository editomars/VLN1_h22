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
        return ((i.getDanarar()-i.getFaedingarar()) < (j.getDanarar()-j.getFaedingarar()));
    }
};
struct aldurLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return ((i.getDanarar()-i.getFaedingarar()) > (j.getDanarar()-j.getFaedingarar()));
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


vector<tolvufolk> tolvufolkService::getTolvufolk(bool readFromDatabase)
{
    if (readFromDatabase)
        _folk = _dataaccess.readToFile();
    return _folk;
}

void tolvufolkService::deleteTolvufolk()
{
    _dataaccess.deleteFile();
}

void tolvufolkService::appendTolvufolk(const tolvufolk& t)
{
    _dataaccess.appendToFile(t);
}

void tolvufolkService::appendTolvufolk(const vector<tolvufolk>& folk)
{
    for (size_t i = 0; i < folk.size(); ++i)
    {
        _dataaccess.appendToFile(folk[i]);
    }
}

void tolvufolkService::writeTolvufolk(const tolvufolk& t)
{
    _dataaccess.writeToFile(t);
}

void tolvufolkService::writeTolvufolk(const vector<tolvufolk>& folk)
{
    deleteTolvufolk();
    appendTolvufolk(folk);
}

void tolvufolkService::addTolvufolk(const tolvufolk &t)
{
    _folk.push_back(t);
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


void tolvufolkService::deleteSingleTolvufolk(int nr)
{
    _folk.erase(_folk.begin() + nr);
}
