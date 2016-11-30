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
    void updatePerson(vector<tolvufolk>& data);
    void refreshTxtFile(const vector<tolvufolk>& data);
    void purgeList(vector<tolvufolk>& data);
private:
    tolvufolkService _service;
    void skrifaUt(); //Skrifa út aðalvalmynd
    void continueUI();
    void searchOptions();
    void sortOptions(); //Skrifar út sort valmöguleika notanda
};

#endif // NOTENDAUI_H
