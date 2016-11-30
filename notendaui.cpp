#include "notendaui.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

NotendaUI::NotendaUI()
{

}

bool ath = true;

void NotendaUI::keyra()
{

    _service.yfirskrifaTolvufolk(tolvufolk("Charles Babbage", "m", 1990, 1991));
    _service.vidbotarTolvufolk(tolvufolk("Ada Lovelace", "f", 1880, 1890));
    _service.vidbotarTolvufolk(tolvufolk("zllan Turing", "m", 1918, 1948));



    vector<tolvufolk> gogn = _service.getTolvufolk(true);

    skrifaUt();

    do
        {
        ath = true;
        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            system("cls");
            cout << "List of computer scientists: " << endl;
            prentaLista();
            aframhaldandiUI();
        }
        else if (skipun == "sort"|| skipun == "so")
        {
            skrifaUt();
            flokkunarMoguleikar();
            aframhaldandiUI();
        }

        else if (skipun == "add" || skipun == "a")
        {
            system("cls");
            cout << "Adding computer scientist: " << endl;
            baetaVidPersonu();
            prentaLista();
            aframhaldandiUI();
        }

        else if (skipun == "delete" || skipun == "d")
        {
            eydaPersonu();
            aframhaldandiUI();
        }

        else if (skipun == "update" || skipun == "u")
        {
            skrifaUt();
            uppfaeraPersonu(gogn);
            aframhaldandiUI();
        }

        else if (skipun == "search" || skipun == "s")
        {
            skrifaUt();
            leitaAdNafni(gogn);
            aframhaldandiUI();
        }

        else if (skipun == "purge" || skipun == "p")
        {
            skrifaUt();
            tortimaLista(gogn);


        }

        else if (skipun == "quit" || skipun == "q")
        {
            ath = true;
        }

        else
        {
            skrifaUt();
            cerr << "Input not valid, try again: ";
            ath = false;
        }
    } while (ath == false);
}

void NotendaUI::skrifaUt()
{
    system("cls");

    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following commands                    ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||list   - Shows a list of all known entries in the database.   ||*" << endl;
    cout << "*||add    - Add a new entry into the database.                   ||*" << endl;
    cout << "*||delete - Removes an entry from the database.                  ||*" << endl;
    cout << "*||update - Updates an entry from the database.                  ||*" << endl;
    cout << "*||search - Search for an entry from the database.               ||*" << endl;
    cout << "*||purge  - Removes every entry from the database.               ||*" << endl;
    cout << "*||quit   - Exits/quits the program.                             ||*" << endl;
    cout << "*==================================================================*" << endl;
}
void NotendaUI::uppfaeraPersonu(vector<tolvufolk>& gogn)
{
    system("cls");
    prentaLista();
    int persNR;
    string skipunin;
    cout << "Update scientist number: ";
    cin >> persNR;
    persNR --;

    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following command*                    ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name   - update name, please write 'name'                     ||*" << endl;
    cout << "*||gender - update gender, please write 'gender'                 ||*" << endl;
    cout << "*||birth  - update year of birth, please write 'birth'           ||*" << endl;
    cout << "*||death  - update year of death, please write 'deat'            ||*" << endl;
    cout << "*==================================================================*" << endl;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        string nafn;
        cout << "Enter updated name for " << gogn[persNR].getNafn() << ": ";
        cin.ignore();
        getline(cin,nafn);
        gogn[persNR].uppfNafn(nafn);
    }

    else if (skipunin == "gender" || skipunin == "g")
    {
        string nyttKyn;
        cout << "Enter updated gender for " << gogn[persNR].getNafn() << ": ";
        cin >> nyttKyn;
        while (nyttKyn != "f" && nyttKyn != "m")
        {
            cerr << "Input not valid, try again: ";
            cin >> nyttKyn;
        }
        gogn[persNR].uppfGender(nyttKyn);
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        int nytt;
        cout << "Enter updated year of birth for " << gogn[persNR].getNafn() << ": ";
        cin >> nytt;
        gogn[persNR].uppfFaedingarar(nytt);
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        int nytt;
        cout << "Enter updated year of death for " << gogn[persNR].getNafn() << ": ";
        cin >> nytt;
        gogn[persNR].uppfDanarar(nytt);
    }

    refreshTxtFile(gogn);

}

