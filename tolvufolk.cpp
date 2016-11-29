#include "tolvufolk.h"

tolvufolk::tolvufolk()
{
    _nafn = _kyn = _faedingarar = _danarar = "None";
}

tolvufolk::tolvufolk(string nafn, string kyn, string fAr, string dAr)
{
    _nafn = nafn;
    _kyn = kyn;
    _faedingarar = fAr;
    _danarar = dAr;
}

string tolvufolk::getFaedingarar() const
{
    return _faedingarar;
}

string tolvufolk::getDanarar() const
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
