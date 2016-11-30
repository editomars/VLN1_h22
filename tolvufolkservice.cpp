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

void tolvufolkService::deleteTolvufolk()
{
    _dataaccess.deleteFile();
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

vector<tolvufolk> tolvufolkService::sortByName()
{
    samanburdur temp;
    sort(_folk.begin(), _folk.end(), temp);
    return _folk;

}

void tolvufolkService::displayVector(vector<tolvufolk> folk)
{
    for (vector<tolvufolk>::iterator it = folk.begin(); it!=folk.end(); ++it)
    {
        cout << ' ' << *it;
        cout << '\n';
    }
}
