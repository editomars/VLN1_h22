#ifndef NOTENDAUI_H
#define NOTENDAUI_H

#include "tolvufolk.h"
#include "tolvufolkservice.h"
#include <string>
#include <vector>

class NotendaUI
{
public:
    NotendaUI();

    void keyra();

    void baetaVidPersonu(); //Baeta vid personu UI grein
    void eydaPersonu(); //Eyda personu UI grein
    void prentaLista(); //Skrifar út gögn á console
    void leitaAdNafni(const vector<tolvufolk>& gogn);
    void uppfaeraPersonu();
    void tortimaLista();

private:
    tolvufolkService _service;
    void skrifaUt(); //Skrifa út aðalvalmynd
    bool aframhaldandiUI();
    void leitarMoguleikar();
    void flokkunarMoguleikar(); //Skrifar út sort valmöguleika notanda
    void hausUI();
};

#endif // NOTENDAUI_H
