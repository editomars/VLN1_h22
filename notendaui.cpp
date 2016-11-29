#include "notendaui.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

NotendaUI::NotendaUI()
{

}



bool check = true;

void NotendaUI::keyra()
{
    //TEMP
    vector<tolvufolk> data;
    data.push_back(tolvufolk("Ada Lovelace", "kvk", 1880, 1890));
    data.push_back(tolvufolk("Charles Babbage", "kk", 1900, 1920));

    string nName;
    string gGender;
    int bYear;
    int dYear;

    skrifaUt();

    do
        {
        check = true;
        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            skrifaUt();
            printList(data);
            continueUI();
        }
        else if (skipun == "add" || skipun == "a")
        {
            skrifaUt();
            cout << "Enter name: ";
            cin >> nName;

            cout << "Enter gender(kk/kvk) [lowercase]: ";
            cin >> gGender;

            while (gGender != "kk" && gGender != "kvk")
            {
                cerr << "Input not valid, try again: ";
                cin >> gGender;
            }

            cout << "Enter year of birth: ";
            cin >> bYear;

            while (0 > bYear)
            {
                cerr << "Input not valid, try again: ";
                cin >> bYear;
            }

            cout << "Enter year of death(-1 if still alive): ";
            cin >> dYear;

            while (-1 > dYear)
            {
                cerr << "Input not valid, try again: ";
                cin >> dYear;
                cout << endl;
            }

            data.push_back(tolvufolk(nName, gGender, bYear, dYear));
            printList(data);
            continueUI();

        }
        else if (skipun == "delete" || skipun == "d")
        {
            skrifaUt();
            printList(data);
            continueUI();

        }

        else if (skipun == "update" || skipun == "u")
        {
            skrifaUt();

            continueUI();
        }

        else if (skipun == "search" || skipun == "s")
        {
            skrifaUt();
            searchName(data);
            continueUI();
        }

        else if (skipun == "purge" || skipun == "p")
        {
            skrifaUt();
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
                    continueUI();

                }
                else
                {
                    cout << "Purge canceled." << endl;
                    continueUI();
                }

            }
            else
            {
                cout << "Purge canceled." << endl;
                continueUI();
            }


        }

        else if (skipun == "quit" || skipun == "q")
        {
            check = true;
        }

        else
        {
            skrifaUt();
            cerr << "Input not valid, try again: ";
            check = false;
        }
    } while (check == false);
}

void NotendaUI::skrifaUt()
{
    system("cls");
    cout << "*==============================================================*" << endl;
    cout << "*||Please enter one the following commands                   ||*" << endl;
    cout << "*==============================================================*" << endl;
    cout << "*||list - Shows a list of all known entries in the database. ||*" << endl;
    cout << "*||add - Add a new entry into the database.                  ||*" << endl;
    cout << "*||delete - Removes an entry from the database.              ||*" << endl;
    cout << "*||update - Updates an entry from the database.              ||*" << endl;
    cout << "*||search - Search for an entry from the database.           ||*" << endl;
    cout << "*||purge - Removes every entry from the database.            ||*" << endl;
    cout << "*||quit - Exits/quits the program                            ||*" << endl;
    cout << "*==============================================================*" << endl;
}
void NotendaUI::searchOptions()
{
    system("cls");
    cout << "*==============================================================*" << endl;
    cout << "*||Please enter one the following command                    ||*" << endl;
    cout << "*==============================================================*" << endl;
    cout << "*||name - Search by name                                     ||*" << endl;
    cout << "*||age - Search by age                                       ||*" << endl;
    cout << "*||birth - Search by year of birth                           ||*" << endl;
    cout << "*||death - Search by year of death                           ||*" << endl;
    cout << "*==============================================================*" << endl;
}

void NotendaUI::printList(const vector<tolvufolk>& data)
{
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << data[i] << endl;
    }
}

void NotendaUI::searchName(const vector<tolvufolk>& data)
{
    searchOptions();
    string skipunin;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        searchOptions();
        string nafn;
        cout << "Name to search: ";
        cin.ignore();
        getline(cin,nafn);
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (nafn == data[i].getNafn() )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "age" || skipunin == "a")
    {
        searchOptions();
        int age;
        cout << "Age to search: ";
        cin >> age;
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (age == (data[i].getDanarar() - data[i].getFaedingarar() ) )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        searchOptions();
        int birth;
        cout << "Year of birth to search: ";
        cin >> birth;
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (birth == data[i].getFaedingarar() )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        searchOptions();
        int death;
        cout << "Year of birth to search: ";
        cin >> death;
        cout << endl;
        for(size_t i = 0; i < data.size(); i++)
        {
            if (death == data[i].getDanarar() )
            {
                cout << data[i];
            }
        }
        cout << endl;
    }

}

void NotendaUI::continueUI()
{
    string answer;
    cout << "Continue? (Y/N): ";
    cin >> answer;
    if (answer == "Y" || answer == "y")
    {
        skrifaUt();
        check = false;
    }
    else
    {
        check = true;
    }

}
