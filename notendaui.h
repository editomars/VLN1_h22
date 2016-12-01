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
private:
    tolvufolkService _service;

    void prentaLista(const vector<tolvufolk>& gogn); //Skrifar út gögn á console

    //Föll sem skipta um UI grein
    void adalvalmyndUI();
    void baetaVidPersonu(); //Baeta vid personu UI grein
    void eydaPersonu(); //Eyda personu UI grein
    void uppfaeraPersonu();
    void leitaGrein();
    void flokkunarMoguleikar(); //Skrifar út sort valmöguleika notanda
    void tortimaLista();

    //Cout blokkir
    void skrifaUt(); //Skrifa út aðalvalmynd
    void leitarMoguleikar();
    void upphafsUI();
    void hausUI();

    //Bool flög
    bool aframhaldandiUI();
    bool skipunaAframhald();
};

#endif // NOTENDAUI_H
