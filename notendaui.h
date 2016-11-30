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

    void addPerson(); //Add person UI grein
    void deletePerson(); //delete person UI grein
    void printList(); //Skrifar út gögn á console
    void searchName(const vector<tolvufolk>& data);
    void updatePerson();
    void purgeList();
private:
    tolvufolkService _service;
    void skrifaUt(); //Skrifa út aðalvalmynd
    void continueUI();
    void searchOptions();
    void sortOptions(); //Skrifar út sort valmöguleika notanda
    void hausUI();
};

#endif // NOTENDAUI_H
