#include "skraarvinnsla.h"

skraarvinnsla::skraarvinnsla()
{

}

void skraarvinnsla::baetaVidIskra(const tolvufolk& folk)
{
    ofstream file;
    file.open("tolvufolk.txt", ios::app);
    file << folk.getNafn() << " " << folk.getKyn() << " " << folk.getFaedingarar() << " " << folk.getDanarar() << endl;
    file.close();
}

void skraarvinnsla::skrifaIskra(const tolvufolk& folk)
{
    ofstream file;
    file.open("tolvufolk.txt");
    file << folk.getNafn() << " " << folk.getKyn() << " " << folk.getFaedingarar() << " " << folk.getDanarar() << endl;
    file.close();
}

void skraarvinnsla::eydaSkra()
{
    remove("tolvufolk.txt");
}

vector<tolvufolk> skraarvinnsla::lesaSkra() const
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
