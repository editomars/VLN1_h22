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

    void printList(const vector<tolvufolk>& data);
private:
    tolvufolkService _service;
    void searchName(const vector<tolvufolk>& data);
    void skrifaUt();
    void continueUI();
    void searchOptions();
};

#endif // NOTENDAUI_H
