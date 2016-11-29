#include "skraarvinnsla.h"
#include "tolvufolk.h"
#include <fstream>
skraarvinnsla::skraarvinnsla()
{

}

void skraarvinnsla::writeToFile(tolvufolk folk)
{
    ofstream file;
    file.open("tolvufolk.txt");
    file << folk << endl;
    file.close();
}

vector<tolvufolk> skraarvinnsla::readToFile() const
{
    string nafn;
    string kyn;
    int aldur;
    int danarar;
    vector<tolvufolk> temp;
    ifstream file;
    file.open("tolvufolk.txt");
    while (file >> nafn >> kyn >> aldur >> danarar)
    {
        tolvufolk folk(nafn, kyn, aldur, danarar);
        temp.push_back(folk);
    }

    file.close();
    return temp;
}
