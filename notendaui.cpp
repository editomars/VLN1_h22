#include "notendaui.h"
#include <iostream>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

//Smiður
NotendaUI::NotendaUI()
{

}

//"Main" fall
void NotendaUI::keyra()
{
    _service.yfirskrifaTolvufolk(tolvufolk("Charles Babbage", "m", 1990, 1991));
    _service.vidbotarTolvufolk(tolvufolk("Ada Lovelace", "f", 1880, 1890));
    _service.vidbotarTolvufolk(tolvufolk("zllan Turing", "m", 1918, 1948));
    _service.vidbotarTolvufolk(tolvufolk("Edit Omarsdottir", "f", 1988, -1));

    _service.saekjaGogn();

    adalvalmyndUI();
}

void NotendaUI::prentaLista(const vector<tolvufolk>& gogn)
{
    system("cls");
    hausUI();
    for (size_t i = 0; i < gogn.size(); i++)
    {
        cout << "|" << i + 1 << " \t\t ";
        cout << gogn[i];

    }
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

//------------------------------- Svæði fyrir UI greinar byrjar --------------------------------

void NotendaUI::adalvalmyndUI() //Upphaflega greinin, branchar út í aðrar UI greinar
{
    skrifaUt();

    do
    {
        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            prentaLista(_service.getTolvufolk());
        }

        else if (skipun == "sort"|| skipun == "so")
        {
            skrifaUt();
            flokkunarMoguleikar();
        }

        else if (skipun == "add" || skipun == "a")
        {
            system("cls");
            cout << "-----Adding computer scientist-----" << endl;
            baetaVidPersonu();
            prentaLista(_service.getTolvufolk());
        }

        else if (skipun == "delete" || skipun == "d")
        {
            eydaPersonu();
        }

        else if (skipun == "update" || skipun == "u")
        {
            skrifaUt();
            uppfaeraPersonu();
        }

        else if (skipun == "search" || skipun == "se")
        {
            skrifaUt();
            leitaGrein();
        }

        else if (skipun == "purge" || skipun == "p")
        {
            skrifaUt();
            tortimaLista();
        }

        else if (skipun == "quit" || skipun == "q")
        {
            cout << "Do you want to save before you quit? (Y/N): ";
            cin >> skipun;
            if(skipun == "Y" || skipun == "y")
            {
                vista();
            }
            break;
        }

        else if (skipun == "save" || skipun == "s")
        {
            vista();
        }

        else
        {
            skrifaUt();
            cerr << "Input not valid, try again: ";
        }
    } while (aframhaldandiUI());
}

void NotendaUI::baetaVidPersonu() //UI grein til að bæta við persónu
{
    do
    {
        string fornafn;
        string eftirnafn;
        string kKyn;
        int fAr;
        int dAr;

        cout << "Enter firstname: ";
        cin >> fornafn;

        cout << "Enter lastname: ";
        cin >> eftirnafn;

        cout << "Enter gender(f/m) [lowercase]: ";
        cin >> kKyn;

        while (kKyn != "m" && kKyn != "f")
        {
            cin.clear();
            cerr << "Input not valid, try again: ";
            cin >> kKyn;
        }

        cout << "Enter year of birth: ";
        cin >> fAr;

        while (0 > fAr || cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> fAr;
        }

        cout << "Enter year of death(-1 if still alive): ";
        cin >> dAr;

        while (-1 > dAr || !cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> dAr;
        }

        _service.baetaVidTolvufolk(tolvufolk(fornafn + " " + eftirnafn, kKyn, fAr, dAr));


    }while(skipunaAframhald());
}

void NotendaUI::eydaPersonu() //Delete UI grein
{
    vector<tolvufolk> gogn = _service.getTolvufolk();
    do
    {
        system("cls");
        prentaLista(_service.getTolvufolk());
        int persNR;
        cout << "Delete scientist number: ";
        cin >> persNR;
        persNR--;
        while (persNR > gogn.size() || persNR < 0)
        {
            cerr << "Input not valid, try again: ";
            cin >> persNR;
            persNR--;
        }
        _service.eydaStakiTolvufolk(persNR);

    }while(skipunaAframhald());
}

