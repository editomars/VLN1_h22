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

    _service.writeTolvufolk(tolvufolk("Charles Babbage", "kk", 1990, 1991));
    _service.appendTolvufolk(tolvufolk("Ada Lovelace", "kvk", 1880, 1890));
    _service.appendTolvufolk(tolvufolk("zllan Turing", "kk", 1918, 1948));



    vector<tolvufolk> data = _service.getTolvufolk(true);

    skrifaUt();

    do
        {
        check = true;
        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            system("cls");
            cout << "List of computer scientists: " << endl;
            printList();
            continueUI();
        }
        else if (skipun == "sort"|| skipun == "so")
        {
            skrifaUt();
            sortOptions();
            continueUI();
        }
        else if (skipun == "add" || skipun == "a")
        {
            system("cls");
            cout << "Adding computer scientist: " << endl;
            addPerson();
            printList();
            continueUI();

        }
        else if (skipun == "delete" || skipun == "d")
        {
            deletePerson();
            continueUI();
        }

        else if (skipun == "update" || skipun == "u")
        {

            skrifaUt();
            updatePerson();
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
            purgeList();


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

    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following commands.                      ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||list - Shows a list of all known entries in the database.     ||*" << endl;
    cout << "*||add - Add a new entry into the database.                      ||*" << endl;
    cout << "*||delete - Removes an entry from the database.                  ||*" << endl;
    cout << "*||update - Updates an entry from the database.                  ||*" << endl;
    cout << "*||search - Search for an entry from the database.               ||*" << endl;
    cout << "*||purge - Removes every entry from the database.                ||*" << endl;
    cout << "*||quit - Exits/quits the program.                               ||*" << endl;
    cout << "*==================================================================*" << endl;
}
void NotendaUI::updatePerson()
{
    string skipunin;
    int persNR;
    tolvufolk target;
    system("cls");
    printList();
    cout << "Update scientist number: ";
    cin >> persNR;
    persNR --;
    target = _service.getSingleTolvufolk(persNR);
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command.                       ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name - update name, please write 'name'                       ||*" << endl;
    cout << "*||gender - update gender, please write 'gender'                 ||*" << endl;
    cout << "*||birth - update year of birth, please write 'birth'            ||*" << endl;
    cout << "*||death - update year of death, please write 'deat'             ||*" << endl;
    cout << "*==================================================================*" << endl;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        string fornafn, eftirnafn;
        cout << "Enter updated name for " << target.getNafn() << ": ";
        cin >> fornafn >> eftirnafn;

        _service.updateTolvufolkSingle(persNR, fornafn + " " + eftirnafn, target.getKyn(), target.getFaedingarar(), target.getDanarar());
    }

    else if (skipunin == "gender" || skipunin == "g")
    {
        string newgend;
        cout << "Enter updated gender for " << target.getNafn() << ": ";
        cin >> newgend;
        while (newgend != "kk" && newgend != "kvk")
        {
            cerr << "Input not valid, try again: ";
            cin >> newgend;
        }
        _service.updateTolvufolkSingle(persNR, target.getNafn(), newgend, target.getFaedingarar(), target.getDanarar());
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        int nytt;
        cout << "Enter updated year of birth for " << target.getNafn() << ": ";
        cin >> nytt;
        _service.updateTolvufolkSingle(persNR, target.getNafn(), target.getKyn(), nytt, target.getDanarar());
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        int nytt;
        cout << "Enter updated year of death for " << target.getNafn() << ": ";
        cin >> nytt;
        _service.updateTolvufolkSingle(persNR, target.getNafn(), target.getKyn(), target.getFaedingarar(), nytt);
    }
}

