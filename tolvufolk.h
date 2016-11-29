#ifndef TOLVUFOLK_H
#define TOLVUFOLK_H

#include <string>

using namespace std;

class tolvufolk
{
public:
    tolvufolk();
    tolvufolk(string nafn, string kyn, string fAr, string dAr);
    string getFaedingarar() const;
    string getDanarar() const;
    string getNafn() const;
    string getKyn() const;
private:
    string _nafn;
    string _kyn;
    string _danarar;
    string _faedingarar;
};

#endif // TOLVUFOLK_H