void NotendaUI::uppfaeraPersonu() //Update UI grein
{
    string skipunin;
    int persNR;
    tolvufolk target;
    system("cls");

    prentaLista(_service.getTolvufolk());

    cout << "Update scientist number: ";
    cin >> persNR;
    persNR --;
    target = _service.getStaktTolvufolk(persNR);

    system("cls");
    cout << "Update information for: " << endl << endl;
    cout << "Name: " << target.getNafn() << ",\tGender: "
         << target.getKyn() << ",\tBorn: " << target.getFaedingarar() << ",\tDied: " << target.getDanarar() << endl << endl;

    uppfaersluMoguleikar();

    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        string fornafn, eftirnafn;
        cout << "Enter updated first name: ";
        cin >> fornafn;
        cout << "Enter updated last name: ";
        cin >> eftirnafn;
        _service.uppfaeraStakTolvufolk(persNR, fornafn + " " + eftirnafn, target.getKyn(), target.getFaedingarar(), target.getDanarar());
    }

    else if (skipunin == "gender" || skipunin == "g")
    {
        string nyttKyn;
        cout << "Enter updated gender: ";
        cin >> nyttKyn;
        while (nyttKyn != "m" && nyttKyn != "f")
        {
            cerr << "Input not valid, try again: ";
            cin >> nyttKyn;
        }
        _service.uppfaeraStakTolvufolk(persNR, target.getNafn(), nyttKyn, target.getFaedingarar(), target.getDanarar());

    }

    else if (skipunin == "birth" || skipunin == "b")
    {
        int nytt;
        cout << "Enter updated year of birth: ";
        cin >> nytt;
        _service.uppfaeraStakTolvufolk(persNR, target.getNafn(), target.getKyn(), nytt, target.getDanarar());
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        int nytt;
        cout << "Enter updated year of death: ";
        cin >> nytt;
        _service.uppfaeraStakTolvufolk(persNR, target.getNafn(), target.getKyn(), target.getFaedingarar(), nytt);
    }

    else if (skipunin == "return" || skipunin == "r")
    {
        adalvalmyndUI();
    }
}

void NotendaUI::leitaGrein() //Search / Filter UI grein
{
    vector<tolvufolk> gogn = _service.getTolvufolk();
    do
    {
        leitarMoguleikar();
        string skipunin;
        cin >> skipunin;
        bool ekkiFundid = true;

        if (skipunin == "name" || skipunin == "n")
        {
            leitarMoguleikar();
            string nafn;
            cout << "Name to search: ";
            cin.ignore();
            getline(cin,nafn);
            cout << endl;
            hausUI();
            for(size_t i = 0; i < gogn.size(); i++)
            {
                if (nafn == gogn[i].getNafn() )
                {
                    cout << "|" << i + 1 << " \t\t ";
                    cout << gogn[i];
                    ekkiFundid = false;
                }

                else if (gogn.size() == (i + 1) && ekkiFundid == true )
                {
                    cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                }
            }
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
        }

        else if (skipunin == "age" || skipunin == "a")
        {
            leitarMoguleikar();
            int age;
            cout << "Age to search: ";
            cin >> age;
            cout << endl;
            hausUI();
            for(size_t i = 0; i < gogn.size(); i++)
            {
                if (age == (gogn[i].getDanarar() - gogn[i].getFaedingarar() ) )
                {
                    cout << "|" << i + 1 << " \t\t ";
                    cout << gogn[i];
                    ekkiFundid = false;
                }

                else if (gogn.size() == (i + 1) && ekkiFundid == true )
                {
                    cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                }
            }
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
        }

        else if (skipunin == "birth" || skipunin == "b")
        {
            leitarMoguleikar();
            int birth;
            cout << "Year of birth to search: ";
            cin >> birth;
            cout << endl;
            hausUI();
            for(size_t i = 0; i < gogn.size(); i++)
            {
                if (birth == gogn[i].getFaedingarar() )
                {
                    cout << "|" << i + 1 << " \t\t ";
                    cout << gogn[i];
                    ekkiFundid = false;
                }

                else if (gogn.size() == (i + 1) && ekkiFundid == true )
                {
                    cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                }
            }
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
        }

        else if (skipunin == "death" || skipunin == "d")
        {
            leitarMoguleikar();
            int death;
            cout << "Year of birth to search: ";
            cin >> death;
            cout << endl;
            hausUI();
            for(size_t i = 0; i < gogn.size(); i++)
            {
                if (death == gogn[i].getDanarar() )
                {
                    cout << "|" << i + 1 << " \t\t ";
                    cout << gogn[i];
                    ekkiFundid = false;
                }

                else if (gogn.size() == (i + 1) && ekkiFundid == true )
                {
                    cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                }
            }
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
        }

        else if (skipunin == "return" || skipunin == "r")
        {
            adalvalmyndUI();
        }

    }while(skipunaAframhald());
}