void NotendaUI::searchOptions()
{
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name  - Search by name, please write 'name'                   ||*" << endl;
    cout << "*||age   - Search by age, please write 'age'                     ||*" << endl;
    cout << "*||birth - Search by year of birth, please write 'birth'         ||*" << endl;
    cout << "*||death - Search by year of death, please write 'death'         ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::printList()
{
    hausUI();
    vector<tolvufolk> data = _service.getTolvufolk(false);
    for (size_t i = 0; i < data.size(); i++)
    {
        cout << "|" << i + 1 << " \t\t ";
        cout << data[i];
        /*
        cout << "Scientist number: " << i + 1 << endl;
        cout << data[i] << endl;
        */

    }
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

void NotendaUI::searchName(const vector<tolvufolk>& data)
{
    searchOptions();
    string skipunin;
    cin >> skipunin;
    bool notFound = true;

    if (skipunin == "name" || skipunin == "n")
    {
        searchOptions();
        string nafn;
        cout << "Name to search: ";
        cin.ignore();
        getline(cin,nafn);
        hausUI();
        for(size_t i = 0; i < data.size(); i++)
        {
            if (nafn == data[i].getNafn() )
            {
                cout << "|" << i + 1 << " \t\t ";
                cout << data[i];
                notFound = false;
            }
            else if (data.size() == (i + 1) && notFound == true )
            {
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
            }
        }
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
    }

    else if (skipunin == "age" || skipunin == "a")
    {
        searchOptions();
        int age;
        cout << "Age to search: ";
        cin >> age;
        hausUI();
        for(size_t i = 0; i < data.size(); i++)
        {
            if (age == (data[i].getDanarar() - data[i].getFaedingarar() ) )
            {
                cout << "|" << i + 1 << " \t\t ";
                cout << data[i];
                notFound = false;
            }
            else if (data.size() == (i + 1) && notFound == true )
            {
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
            }
        }
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        searchOptions();
        int birth;
        cout << "Year of birth to search: ";
        cin >> birth;
        hausUI();
        for(size_t i = 0; i < data.size(); i++)
        {
            if (birth == data[i].getFaedingarar() )
            {
                cout << "|" << i + 1 << " \t\t ";
                cout << data[i];
                notFound = false;
            }
            else if (data.size() == (i + 1) && notFound == true )
            {
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
            }
        }
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        searchOptions();
        int death;
        cout << "Year of birth to search: ";
        cin >> death;
        hausUI();
        for(size_t i = 0; i < data.size(); i++)
        {
            if (death == data[i].getDanarar() )
            {
                cout << "|" << i + 1 << " \t\t ";
                cout << data[i];
                notFound = false;
            }
            else if (data.size() == (i + 1) && notFound == true )
            {
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
            }
        }
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
    }

}

void NotendaUI::sortOptions()
{
    string skipunin;

    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name - Sort by name, please write 'name'                      ||*" << endl;
    cout << "*||age - Sort by age, please write 'age'                         ||*" << endl;
    cout << "*||birth - Sort by year of birth, please write 'birth'           ||*" << endl;
    cout << "*||death - Sort by year of death, please write 'death'           ||*" << endl;
    cout << "*==================================================================*" << endl;

    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||ascending - Sort names by ascending order                     ||*" << endl;
    cout << "*||descending - Sort names by descending order                   ||*" << endl;
    cout << "*==================================================================*" << endl;

    cin >> skipunin;

        if(skipunin == "ascending" || skipunin == "a")
        {
            _service.radaNafniHaekkandi();
            printList();
        }
        else if(skipunin == "descending" || skipunin == "d")
        {
            _service.radaNafniLaekkandi();
            printList();
        }
    }

    else if(skipunin == "age" || skipunin == "a")
    {
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one the following command                        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||ascending - Sort age by ascending order                       ||*" << endl;
    cout << "*||descending - Sort age by descending order                     ||*" << endl;
    cout << "*==================================================================*" << endl;

    cin >> skipunin;

        if(skipunin == "ascending" || skipunin == "a")
        {
            _service.radaAldriHaekkandi();
            printList();
        }
        else if(skipunin == "descending" || skipunin == "d")
        {
            _service.radaAldriLaekkandi();
            printList();

        }
    }
    else if(skipunin == "birth" || skipunin == "b")
    {
        system("cls");
        cout << "*==================================================================*" << endl;
        cout << "*||Please enter one the following command                        ||*" << endl;
        cout << "*==================================================================*" << endl;
        cout << "*||ascending - Sort age by ascending order                       ||*" << endl;
        cout << "*||descending - Sort age by descending order                     ||*" << endl;
        cout << "*==================================================================*" << endl;

        cin >> skipunin;

        if(skipunin == "ascending" || skipunin == "a")
        {
            _service.radaFaedinguHaekkandi();
            printList();
        }
        else if(skipunin == "descending" || skipunin == "d")
        {
            _service.radaFaedinguLaekkandi();
            printList();

        }
    }
}

void NotendaUI::addPerson()
{
    string firstName;
    string lastName;
    string gGender;
    int bYear;
    int dYear;

    cout << "Enter firstname: ";
    cin >> firstName;

    cout << "Enter lastname: ";
    cin >> lastName;

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
    cout << endl;

    _service.addTolvufolk(tolvufolk(firstName + " " + lastName, gGender, bYear, dYear));

}

void NotendaUI::deletePerson()
{
    system("cls");
    printList();
    int persNR;
    cout << "Delete scientist number: ";
    cin >> persNR;
    persNR--;
    _service.deleteSingleTolvufolk(persNR);
}

void NotendaUI::purgeList()
{
    string skipun;
    cout << "By the Emperor, are you sure? (Y/N): ";
    cin >> skipun;

    if (skipun == "Y" || skipun == "y")
    {
        cout << "Are you really sure? This will EXTERMINATE ALL ENTRIES. (Y/N): ";
        cin >> skipun;

        if (skipun == "Y" || skipun == "y")
        {
            cout << "Acknowledged, by your will, all ENTRIES will be EXTERMINATED." << endl;
            _service.clearTolvufolk();
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
    else if(answer == "N" || answer == "n")
    {
        check = true;
    }

}

void NotendaUI::hausUI()
{
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Scientist ID \t |Name \t\t\t\t |Gender \t |Year of Birth  |Year of death  |Age \t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}
