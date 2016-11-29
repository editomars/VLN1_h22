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
};

#endif // NOTENDAUI_H
