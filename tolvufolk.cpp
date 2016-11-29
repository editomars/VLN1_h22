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
ostream& operator <<(ostream& out, const tolvufolk& data)
{
    out << "Nafn: " << data.getNafn() << endl;
    out << "Kyn: " << data.getKyn() << endl;
    out << "Faedingarar: " << data.getFaedingarar() << endl;
    out << "Danarar: " << data.getDanarar() << endl;
    return out;
}
