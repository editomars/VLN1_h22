#include "tolvufolk.h"

//Smiðir
tolvufolk::tolvufolk()
{

}

tolvufolk::tolvufolk(int id, string nafn, char kyn, int faedingarar, int danarar)
{
    _id = id;
    _nafn = nafn;
    _nafn[0] = toupper(_nafn[0]);
    _kyn = kyn;
    _danarar = danarar;
    _faedingarar = faedingarar;
}

//Get föll
int tolvufolk::getID() const
{
    return _id;
}
string tolvufolk::getNafn() const
{
       return _nafn;
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
int tolvufolk::getAldur() const
{
    return (_danarar == -1 ? constants::CURRENT_YEAR - _faedingarar : _danarar - _faedingarar);
}

//operators
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
            if (data.getNafn().length() == 0)
            {
                out << "|" << data.getNafn() << " \t\t\t\t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |Still alive \t |";

            }
            else
            {
                out << "|" << data.getNafn() << " \t\t\t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |Still alive \t |";

            }
            out << 2016- data.getFaedingarar() << " \t |" << endl;
        }

        else
        {
            if (data.getNafn().length() == 0)
            {
                out << "|" << data.getNafn() << " \t\t\t\t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |";
            }
            else
            {
                out << "|" << data.getNafn() << " \t\t\t\t |" << data.getKyn() <<  " \t\t |" << data.getFaedingarar() <<  " \t\t |";

            }
            out << data.getDanarar() <<  " \t\t |" << data.getDanarar() - data.getFaedingarar() << " \t |" << endl;
        }
    }

    else if (data.getNafn().length() < 21 && data.getNafn().length() >= 12)
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

    else if (data.getNafn().length() >= 21 && data.getNafn().length() < 29)
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
