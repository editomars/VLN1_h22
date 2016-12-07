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

    tolvufolk(int id, string fornafn, string eftirnafn, char kyn, int faedingarar, int danarar);
    //Get föll
    int getID() const;
    string getNafn() const;
    string getFornafn() const;
    string getEftirnafn() const;
    char getKyn() const;
    int getFaedingarar() const;
    int getDanarar() const;
    int getAldur() const;

    //Set föll
    void uppfFaedingarar(int nyttAr);
    void uppfDanarar(int nyttAr);

    //ops
    friend ostream& operator <<(ostream& out, const tolvufolk& gogn);
private:
    int _id;
    string _fornafn;
    string _eftirnafn;
    char _kyn;
    int _faedingarar;
    int _danarar;
};

#endif // TOLVUFOLK_H
