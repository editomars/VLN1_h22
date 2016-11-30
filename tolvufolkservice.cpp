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

<<<<<<< HEAD
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
=======
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

void tolvufolkService::sortByName()
{
    samanburdur temp;
    sort(_folk.begin(), _folk.end(), temp);
>>>>>>> 84f0b8959643ec8d1815939c546d517d452940d9
}
