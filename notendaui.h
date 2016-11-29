#ifndef NOTENDAUI_H
#define NOTENDAUI_H

#include "tolvufolk.h"
#include <string>
#include <vector>

class NotendaUI
{
public:
    NotendaUI();

    void keyra();

    void printList(const vector<tolvufolk>& data);

    void searchName(const vector<tolvufolk>& data);
};

#endif // NOTENDAUI_H
