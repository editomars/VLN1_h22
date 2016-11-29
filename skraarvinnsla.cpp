#include "skraarvinnsla.h"

skraarvinnsla::skraarvinnsla()
{

}

void skraarvinnsla::writeToFile(const tolvufolk& folk)
{
    ofstream file;
    file.open("tolvufolk.txt", ios::app);
    file << folk.getNafn() << " " << folk.getKyn() << " " << folk.getFaedingarar() << " " << folk.getDanarar() << endl;
    file.close();
}

vector<tolvufolk> skraarvinnsla::readToFile() const
{
    string fornafn;
    string eftirnafn;
    string kyn;
    int aldur;
    int danarar;
    vector<tolvufolk> temp;
    ifstream file;
    file.open("tolvufolk.txt");
    while (file >> fornafn >> eftirnafn >> kyn >> aldur >> danarar)
    {
        tolvufolk folk(fornafn + " " + eftirnafn, kyn, aldur, danarar);
        temp.push_back(folk);
    }

    file.close();
    return temp;
}
