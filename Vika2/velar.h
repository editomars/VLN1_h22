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

    velar(int id, string vNafn, int bAr, string tegund, string bygd);
    //Get föll
    int getID() const;
    string getVelaNafn() const;
    int getByggingarAr() const;
    string getTegund() const;
    string getBygd() const;
    //Set föll
    void uppfVelaNafn(string nyttvNafn);
    void uppfByggingarAr(int nyttbAr);
    void uppfTegund(int nyttTegund);
    void uppfBygd(string nyttBygd);
    //ops
    friend ostream& operator <<(ostream& out, const velar& gogn);
private:
    int _id;
    string _vNafn;
    int _bAr;
    string _tegund;
    string _bygd;
};

#endif // VELAR_H