void NotendaUI::flokkunarMoguleikar() //Sort UI grein
{
    string skipunin;
    vector<tolvufolk> radad;

    rodunarMoguleikar();

    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        upphafsUI();

        cin >> skipunin;

            if(skipunin == "ascending" || skipunin == "a")
            {
                radad = _service.rada("nafn", "asc");
                prentaLista(radad);
            }

            else if(skipunin == "descending" || skipunin == "d")
            {
                radad = _service.rada("nafn", "desc");
                prentaLista(radad);
            }

            else if (skipunin == "return" || skipunin == "r")
            {
                adalvalmyndUI();
            }
    }

    else if(skipunin == "age" || skipunin == "a")
    {
        upphafsUI();

        cin >> skipunin;

            if(skipunin == "ascending" || skipunin == "a")
            {
                radad = _service.rada("aldur", "asc");
                prentaLista(radad);
            }

            else if(skipunin == "descending" || skipunin == "d")
            {
                radad = _service.rada("aldur", "desc");
                prentaLista(radad);

            }

            else if (skipunin == "return" || skipunin == "r")
            {
                adalvalmyndUI();
            }
    }

    else if(skipunin == "birth" || skipunin == "b")
    {
        upphafsUI();


        cin >> skipunin;

            if(skipunin == "ascending" || skipunin == "a")
            {
                radad = _service.rada("faedingarar", "asc");
                prentaLista(radad);
            }

            else if(skipunin == "descending" || skipunin == "d")
            {
                radad = _service.rada("faedingarar", "desc");
                prentaLista(radad);

            }

            else if (skipunin == "return" || skipunin == "r")
            {
                adalvalmyndUI();
            }
    }

    else if(skipunin == "death" || skipunin == "d")
    {
        radaUI();

        cin >> skipunin;

        if(skipunin == "ascending" || skipunin == "a")
        {
            radad = _service.rada("danarar", "asc");
            prentaLista(radad);
        }

        else if(skipunin == "descending" || skipunin == "d")
        {
            radad = _service.rada("danarar", "desc");
            prentaLista(radad);

        }
    }

    cout << "Do you want to save the sorted list? (Y/N): ";
    cin >> skipunin;
    if(skipunin == "Y" || skipunin == "y")
    {
        _service.uppfaeraTolvufolk(radad);
        vista();
    }
}

