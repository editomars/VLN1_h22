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

    void addPerson(vector<tolvufolk>& data);
    void deletePerson(vector<tolvufolk>& data);
    void printList(const vector<tolvufolk>& data);
    void searchName(const vector<tolvufolk>& data);
    void updatePerson(vector<tolvufolk>& data);
    void refreshTxtFile(const vector<tolvufolk>& data);
    void purgeList(vector<tolvufolk>& data);
private:
    tolvufolkService _service;
    void skrifaUt();
    void continueUI();
    void searchOptions();
    void sortOptions(vector<tolvufolk>& data);
};

#endif // NOTENDAUI_H
