#include "tolvufolk.h"

//Smiðir
tolvufolk::tolvufolk()
{

}

tolvufolk::tolvufolk(int id, string fornafn, string eftirnafn, char kyn, int faedingarar, int danarar)
{
    _id = id;
    _fornafn = fornafn;
    _eftirnafn = eftirnafn;
    _kyn = kyn;
    _danarar = danarar;
    _faedingarar = faedingarar;
}

//Get föll

int tolvufolk::getId() const
{
    return _id;
}
string tolvufolk::getFornafn() const
{
    return _fornafn;
}
string tolvufolk::getEftirnafn() const
{
    return _eftirnafn;
}
char tolvufolk::getKyn() const
{
    return _kyn;
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
       return _fornafn + " " + _eftirnafn;
}

//Set föll
void tolvufolk::uppfFaedingarar(int nyttAr)
{
    _faedingarar = nyttAr;
}

void tolvufolk::uppfDanarar(int nyttAr)
{
    _danarar = nyttAr;
}



//ops
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
