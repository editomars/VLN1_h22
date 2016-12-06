#ifndef NOTENDAUI_H
#define NOTENDAUI_H

#include "tolvufolk.h"
#include "tolvufolkservice.h"
#include "velar.h"
#include "velarservice.h"
#include <string>
#include <vector>

class NotendaUI
{
public:
    NotendaUI();

    void keyra(); //main fail
private:
    tolvufolkService _service;
    velarService _vService;
    void prentaListaTolvuFolk(const vector<tolvufolk>& gogn); //Skrifar út gögn á console
    void prentaListaTolvuVelar(const vector<velar>& gogn); //Skrifar út gögn á console
    void prentaPersonu(const tolvufolk kall, int i);

    //Föll sem skipta um UI grein
    void adalvalmyndUI(); //Main Menu UI grein
    void adalvalmyndUITolvuVelar(); //Menu UI grein fyrir tölvur
    void adalvalmyndUITolvuFolk(); //Menu UI grein fyrir tölvufólk
    void adalvalmyndUILinked(); //Menu UI grein fyrir bæði tölvufólk og tölvur
    void baetaVidPersonu(); //Add Person UI grein
    void eydaPersonu(); //Eyda personu UI grein
    void uppfaeraPersonu(); //Update Person UI grein
    void leitaGrein(); //Search / Filter UI grein
    void flokkunarMoguleikar(); //Sort UI grein
    void tortimaLista(); //Purge UI grein
    void baetaVidVelar(); //Add velar UI grein
    void eydaVel(); //Eyda vel UI grei

    //Bool flög
    bool aframhaldandiUITolvuVelar(); //Vantar comment
    bool aframhaldandiUITolvuFolk(); //Vantar comment
    bool aframhaldandiUILinked(); //Vantar comment
    bool aframhaldandiUIAdal(); //Vantar comment
    bool skipunaAframhald(); //Vantar comment

    //Cout blokkir
    void skrifaUt(); //Skrifa út aðalvalmynd
    void skrifaUtTolvuVelar(); //Skrifa út valmynd fyrir tölvur
    void skrifaUtTolvuFolk(); //Skrifa út valmynd fyrir tölvufólk
    void skrifaUtLinked(); // skrifa út valmynd fyri bæði tölvur og tölvufólk
    void leitarMoguleikar(); //Birtir moguleika a leitun
    void rodunarMoguleikar(); //Birtir moguleika a rodun
    void uppfaersluMoguleikar(); //Birtir moguleika a uppfaerslu
    void upphafsUI(); //Vantar comment
    void radaUI(); //Vantar comment
    void hausUI(); //Vantar comment
    void hausUITolvuFolk(); //Vantar comment
};

#endif // NOTENDAUI_H
