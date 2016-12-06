#ifndef VELAR_H
#define VELAR_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class velar
{
public:
    velar();
    velar(int id, string vNafn, int bAr, string tegund, bool byggd);

    //Get föll
    int getID() const;
    string getVelaNafn() const;
    int getByggingarAr() const;
    string getTegund() const;
    bool getByggd() const;
    //Set föll
    void uppfVelaNafn(string nyttvNafn);
    void uppfByggingarAr(int nyttbAr);
    void uppfTegund(int nyttTegund);
    void uppfByggd(bool nyttByggd);
    //ops
    friend ostream& operator <<(ostream& out, const velar& gogn);
private:
    int _id;
    string _vNafn;
    int _bAr;
    string _tegund;
    bool _byggd;
};

#endif // VELAR_H
