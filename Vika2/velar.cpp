#include "velar.h"

//Smiðir
velar::velar()
{
    _vNafn = _tegund = "None";
    _byggd = false;
    _bAr = 0;

}

velar::velar(int id, string vNafn, int bAr, string tegund, bool byggd)
{
    _id = id;
    _vNafn = vNafn;
    _bAr = bAr;
    _tegund = tegund;
    _byggd = byggd;
}

//Get föll
int velar::getID() const
{
    return _id;
}

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

bool velar::getByggd() const
{
    return _byggd;
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

void velar::uppfByggd(bool nyttByggd)
{
    _byggd = nyttByggd;
}

//ops
ostream& operator <<(ostream& out, const velar& data)
{

    string svar = "";
    if (data.getByggd() == 1)
    {
        svar = "Yes";
    }
    else
    {
        svar = "No";
    }

    //out << "Name of machine: " << data.getVelaNafn() << endl;
    //out << "Year of creation: " << data.getByggingarAr() << endl;
    //out << "Type: " << data.getTegund() << endl;
    //out << "Was it built?: " << data.getByggd() << endl;

    out << "|" << data.getVelaNafn() ;
    if(data.getVelaNafn().size() < 5)
    {
        out << "\t";
    }
    out    << " \t\t |" << data.getByggingarAr() <<  " \t\t   |" << data.getTegund() <<  " \t\t  |";
    out << svar << " \t\t\t |" << endl;


    return out;
}
