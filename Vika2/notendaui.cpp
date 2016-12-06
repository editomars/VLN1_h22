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

    _service.saekjaGogn();
    adalvalmyndUI();
}

void NotendaUI::prentaLista(const vector<tolvufolk>& gogn)
{
    system("cls");
    hausUI();
    for (size_t i = 0; i < gogn.size(); i++)
    {
        cout << "|" << i+1 << " \t\t ";
        cout << gogn[i];

    }
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

}
void NotendaUI::prentaPersonu(const tolvufolk kall, int i)
{
    hausUI();
    cout << "|" << i+1 << " \t\t " << kall;
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
            return;
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
        char kKyn;
        int fAr;
        int dAr;

        cout << "Enter firstname: ";
        cin >> fornafn;

        cout << "Enter lastname: ";
        cin >> eftirnafn;

        cout << "Enter gender (f/m) [lowercase]: ";
        cin >> kKyn;

        while (kKyn != 'm' && kKyn != 'f')
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

        cout << "Enter year of death (-1 if still alive): ";
        cin >> dAr;

        while (-1 > dAr || !cin || (dAr < fAr && dAr != -1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> dAr;
        }

        _service.baetaVidTolvufolk(fornafn, eftirnafn, kKyn, fAr, dAr);


    }while(skipunaAframhald());
}

void NotendaUI::eydaPersonu() //Delete UI grein
{
    do
    {
        prentaLista(_service.getTolvufolk());
        int persNR;
        cout << "Delete scientist number (-1 to cancel deletion): ";
        cin >> persNR;
        while (/*persNR > _service.getSize() ||*/ persNR <= 0)
        {
            if (persNR == -1)
            {
                break;
            }
            cerr << "Input not valid, try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> persNR;
        }
        if (persNR == -1)
        {
            break;
        }
        persNR--;
        cout << _service.getStaktTolvufolk(persNR).getNafn() << " has been removed.\n";
        _service.eydaStakiTolvufolk(persNR);

    }while(skipunaAframhald());
}

void NotendaUI::uppfaeraPersonu() //Update UI grein
{
    string fornafn, eftirnafn;
    char nyttKyn;
    int persNR, nyttD, nyttF;
    tolvufolk target;

    prentaLista(_service.getTolvufolk());

    cout << "Update scientist number (-1 to cancel update): ";
    cin >> persNR;
    if (persNR == -1)
    {
        return;
    }
    while (persNR > _service.getSize() || persNR <= 0)
    {
        if (persNR == -1)
        {
            break;
        }
        cerr << "Input not valid, try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> persNR;
    }

    persNR--;
    target = _service.getStaktTolvufolk(persNR);

    system("cls");
    cout << "Updating information for: " << endl << endl;

    prentaPersonu(target, persNR);

    cout << "To hold section as is, enter 0." << endl << endl;

    cout << "Enter updated first name: ";
    cin >> fornafn;

    if (fornafn == "0")
        fornafn = target.getFornafn();

    cout << "Enter updated last name: ";
    cin >> eftirnafn;

    if (eftirnafn == "0")
        eftirnafn = target.getEftirnafn();

    cout << "Enter updated gender: ";
    cin >> nyttKyn;

    while (nyttKyn != 'm' && nyttKyn != 'f' && nyttKyn != '0')
    {
        cerr << "Input not valid, try again: ";
        cin >> nyttKyn;
    }

    if (nyttKyn == '0')
        nyttKyn = target.getKyn();

    do
    {
        cout << "Enter updated year of birth: ";
        cin >> nyttF;

        while (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> nyttF;
        }

        if (nyttF == 0)
            nyttF = target.getFaedingarar();


        cout << "Enter updated year of death: ";
        cin >> nyttD;

        while (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> nyttD;
        }

        if (nyttD == 0)
            nyttD = target.getDanarar();

        if (nyttD < nyttF && nyttD != -1)
        {
            cout << "Year of death is lower than birthyear, try again." << endl;
        }



    }while(nyttD < nyttF && nyttD != -1);


    _service.uppfaeraStakTolvufolk(target.getId(), fornafn, eftirnafn, nyttKyn, nyttF, nyttD);

    system("cls");
    cout << "Updated information:" << endl << endl;
    prentaPersonu((_service.getStaktTolvufolk(persNR)), persNR);

}

void NotendaUI::leitaGrein() //Search / Filter UI grein
{
    vector<tolvufolk> gogn;
    do
    {
        leitarMoguleikar();
        string skipunin;
        cin >> skipunin;

        if (skipunin == "name" || skipunin == "n")
        {
            leitarMoguleikar();
            string fornafn, eftirnafn;
            cout << "---Searching by name---" << endl;
            cout << "Enter first name: ";
            cin >> fornafn;
            cout << "Enter last name: ";
            cin >> eftirnafn;
            cout << endl;
            gogn = _service.leitaStreng("nafn", fornafn + " " + eftirnafn);
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaLista(gogn);
            }
        }

        else if (skipunin == "age" || skipunin == "a")
        {
            int age;
            leitarMoguleikar();
            cout << "Age to search: ";
            cin >> age;
            while (-1 > age || !cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Input not valid, try again: ";
                cin >> age;
            }
            cout << endl;
            gogn = _service.leitaHeiltolu("aldur", age);
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaLista(gogn);
            }
        }

        else if (skipunin == "birth" || skipunin == "b")
        {
            leitarMoguleikar();
            int birth;
            cout << "Year of birth to search: ";
            cin >> birth;
            while (-1 > birth || !cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Input not valid, try again: ";
                cin >> birth;
            }
            cout << endl;
            gogn = _service.leitaHeiltolu("faedingarar", birth);
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaLista(gogn);
            }
        }

        else if (skipunin == "death" || skipunin == "d")
        {
            leitarMoguleikar();
            int death;
            cout << "Year of death to search (-1 for still alive): ";
            cin >> death;
            while (-2 > death || !cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Input not valid, try again: ";
                cin >> death;
            }
            cout << endl;
            gogn = _service.leitaHeiltolu("danarar", death);
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaLista(gogn);
            }
        }

        else if (skipunin == "quit" || skipunin == "q")
        {
            return;
        }

        else
        {
            cout << "Invalid input, try again: ";
        }

    }while(skipunaAframhald());
}

