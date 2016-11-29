#include "tolvufolkservice.h"

tolvufolkService::tolvufolkService()
{

}

struct samanburdur
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getNafn() < j.getNafn());
    }
};


vector<tolvufolk> tolvufolkService::getTolvufolk()
{
    _folk = _dataaccess.readToFile();
    return _folk;
}


void tolvufolkService::addTolvufolk(const tolvufolk& t)
{
    _dataaccess.writeToFile(t);
}

void tolvufolkService::addTolvufolk(const vector<tolvufolk>& folk)
{
    for (size_t i = 0; i < folk.size(); ++i)
    {
        _dataaccess.writeToFile(folk[i]);
    }
}

void tolvufolkService::sortByName()
{
    samanburdur temp;
    sort(_folk.begin(), _folk.end(), temp);

}
