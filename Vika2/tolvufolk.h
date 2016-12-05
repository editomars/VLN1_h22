#ifndef TOLVUFOLK_H
#define TOLVUFOLK_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class tolvufolk
{
public:
    tolvufolk();

    tolvufolk(string nafn, string kyn, int fAr, int dAr);
    //Get föll
    int getFaedingarar() const;
    int getDanarar() const;
    string getNafn() const;
    string getKyn() const;
    //Set föll
    void uppfFaedingarar(int nyttAr);
    void uppfDanarar(int nyttAr);
    void uppfNafn(string nyttNafn);
    void uppfGender(string nyttKyn);
    //ops
    friend ostream& operator <<(ostream& out, const tolvufolk& gogn);
private:
    string _nafn;
    string _kyn;
    int _danarar;
    int _faedingarar;
};

#endif // TOLVUFOLK_H
