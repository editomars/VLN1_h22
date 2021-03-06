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
    _vNafn[0] = toupper(_vNafn[0]);
    _bAr = bAr;
    _tegund = tegund;
    _tegund[0] = toupper(_tegund[0]);
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

    out << "|" << data.getVelaNafn();
    if(data.getVelaNafn().size() <= 6)
    {
        out << "\t\t";
    }
    else if(data.getVelaNafn().size() > 6 && data.getVelaNafn().size() < 13)
    {
        out << "\t";
    }
    out << " \t |" << data.getByggingarAr() <<  " \t\t   |" << data.getTegund();
    if (data.getTegund().size() < 3)
    {
        out << "\t";
    }
    if (data.getTegund().size() < 11)
    {
        out <<  " \t";
    }
    out << "  \t  |" << svar << " \t\t\t |" << endl;


    return out;
}