void NotendaUI::leitarMoguleikar()
{
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following command                     ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name  - Search by name, please write 'name'                   ||*" << endl;
    cout << "*||age   - Search by age, please write 'age'                     ||*" << endl;
    cout << "*||birth - Search by year of birth, please write 'birth'         ||*" << endl;
    cout << "*||death - Search by year of death, please write 'death'         ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::prentaLista()
{
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Scientist ID \t |Name \t\t\t\t |Gender \t |Year of Birth  |Year of death  |Age \t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    vector<tolvufolk> gogn = _service.getTolvufolk(false);

    for (size_t i = 0; i < gogn.size(); i++)
    {
        cout << "|" << i + 1 << " \t\t ";
        cout << gogn[i];
        /*
        cout << "Scientist number: " << i + 1 << endl;
        cout << data[i] << endl;
        */

    }
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

void NotendaUI::leitaAdNafni(const vector<tolvufolk>& gogn)
{
    leitarMoguleikar();
    string skipunin;
    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        leitarMoguleikar();
        string nafn;
        cout << "Name to search: ";
        cin.ignore();
        getline(cin,nafn);
        cout << endl;
        for(size_t i = 0; i < gogn.size(); i++)
        {
            if (nafn == gogn[i].getNafn() )
            {
                cout << gogn[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "age" || skipunin == "a")
    {
        leitarMoguleikar();
        int age;
        cout << "Age to search: ";
        cin >> age;
        cout << endl;
        for(size_t i = 0; i < gogn.size(); i++)
        {
            if (age == (gogn[i].getDanarar() - gogn[i].getFaedingarar() ) )
            {
                cout << gogn[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        leitarMoguleikar();
        int birth;
        cout << "Year of birth to search: ";
        cin >> birth;
        cout << endl;
        for(size_t i = 0; i < gogn.size(); i++)
        {
            if (birth == gogn[i].getFaedingarar() )
            {
                cout << gogn[i];
            }
        }
        cout << endl;
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        leitarMoguleikar();
        int death;
        cout << "Year of birth to search: ";
        cin >> death;
        cout << endl;
        for(size_t i = 0; i < gogn.size(); i++)
        {
            if (death == gogn[i].getDanarar() )
            {
                cout << gogn[i];
            }
        }
        cout << endl;
    }

}

void NotendaUI::flokkunarMoguleikar()
{
    string skipunin;

    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following command                     ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||name  - Sort by name, please write 'name'                     ||*" << endl;
    cout << "*||age   - Sort by age, please write 'age'                       ||*" << endl;
    cout << "*||birth - Sort by year of birth, please write 'birth'           ||*" << endl;
    cout << "*||death - Sort by year of death, please write 'death'           ||*" << endl;
    cout << "*==================================================================*" << endl;

    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following command                     ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||ascending  - Sort names by ascending order                    ||*" << endl;
    cout << "*||descending - Sort names by descending order                   ||*" << endl;
    cout << "*==================================================================*" << endl;

    cin >> skipunin;

        if(skipunin == "ascending" || skipunin == "a")
        {
            _service.radaEftirHaekkandi();
            prentaLista();
        }
        else if(skipunin == "descending" || skipunin == "d")
        {
            _service.radaEftirLaekkandi();
            prentaLista();
        }
    }
}

void NotendaUI::baetaVidPersonu()
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

    cout << "Enter gender(f/m) [lowercase]: ";
    cin >> gGender;

    while (gGender != "m" && gGender != "f")
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

    _service.baetaVidTolvufolk(tolvufolk(firstName + " " + lastName, gGender, bYear, dYear));

}

void NotendaUI::eydaPersonu()
{
    system("cls");
    prentaLista();
    int persNR;
    cout << "Delete scientist number: ";
    cin >> persNR;
    persNR--;
    _service.eydaStakiTolvufolk(persNR);
}

void NotendaUI::tortimaLista(vector<tolvufolk> &gogn)
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
            gogn.clear();
            refreshTxtFile(gogn);
            aframhaldandiUI();

        }
        else
        {
            cout << "Purge canceled." << endl;
            aframhaldandiUI();
        }

    }
    else
    {
        cout << "Purge canceled." << endl;
        aframhaldandiUI();
    }
}

void NotendaUI::refreshTxtFile(const vector<tolvufolk>& gogn)
{
    _service.eydaTolvufolk();
    for(size_t i = 0; i < gogn.size(); i++)
    {
         _service.vidbotarTolvufolk(gogn[i]);
    }
}

void NotendaUI::aframhaldandiUI()
{
    string answer;
    cout << "Continue? (Y/N): ";
    cin >> answer;
    if (answer == "Y" || answer == "y")
    {
        skrifaUt();
        ath = false;
    }
    else
    {
        ath = true;
    }

}
