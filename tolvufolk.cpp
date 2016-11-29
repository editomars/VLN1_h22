#include "tolvufolk.h"

tolvufolk::tolvufolk()
{
    _nafn = _kyn = "None";
    _faedingarar = _danarar = 0;
}

tolvufolk::tolvufolk(string nafn, string kyn, int fAr, int dAr)
{
    _nafn = nafn;
    _kyn = kyn;
    _faedingarar = fAr;
    _danarar = dAr;
}

int tolvufolk::getFaedingarar() const
{
    return _faedingarar;
}

int tolvufolk::getDanarar() const
{
    return _danarar;
}

string tolvufolk::getNafn() const
{
    return _nafn;
}

string tolvufolk::getKyn() const
{
    return _kyn;
}
