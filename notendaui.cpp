#include "notendaui.h"
#include <iostream>
#include <string>

using namespace std;

NotendaUI::NotendaUI()
{

}

void NotendaUI::keyra()
{
    cout << "*==============================================================*" << endl;
    cout << "*||Please enter one the following commands*                  ||*" << endl;
    cout << "*==============================================================*" << endl;
    cout << "*||list - Shows a list of all known entries in the database. ||*" << endl;
    cout << "*||add - Add a new entry into the database.                  ||*" << endl;
    cout << "*||delete - Removes an entry from the database.              ||*" << endl;
    cout << "*||update - Updates an entry from the database.              ||*" << endl;
    cout << "*||purge - Removes every entry from the database.            ||*" << endl;
    cout << "*==============================================================*" << endl;

    string skipun;

    if (skipun == "list" || skipun == "l")
    {

    }

    else if (skipun == "add" || skipun == "a")
    {

    }

    else if (skipun == "delete" || skipun == "d")
    {

    }

    else if (skipun == "update" || skipun == "u")
    {

    }

    else if (skipun == "purge" || skipun == "p")
    {

    }
}
