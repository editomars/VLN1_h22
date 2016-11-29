#include "notendaui.h"
#include <iostream>


using namespace std;

NotendaUI::NotendaUI()
{

}

void NotendaUI::keyra()
{
    //TEMP
    vector<tolvufolk> data;
    data.push_back(tolvufolk("Ada Lovelace", "kvk", "1880", "1890"));
    data.push_back(tolvufolk("Charles Babbage", "kk", "1900", "1920"));

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
    cin >> skipun;

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
