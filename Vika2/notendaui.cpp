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
            do
            {
                cin >> skipun;
                if(skipun == "Y" || skipun == "y")
                {
                    vista();
                }
                else if (skipun != "n" && skipun != "N")
                {
                    cout << "Invalid input, try again: ";
                }
            }while(skipun != "y" && skipun != "Y" && skipun != "n" && skipun != "N");
            return;
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

        cout << "Enter gender (f/m) [lowercase]: ";
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

        cout << "Enter year of death (-1 if still alive): ";
        cin >> dAr;

        while (-1 > dAr || !cin || (dAr < fAr && dAr != -1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> dAr;
        }

       // _service.baetaVidTolvufolk(tolvufolk(fornafn + " " + eftirnafn, kKyn, fAr, dAr));


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
    string skipunin;
    int persNR;
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
    persNR --;
    target = _service.getStaktTolvufolk(persNR);

    system("cls");
    cout << "Update information for: " << endl << endl;
    cout << "Name: " << target.getNafn() << ",\tGender: "
         << target.getKyn() << ",\tBorn: " << target.getFaedingarar() << ",\tDied: "
         << target.getDanarar() << endl << endl;

    uppfaersluMoguleikar();

    cin >> skipunin;

    if (skipunin == "name" || skipunin == "n")
    {
        string fornafn, eftirnafn;
        cout << "Enter updated first name: ";
        cin >> fornafn;
        cout << "Enter updated last name: ";
        cin >> eftirnafn;
        //_service.uppfaeraStakTolvufolk(persNR, fornafn + " " + eftirnafn, target.getKyn(), target.getFaedingarar(), target.getDanarar());
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

        while ((nytt > target.getDanarar() && target.getDanarar() != -1) || !cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, birthyear is higher than year of death, try again: ";
            cin >> nytt;
        }
       // _service.uppfaeraStakTolvufolk(persNR, target.getNafn(), target.getKyn(), nytt, target.getDanarar());
    }

    else if (skipunin == "death" || skipunin == "d")
    {
        int nytt;
        cout << "Enter updated year of death: ";
        cin >> nytt;
      //  _service.uppfaeraStakTolvufolk(persNR, target.getNafn(), target.getKyn(), target.getFaedingarar(), nytt);
    }

    else if (skipunin == "quit" || skipunin == "q")
    {
        return;
    }

    else
    {
        cout << "Invalid input, try again: ";
    }
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

    cout << "Do you want to save the sorted list? (Y/N): ";
    do
    {
        cin >> skipunin;
        if(skipunin == "Y" || skipunin == "y")
        {
            vista();
            _service.uppfaeraTolvufolk(radad);
        }
        else if (skipunin != "n" && skipunin != "N")
        {
            cout << "Invalid input, try again: ";
        }
    }while(skipunin != "y" && skipunin != "Y" && skipunin != "n" && skipunin != "N");
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
        cout << "Return to Main Menu? (Y/N): ";
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
            do
            {
                cin >> skipun;
                if(skipun == "Y" || skipun == "y")
                {
                    vista();
                }
                else if (skipun != "n" && skipun != "N")
                {
                    cout << "Invalid input, try again: ";
                }
            }while(skipun != "y" && skipun != "Y" && skipun != "n" && skipun != "N");
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

void NotendaUI::uppfaersluMoguleikar()
{

    cout << "*=========================================================================*" << endl;
    cout << "*||Please enter one of the following command.                           ||*" << endl;
    cout << "*=========================================================================*" << endl;
    cout << "*||name   - update name, please write 'name'                            ||*" << endl;
    cout << "*||gender - update gender, please write 'gender'                        ||*" << endl;
    cout << "*||birth  - update year of birth, please write 'birth'                  ||*" << endl;
    cout << "*||death  - update year of death, please write 'death'                  ||*" << endl;
    cout << "*||quit   - Quit updating.                                              ||*" << endl;
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
    system("cls");
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Scientist ID \t |Name \t\t\t\t |Gender \t |Year of Birth  |Year of death  |Age \t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}
//------------------------------- Svæðu fyrir cout blokkir endar -------------------------------
