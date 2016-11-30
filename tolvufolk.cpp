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
void tolvufolk::uppfFaedingarar(int nyttAr)
{
    _faedingarar = nyttAr;
}

void tolvufolk::uppfDanarar(int nyttAr)
{
    _danarar = nyttAr;
}

void tolvufolk::uppfNafn(string nyttNafn)
{
    _nafn = nyttNafn;
}
void tolvufolk::uppfGender(string nyttKyn)
{
    _kyn = nyttKyn;
}


ostream& operator <<(ostream& out, const tolvufolk& data)
{
    /*
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
    */

    if (data.getNafn().length() < 13)
    {
        if (data.getDanarar() == -1)
        {
            out << "|" << data.getNafn() << " \t\t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |Still alive \t |";
            out << 2016- data.getFaedingarar() << " \t |" << endl;
        }

        else
        {
            out << "|" << data.getNafn() << " \t\t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |";
            out << data.getDanarar() <<  " \t\t |" << data.getDanarar() - data.getFaedingarar() << " \t |" << endl;
        }
    }

    else if (data.getNafn().length() < 21 && data.getNafn().length() >= 12)
    {
        if (data.getDanarar() == -1)
        {
            out << "|" << data.getNafn() << " \t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |Still alive \t |";
            out << 2016- data.getFaedingarar() << " \t |" << endl;
        }

        else
        {
            out << "|" << data.getNafn() << " \t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |";
            out << data.getDanarar() <<  " \t\t |" << data.getDanarar() - data.getFaedingarar() << " \t |" << endl;
        }
    }

    else
    {
        if (data.getDanarar() == -1)
        {
            out << "|" << data.getNafn() << " \t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |Still alive \t |";
            out << 2016- data.getFaedingarar() << " \t |" << endl;
        }

        else
        {
            out << "|" << data.getNafn() << " \t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |";
            out << data.getDanarar() <<  " \t\t |" << data.getDanarar() - data.getFaedingarar() << " \t |" << endl;
        }
    }
    return out;
}
