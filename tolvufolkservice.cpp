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

void tolvufolkService::sortByAscending()
{
    ascending temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::sortByDescending()
{
    descending temp;
    sort(_folk.begin(), _folk.end(), temp);
}

void tolvufolkService::deleteSingleTolvufolk(int nr)
{
    _folk.erase(_folk.begin() + nr);
}