void NotendaUI::flokkunarMoguleikar() //Sort UI grein
{
    string skipunin;
    vector<tolvufolk> radad;
    bool rettInntak = true;
    rodunarMoguleikar();

    do
    {
        rettInntak = true;
        cin >> skipunin;


        if (skipunin == "name" || skipunin == "n")
        {
            radaUI();

            do
            {
                rettInntak = true;

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

                else if (skipunin == "quit" || skipunin == "q")
                {
                    return;
                }

                else
                {
                    cout << "Invalid input, try again: ";
                    rettInntak = false;
                }
            }while(rettInntak == false);
        }

        else if(skipunin == "age" || skipunin == "a")
        {
            radaUI();

            do
            {
                rettInntak = true;

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

                else if (skipunin == "quit" || skipunin == "q")
                {
                    return;
                }

                else
                {
                    cout << "Invalid input, try again: ";
                    rettInntak = false;
                }
            }while(rettInntak == false);
        }

        else if(skipunin == "birth" || skipunin == "b")
        {
            radaUI();

            do
            {
                rettInntak = true;
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

                else if (skipunin == "quit" || skipunin == "q")
                {
                    return;
                }

                else
                {
                    cout << "Invalid input, try again: ";
                    rettInntak = false;
                }

            }while(rettInntak == false);
        }

        else if(skipunin == "death" || skipunin == "d")
        {
            radaUI();

            do
            {
                rettInntak = true;
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

                else if (skipunin == "quit" || skipunin == "q")
                {
                    return;
                }

                else
                {
                    cout << "Invalid input, try again: ";
                    rettInntak = false;
                }

            }while(rettInntak == false);
        }

        else if (skipunin == "quit" || skipunin == "q")
        {
            return;
        }

        else
        {
            cout << "Invalid input, try again: ";
            rettInntak = false;
        }

    }while(rettInntak == false);
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

            _service.tortimaTolvufolk();

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

//------------------------------- Svæði fyrir UI greinar velar ---------------------------------

void NotendaUI::baetaVidVelar() //UI grein til að bæta við vel.
{
    do
    {
        string vNafn;
        int bAr;
        string tegund;
        char byggdIn;
        bool byggd;

        cout << "Enter machine name: ";
        cin >> vNafn;

        cout << "Enter year built: ";
        cin >> bAr;

        while (0 > bAr || cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> bAr;
        }

        cout << "Enter type: ";
        cin >> tegund;

        cout << "Was it built? (y/n)";
        cin >> byggdIn;

        if(byggdIn == 'y' || byggdIn == 'Y')
        {
            byggd = true;
        }
        else if(byggdIn == 'n' || byggdIn == 'N')
        {
            byggd = false;
        }


        _vService.baetaVidVelar(vNafn, bAr, byggd, tegund);

    }while(skipunaAframhald());
}

//------------------------------- Svæði fyrir UI greinar endar ---------------------------------

//------------------------------- Svæði fyrir bool flögg byrjar --------------------------------
bool NotendaUI::aframhaldandiUI()
{
    string svar = "o";

    while (svar != "Y" || svar != "y" || svar != "N" || svar != "n")
    {
        cout << "Return to Main Menu? (Y/N): ";
        cin >> svar;

        if (svar == "Y" || svar == "y")
        {
            skrifaUt();
            return true;
        }

        else if(svar == "N" || svar == "n")
        {
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
    cout << "*||quit   - Exits/quits the program.                             ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::leitarMoguleikar()
{
    system("cls");

    cout << "*=========================================================================*" << endl;
    cout << "*||Please enter one of the following command                            ||*" << endl;
    cout << "*=========================================================================*" << endl;
    cout << "*||name   - Search by name, please write 'name'.                        ||*" << endl;
    cout << "*||age    - Search by age, please write 'age'.                          ||*" << endl;
    cout << "*||birth  - Search by year of birth, please write 'birth'.              ||*" << endl;
    cout << "*||death  - Search by year of death, please write 'death'.              ||*" << endl;
    cout << "*||quit   - Quit searching.                                             ||*" << endl;
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
    cout << "*||quit   - Quit sorting.                                               ||*" << endl;
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
cout << "*||quit   - Quit sorting.                                               ||*" << endl;
cout << "*=========================================================================*" << endl;
}

void NotendaUI::hausUI()
{
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Scientist ID \t |Name \t\t\t\t |Gender \t |Year of Birth  |Year of death  |Age \t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}
//------------------------------- Svæðu fyrir cout blokkir endar -------------------------------
