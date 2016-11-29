#ifndef TOLVUFOLK_H
#define TOLVUFOLK_H

#include <string>

using namespace std;

class tolvufolk
{
public:
    tolvufolk();
    tolvufolk(string nafn, string kyn, int fAr, int dAr);
    int getFaedingarar() const;
    int getDanarar() const;
    string getNafn() const;
    string getKyn() const;
private:
    string _nafn;
    string _kyn;
    int _danarar;
    int _faedingarar;
};

#endif // TOLVUFOLK_H
