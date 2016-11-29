#include "tolvufolkservice.h"

tolvufolkService::tolvufolkService()
{

}

vector<tolvufolk> tolvufolkService::getTolvufolk() const
{
    return _dataaccess.readToFile();
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
