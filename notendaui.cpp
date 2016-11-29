#include "notendaui.h"
#include <iostream>


using namespace std;

NotendaUI::NotendaUI()
{

}

void Skrifaut()
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
}

bool check = true;

void NotendaUI::keyra()
{
    //TEMP
    vector<tolvufolk> data;
    data.push_back(tolvufolk("Ada Lovelace", "kvk", 1880, 1890));
    data.push_back(tolvufolk("Charles Babbage", "kk", 1900, 1920));

    Skrifaut();

    do
        {
        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            printList(data);
        }
        else if (skipun == "add" || skipun == "a")
        {
            cout << "Enter name:";
            cout << "Enter gender:";
            cout << "Enter year of birth:";
            cout << "Enter year of death(if any):";

        }
        else if (skipun == "delete" || skipun == "d")
        {

        }

        else if (skipun == "update" || skipun == "u")
        {

        }

        else if (skipun == "purge" || skipun == "p")
        {
            cout << "By the Emperor, are you sure? (Y/N): ";
            cin >> skipun;

            if (skipun == "Y" || skipun == "y")
            {
                cout << "Are you really sure? This will EXTERMINATE ALL ENTRIES. (Y/N): ";
                cin >> skipun;

                if (skipun == "Y" || skipun == "y")
                {
                    cout << "Acknowledged, by your will, all ENTRIES will be EXTERMINATED.";
                    // TODO; Erase everything

                }
                else
                {
                    cout << "Purge canceled." << endl;
                }

            }
            else
            {
                cout << "Purge canceled." << endl;
            }


        }

        else
        {
            system("cls");
            Skrifaut();
            cerr << "Input not valid, try again: ";
            check = false;
        }
    } while (check == false);
}

void NotendaUI::printList(const vector<tolvufolk>& data)
{
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << endl;
    }
}
