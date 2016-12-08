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
    void prentaVel(const velar kall, int i);
    void prentaVelarvensl(); //Bidur um vel og prentar ut alla venslada vid þá vél
    void prentaFolkVensl();

    //Föll sem skipta um UI grein
    void adalvalmyndUI(); //Main Menu UI grein
    void adalvalmyndUITolvuVelar(); //Menu UI grein fyrir tölvur
    void adalvalmyndUITolvuFolk(); //Menu UI grein fyrir tölvufólk
    void baetaVidPersonu(); //Add Person UI grein
    void eydaPersonu(); //Eyda personu UI grein
    void uppfaeraPersonu(); //Update Person UI grein
    void leitaGreinTolvuFolk(); //Search / Filter UI grein
    void flokkunarMoguleikarTolvuFolk(); //Sort UI grein
    void tortimaListaTolvuFolk(); //Purge UI grein
    void baetaVidVelar(); //Add velar UI grein
    void tengjaFolkiVel(); //Venlsar persónu með vél

    void eydaVel(); //Eyda vel UI grei
    void uppfaeraVelar(); //Update Machine UI grein
    void leitaGreinVelar(); //Search / Filter UI grein
    void flokkunarMoguleikarVelar(); //Sort UI grein
    void tortimaListaVelar(); //Purge UI grein

    //Bool flög
    bool aframhaldandiUITolvuVelar(); //Vantar comment
    bool aframhaldandiUITolvuFolk(); //Vantar comment
    bool aframhaldandiUIAdal(); //Vantar comment
    bool aframhaldandiUIAlmennt(); //Vantar comment
    bool skipunaAframhald(); //Vantar comment
    bool sjaVelarVensl(); //spyr hvort þú viljir sjá venslin

    //Cout blokkir

    void skrifaUt(); //Skrifa út aðalvalmynd
    void skrifaUtTolvuVelar(); //Skrifa út gluggan fyrir tölvur
    void skrifaUtTolvuFolk(); //Skrifa út gluggan fyrir tölvufólk
    void skrifaUtVal(); //Skrifa út aðal valmynd fyrir tölvur og tölvufólk
    void skipunaGluggi(); //Skrifa út gluggan fyrir ofan skipanir
    void haettaLeit(); //Skrifa út gluggan fyrir neðan leit skipanir
    void haettaSort(); //Skrifa út gluggan fyrir neðan sort skipanir
    void leitarMoguleikarTolvuFolk(); //Birtir moguleika a leitun
    void leitarMoguleikarVelar(); //Birtir moguleika a leitun
    void rodunarMoguleikarTolvuFolk(); //Birtir moguleika a rodun
    void rodunarMoguleikarVelar(); //Birtir moguleika a rodun
    void uppfaersluMoguleikar(); //Birtir moguleika a uppfaerslu
    void upphafsUI(); //Vantar comment
    void radaUINafn(); //Vantar comment
    void radaUIAldur(); //Vantar comment
    void radaUIFaedingar(); //Vantar comment
    void radaUIDaudi(); //Vantar comment
    void radaUIbAr(); //Vantar comment
    void radaUITypa(); //Vantar comment
    void radaUIByggd(); //Vantar comment
    void hausUI(); //Vantar comment
    void hausUITolvuFolk(); //Vantar comment
};

#endif // NOTENDAUI_H