void NotendaUI::tortimaLista() //Purge UI grein
{
    string skipun;
    cout << "By the Emperor, are you sure you want to purify this database? (Y/N): ";
    cin >> skipun;

    if (skipun == "Y" || skipun == "y")
    {
        cout << "Are you really sure? This will EXTERMINATE ALL ENTRIES. (Y/N): ";
        cin >> skipun;

        if (skipun == "Y" || skipun == "y")
        {
            cout << "Acknowledged, by your will, all ENTRIES will be EXTERMINATED." << endl;

            _service.hreinsaTolvufolk();
            _service.eydaTolvufolk();
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

void NotendaUI::vista()
{
    string skipun;
    cout << "Saving will overwrite previous data, are you sure you want to continue? (Y/N): ";
    cin >> skipun;
    if (skipun == "Y" || skipun == "y")
    {
        _service.yfirskrifaTolvufolk();
        cout << "Data has been saved" << endl;
    }
    else
    {
        cout << "Saving has been cancelled" << endl;
    }
}


//------------------------------- Svæði fyrir UI greinar endar ---------------------------------

//------------------------------- Svæði fyrir bool flögg byrjar --------------------------------
bool NotendaUI::aframhaldandiUI()
{

    string svar = "o";

    while (svar != "Y" || svar != "y" || svar != "N" || svar != "n")
    {
        cout << "Continue? (Y/N): ";
        cin >> svar;

        if (svar == "Y" || svar == "y")
        {
            skrifaUt();
            return true;
        }

        else if(svar == "N" || svar == "n")
        {
            string skipun;
            cout << "Do you want to save before you quit? (Y/N): ";
            cin >> skipun;
            if(skipun == "Y" || skipun == "y")
            {
                vista();
            }
            return false;
        }

        else
        {
            cout << "Invalid input, try again!" << endl;
        }
    }
    return false;
}

bool NotendaUI::skipunaAframhald()
{

    string svar = "o";

    while (svar != "Y" || svar != "y" || svar != "N" || svar != "n")
    {
        cout << "Another entry? (Y/N): ";
        cin >> svar;

        if (svar == "Y" || svar == "y")
        {
            return true;
        }

        else if(svar == "N" || svar == "n")
        {
            return false;
        }
    }
    return false;
}


//------------------------------- Svæði fyrir bool flögg endar ---------------------------------

//------------------------------- Svæði fyrir cout blokkir byrjar ------------------------------
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
    cout << "*||sort   - Sort the entries in the database.                    ||*" << endl;
    cout << "*||purge  - Removes every entry from the database.               ||*" << endl;
    cout << "*||save   - Saves data to database.                              ||*" << endl;
    cout << "*||quit   - Exits/quits the program.                             ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::leitarMoguleikar()
{
    system("cls");

    cout << "*=========================================================================*" << endl;
    cout << "*||Please enter one of the following command                            ||*" << endl;
    cout << "*=========================================================================*" << endl;
    cout << "*||name   - Search by name, please write 'name'                         ||*" << endl;
    cout << "*||age    - Search by age, please write 'age'                           ||*" << endl;
    cout << "*||birth  - Search by year of birth, please write 'birth'               ||*" << endl;
    cout << "*||death  - Search by year of death, please write 'death'               ||*" << endl;
    cout << "*||return - Returns to the main menu                                    ||*" << endl;
    cout << "*=========================================================================*" << endl;
}

void NotendaUI::rodunarMoguleikar()
{
    system("cls");

    cout << "*=========================================================================*" << endl;
    cout << "*||Please enter one of the following command                            ||*" << endl;
    cout << "*=========================================================================*" << endl;
    cout << "*||name   - Sort by name, please write 'name'                           ||*" << endl;
    cout << "*||age    - Sort by age, please write 'age'                             ||*" << endl;
    cout << "*||birth  - Sort by year of birth, please write 'birth'                 ||*" << endl;
    cout << "*||death  - Sort by year of death, please write 'death'                 ||*" << endl;
    cout << "*||return - Returns to the main menu                                    ||*" << endl;
    cout << "*=========================================================================*" << endl;
}

void NotendaUI::uppfaersluMoguleikar()
{

    cout << "*=========================================================================*" << endl;
    cout << "*||Please enter one of the following command.                           ||*" << endl;
    cout << "*=========================================================================*" << endl;
    cout << "*||name   - update name, please write 'name'                            ||*" << endl;
    cout << "*||gender - update gender, please write 'gender'                        ||*" << endl;
    cout << "*||birth  - update year of birth, please write 'birth'                  ||*" << endl;
    cout << "*||death  - update year of death, please write 'death'                  ||*" << endl;
    cout << "*||return - Returns to the main menu                                    ||*" << endl;
    cout << "*=========================================================================*" << endl;
}

void NotendaUI::upphafsUI()
{
    system("cls");
    cout << "*=========================================================================*" << endl;
    cout << "*||Please enter one of the following command                            ||*" << endl;
    cout << "*=========================================================================*" << endl;
    cout << "*||ascending  - Sort age by ascending order                             ||*" << endl;
    cout << "*||descending - Sort age by descending order                            ||*" << endl;
    cout << "*||return     - Returns to the main menu                                ||*" << endl;
    cout << "*=========================================================================*" << endl;
}

void NotendaUI::radaUI()
{
system("cls");
cout << "*=========================================================================*" << endl;
cout << "*||Please enter one of the following command                            ||*" << endl;
cout << "*=========================================================================*" << endl;
cout << "*||ascending  - Sort age by ascending order, please write 'ascending'   ||*" << endl;
cout << "*||descending - Sort age by descending order, please write 'descending' ||*" << endl;
cout << "*=========================================================================*" << endl;
}

void NotendaUI::hausUI()
{
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Scientist ID \t |Name \t\t\t\t |Gender \t |Year of Birth  |Year of death  |Age \t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

//------------------------------- Svæðu fyrir cout blokkir endar -------------------------------
