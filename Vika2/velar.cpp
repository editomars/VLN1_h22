#include "velar.h"

//Smiðir
velar::velar()
{
    _vNafn = _tegund = _bygd = "None";
    _bAr = 0;

}

velar::velar(string vNafn, int bAr, string tegund, string bygd)
{
    _vNafn = vNafn;
    _bAr = bAr;
    _tegund = tegund;
    _bygd = bygd;
}

//Get föll
string velar::getVelaNafn() const
{
    return _vNafn;
}

int velar::getByggingarAr() const
{
    return _bAr;
}

string velar::getTegund() const
{
    return _tegund;
}

string velar::getBygd() const
{
    return _bygd;
}

//Set föll
void velar::uppfVelaNafn(string nyttvNafn)
{
    _vNafn = nyttvNafn;
}

void velar::uppfByggingarAr(int nyttbAr)
{
    _bAr = nyttbAr;
}

void velar::uppfTegund(int nyttTegund)
{
    _tegund = nyttTegund;
}
void velar::uppfBygd(string nyttBygd)
{
    _bygd = nyttBygd;
}

//ops
ostream& operator <<(ostream& out, const velar& data)
{

    out << "Name of machine: " << data.getVelaNafn() << endl;
    out << "Year of creation: " << data.getByggingarAr() << endl;
    out << "Type: " << data.getTegund() << endl;
    out << "Was it built?: " << data.getBygd() << endl;


    /*
    if (data.getVelaNafn().length() < 13)
    {
        if (data.getBygd() == -1)
        {
            out << "|" << data.getVelaNafn() << " \t\t\t |" << data.getByggingarAr() <<  " \t\t |" << data.getTegund() <<  " \t\t |Still alive \t |";
            out << 2016- data.getTegund() << " \t |" << endl;
        }

        else
        {
            out << "|" << data.getVelaNafn() << " \t\t\t |" << data.getByggingarAr() <<  " \t\t |" << data.getTegund() <<  " \t\t |";
            out << data.getBygd() <<  " \t\t |" << data.getBygd() - data.getTegund() << " \t |" << endl;
        }
    }

    else if (data.getVelaNafn().length() < 21 && data.getVelaNafn().length() >= 12)
    {
        if (data.getBygd() == -1)
        {
            out << "|" << data.getVelaNafn() << " \t\t |" << data.getByggingarAr() <<  " \t\t |" << data.getTegund() <<  " \t\t |Still alive \t |";
            out << 2016- data.getTegund() << " \t |" << endl;
        }

        else
        {
            out << "|" << datagetVelaNafn() << " \t\t |" << data.getByggingarAr() <<  " \t\t |" << data.getTegund() <<  " \t\t |";
            out << data.getBygd() <<  " \t\t |" << data.getBygd() - data.getTegund() << " \t |" << endl;
        }
    }

    else
    {
        if (data.getBygd() == -1)
        {
            out << "|" << datagetVelaNafn() << " \t |" << data.getByggingarAr() <<  " \t\t |" << data.getTegund() <<  " \t\t |Still alive \t |";
            out << 2016- data.getTegund() << " \t |" << endl;
        }

        else
        {
            out << "|" << datagetVelaNafn() << " \t |" << data.getByggingarAr() <<  " \t\t |" << data.getTegund() <<  " \t\t |";
            out << data.getBygd() <<  " \t\t |" << data.getBygd() - data.getTegund() << " \t |" << endl;
        }
    }
    */
    return out;
}
