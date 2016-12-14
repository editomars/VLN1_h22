#ifndef TOLVUFOLK_H
#define TOLVUFOLK_H

#include <string>
#include <iostream>
#include <vector>
#include "utils/constants.h"

using namespace std;

class tolvufolk
{
public:
    //Smiðir
    tolvufolk();
    tolvufolk(int id, string nafn, char kyn, int faedingarar, int danarar);

    //Get föll
    int getID() const;
    string getNafn() const;
    char getKyn() const;
    int getFaedingarar() const;
    int getDanarar() const;
    int getAldur() const;

    //operators
    friend ostream& operator <<(ostream& out, const tolvufolk& gogn);
private:
    int _id;
    string _nafn;
    char _kyn;
    int _faedingarar;
    int _danarar;
};

#endif // TOLVUFOLK_H
