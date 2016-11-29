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
void tolvufolk::updFaedingarar(int newyear)
{
    _faedingarar = newyear;
}

void tolvufolk::updDanarar(int newyear)
{
    _danarar = newyear;
}

void tolvufolk::updNafn(string newnafn)
{
    _nafn = newnafn;
}
void tolvufolk::updGender(string newgend)
{
    _kyn = newgend;
}

ostream& operator <<(ostream& out, const tolvufolk& data)
{
    out << "Name: " << data.getNafn() << endl;
    out << "Gender: " << data.getKyn() << endl;
    out << "Year of birth: " << data.getFaedingarar() << endl;
    if (data.getDanarar() == -1)
    {
        out << "Year of death: still alive" << endl;
        out << "Age: " << 2016 - data.getFaedingarar() << endl;
    }
    else
    {
        out << "Year of death: " << data.getDanarar() << endl;
        out << "Died at age: " << data.getDanarar() - data.getFaedingarar() << endl;
    }
    return out;
}
