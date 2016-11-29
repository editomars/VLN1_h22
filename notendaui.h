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
    void searchName(const vector<tolvufolk>& data);
    void updatePerson(vector<tolvufolk>& data);
private:
    tolvufolkService _service;

};

#endif // NOTENDAUI_H
