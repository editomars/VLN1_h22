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

    void keyra(); //main fail
private:
    tolvufolkService _service;

    void prentaLista(const vector<tolvufolk>& gogn); //Skrifar út gögn á console

    //Föll sem skipta um UI grein
    void adalvalmyndUI(); //Main Menu UI grein
    void baetaVidPersonu(); //Add Person UI grein
    void eydaPersonu(); //Eyda personu UI grein
    void uppfaeraPersonu(); //Update Person UI grein
    void leitaGrein(); //Search / Filter UI grein
    void flokkunarMoguleikar(); //Sort UI grein
    void tortimaLista(); //Purge UI grein

    //Bool flög
    bool aframhaldandiUI(); //Vantar comment
    bool skipunaAframhald(); //Vantar comment

    //Cout blokkir
    void skrifaUt(); //Skrifa út aðalvalmynd
    void leitarMoguleikar(); //Vantar comment
    void upphafsUI(); //Vantar comment
    void radaUI(); //Vantar comment
    void hausUI(); //Vantar comment
};

#endif // NOTENDAUI_H
