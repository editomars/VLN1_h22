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

void NotendaUI::prentaListaTolvuFolk(const vector<tolvufolk>& gogn)
{
    system("cls");
    hausUITolvuFolk();
    for (size_t i = 0; i < gogn.size(); i++)
    {
        cout << "|" << i+1 << " \t\t ";
        cout << gogn[i];
    }
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

}

void NotendaUI::prentaListaTolvuVelar(const vector<velar>& gogn)
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
    hausUITolvuFolk();
    cout << "|" << i+1 << " \t\t " << kall;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

}

void NotendaUI::prentaVel(const velar kall, int i)
{
    hausUI();
    cout << "|" << i+1 << " \t\t " << kall;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;

}

void NotendaUI::prentaFolkVensl()
{
    int persNR;
    int ID;
    tolvufolk target;
    vector<tolvufolk> gogn = _service.getTolvufolk();

    cout << "Enter number of scientist you want to see linked machines with: ";
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
    ID = gogn[persNR].getID();
    target = _service.getStaktTolvufolk(ID);

    system("cls");
    prentaListaTolvuVelar(_vService.getVelarVensl(ID));

    cout << "These are the Machines linked to " << target.getNafn() << endl << endl;

}

void NotendaUI::prentaVelarvensl()
{
    int velNR;
    int id;
    vector<velar> gogn = _vService.getVelar();
    velar target;

    cout << "Enter number of machine to see people that are linked to it (-1 to cancel): ";
    cin >> velNR;

    if (velNR == -1)
    {
        return;
    }
    while (velNR > _vService.getSize() || velNR <= 0)
    {
        if (velNR == -1)
        {
            break;
        }
        cerr << "Input not valid, try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> velNR;
    }

    velNR--;
    id = gogn[velNR].getID();
    target = _vService.getStaktVelar(id);


    prentaListaTolvuFolk(_service.getTolvufolkVensl(id));
    cout << "These are the people linked to: " << target.getVelaNafn() << endl << endl;
}

//------------------------------- Svæði fyrir UI greinar byrjar --------------------------------

void NotendaUI::adalvalmyndUI() //Upphaflega greinin, branchar út í aðrar UI greinar
{
    skrifaUt();
    bool satt = false;

    do
    {
        if (satt == true)
        {
            cerr << "Input not valid, try again: ";
        }

        string skipun;
        cin >> skipun;

        if (skipun == "machines" || skipun == "machine" || skipun == "m")
        {
            satt = false;
            adalvalmyndUITolvuVelar();
        }

        else if (skipun == "people" || skipun == "p")
        {
            satt = false;
            adalvalmyndUITolvuFolk();
        }

        else if (skipun == "quit" || skipun == "q")
        {
            satt = false;
            return;
        }

        else
        {
            skrifaUt();
            satt = true;
        }
    } while (aframhaldandiUIAdal());
}

void NotendaUI::adalvalmyndUITolvuVelar() //Greinin fyrir tölvur, branchar út í aðrar UI greinar
{
    skrifaUtTolvuVelar();

    bool satt = false;

    do
    {
        if (satt == true)
        {
            cerr << "Input not valid, try again: ";
        }

        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            satt = false;
            system("cls");
            prentaListaTolvuVelar(_vService.getVelar());

            cout << "Do you want to see people linked to these machines? (Y/N): ";
            if (sjaVelarVensl())
            {
                prentaVelarvensl();
            }
            aframhaldandiUIAlmennt();
        }

        else if (skipun == "link" || skipun == "li")
        {
            tengjaFolkiVel();
        }

        else if (skipun == "sort" || skipun == "so")
        {
            satt = false;
            skrifaUtTolvuVelar();
            flokkunarMoguleikarVelar();
        }

        else if (skipun == "add" || skipun == "a")
        {
            satt = false;
            system("cls");
            cout << "-----Adding computer machines-----" << endl;
            baetaVidVelar();
            prentaListaTolvuVelar(_vService.getVelar());
        }

        else if (skipun == "delete" || skipun == "d")
        {
            satt = false;
            eydaVel();
        }

        else if (skipun == "update" || skipun == "u")
        {
            satt = false;
            uppfaeraVelar();
        }

        else if (skipun == "search" || skipun == "se")
        {
            satt = false;
            leitaGreinVelar();
        }

        else if (skipun == "purge" || skipun == "p")
        {
            satt = false;
            skrifaUtTolvuVelar();
            tortimaListaVelar();
            aframhaldandiUIAlmennt();
        }

        else if (skipun == "return" || skipun == "r")
        {
            satt = false;
            return;
        }

        else
        {
            skrifaUtTolvuVelar();
            satt = true;
        }
    } while (aframhaldandiUITolvuVelar());
}

void NotendaUI::adalvalmyndUITolvuFolk() //Greinin fyrir tölvufolk, branchar út í aðrar UI greinar
{
    skrifaUtTolvuFolk();

    bool satt = false;

    do
    {
        if (satt == true)
        {
            satt = false;
            cerr << "Input not valid, try again: ";
        }

        string skipun;
        cin >> skipun;

        if (skipun == "list" || skipun == "l")
        {
            satt = false;
            system("cls");
            prentaListaTolvuFolk(_service.getTolvufolk());

            cout << "Want to see what machines these people are linked to? (Y/N): ";
            if (sjaVelarVensl())
            {
                prentaFolkVensl();
            }
            aframhaldandiUIAlmennt();
        }

        else if (skipun == "link" || skipun == "li")
        {
            tengjaFolkiVel();
        }

        else if (skipun == "sort" || skipun == "so")
        {

            satt = false;
            flokkunarMoguleikarTolvuFolk();
        }

        else if (skipun == "add" || skipun == "a")
        {
            satt = false;
            system("cls");
            cout << "-----Adding computer scientist-----" << endl;
            baetaVidPersonu();
            prentaListaTolvuFolk(_service.getTolvufolk());
        }

        else if (skipun == "delete" || skipun == "d")
        {
            satt = false;
            eydaPersonu();
        }

        else if (skipun == "update" || skipun == "u")
        {

            satt = false;
            uppfaeraPersonu();
        }

        else if (skipun == "search" || skipun == "se")
        {
            satt = false;
            skrifaUtTolvuFolk();
            leitaGreinTolvuFolk();
        }

        else if (skipun == "purge" || skipun == "p")
        {
            satt = false;
            skrifaUtTolvuFolk();
            tortimaListaTolvuFolk();
            aframhaldandiUIAlmennt();
        }

        else if (skipun == "return" || skipun == "r")
        {
            satt = false;
            return;
        }

        else
        {
            skrifaUtTolvuFolk();
            satt = true;
        }
    } while (aframhaldandiUITolvuFolk());
}

void NotendaUI::baetaVidPersonu() //UI grein til að bæta við persónu
{
    do
    {
        string nafn;
        char kKyn;
        int fAr;
        int dAr;

        cout << "Enter name (-1 to cancel add): ";
        cin.ignore();
        getline(cin, nafn);

        if (nafn == "-1")
        {
            break;
        }

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

        _service.baetaVidTolvufolk(nafn, kKyn, fAr, dAr);


    }while(skipunaAframhald());
}

void NotendaUI::eydaPersonu() //Delete UI grein
{
    do
    {
        vector<tolvufolk> gogn = _service.getTolvufolk();
        prentaListaTolvuFolk(gogn);
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
        int id = gogn[persNR].getID();
        cout << _service.getStaktTolvufolk(id).getNafn() << " has been removed.\n";
        _service.eydaStakiTolvufolk(id);

    }while(skipunaAframhald());
}

void NotendaUI::tengjaFolkiVel()
{
    int persNR;
    int machNR;
    tolvufolk folktarget;
    velar veltarget;
    vector<tolvufolk> gogn = _service.getTolvufolk();
    vector<velar> velargogn = _vService.getVelar();
    prentaListaTolvuFolk(gogn);

    cout << "Enter number of scientist to link to a machine (-1 to cancel): ";
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
    folktarget = _service.getStaktTolvufolk(gogn[persNR].getID());
    int folkID = gogn[persNR].getID();

    system("cls");
    prentaListaTolvuVelar(velargogn);
    cout << "Enter number of machine to link with " << folktarget.getNafn() << ": ";
    cin >> machNR;

    if (machNR == -1)
    {
        return;
    }
    while (machNR > _vService.getSize() || machNR <= 0)
    {
        if (machNR == -1)
        {
            break;
        }
        cerr << "Input not valid, try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> machNR;
    }

    machNR--;

    int velID = velargogn[machNR].getID();
    veltarget = _vService.getStaktVelar(velID);

    _service.venslaVidVel(folkID, velID);

    cout << folktarget.getNafn() << " is now linked with " << veltarget.getVelaNafn() << endl;

}

void NotendaUI::uppfaeraPersonu() //Update UI grein
{
    string nafn;
    char nyttKyn;
    int persNR, nyttD, nyttF;
    tolvufolk target;
    vector<tolvufolk> gogn = _service.getTolvufolk();
    prentaListaTolvuFolk(gogn);

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
    target = _service.getStaktTolvufolk(gogn[persNR].getID());

    system("cls");
    cout << "Updating information for: " << endl << endl;

    prentaPersonu(target, persNR);

    cout << "To hold section as is, enter 0." << endl << endl;

    cout << "Enter updated name: ";
    cin.ignore();
    getline(cin, nafn);

    if (nafn == "0")
        nafn = target.getNafn();

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


    _service.uppfaeraStakTolvufolk(target.getID(), nafn, nyttKyn, nyttF, nyttD);

    system("cls");
    cout << "Updated information:" << endl << endl;
    prentaPersonu((_service.getStaktTolvufolk(gogn[persNR].getID())), persNR);

}


void NotendaUI::leitaGreinTolvuFolk() //Search / Filter UI grein
{
    vector<tolvufolk> gogn;
    bool satt = false;

    leitarMoguleikarTolvuFolk();

    do
    {
        if (satt == true)
        {
            cerr << "Input not valid, try again: ";
        }

        string skipunin;
        cin >> skipunin;

        if (skipunin == "name" || skipunin == "n")
        {
            satt = false;
            leitarMoguleikarTolvuFolk();
            string nafn;
            cout << "---Searching by name---" << endl;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, nafn);
            cout << endl;
            gogn = _service.leitaStreng("nafn", nafn, 'a');
            if (gogn.size() == 0)
            {
                hausUITolvuFolk();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaListaTolvuFolk(gogn);
            }
        }

        else if (skipunin == "age" || skipunin == "a")
        {
            satt = false;
            int age;
            leitarMoguleikarTolvuFolk();
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
            gogn = _service.leitaHeiltolu("aldur", '=', age);
            if (gogn.size() == 0)
            {
                hausUITolvuFolk();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaListaTolvuFolk(gogn);
            }
        }

        else if (skipunin == "birth" || skipunin == "b")
        {
            satt = false;
            leitarMoguleikarTolvuFolk();
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
            gogn = _service.leitaHeiltolu("faedingarar", '=', birth);
            if (gogn.size() == 0)
            {
                hausUITolvuFolk();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaListaTolvuFolk(gogn);
            }
        }

        else if (skipunin == "death" || skipunin == "d")
        {
            satt = false;
            leitarMoguleikarTolvuFolk();
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
            gogn = _service.leitaHeiltolu("danarar", '=', death);
            if (gogn.size() == 0)
            {
                hausUITolvuFolk();
                cout << "|No person with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }
            else
            {
                prentaListaTolvuFolk(gogn);
            }
        }

        else if (skipunin == "quit" || skipunin == "q")
        {
            satt = false;
            return;
        }

        else
        {
            leitarMoguleikarTolvuFolk();
            satt = true;

        }

    }while(skipunaAframhald());
}

void NotendaUI::flokkunarMoguleikarTolvuFolk() //Sort UI grein
{
    string skipunin;
    vector<tolvufolk> radad;
    bool rettInntak = true;
    rodunarMoguleikarTolvuFolk();

    do
    {
        rettInntak = true;
        cin >> skipunin;


        if (skipunin == "name" || skipunin == "n")
        {
            radaUINafn();

            do
            {
                rettInntak = true;

                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _service.rada("nafn", "asc");
                    prentaListaTolvuFolk(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _service.rada("nafn", "desc");
                    prentaListaTolvuFolk(radad);
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
            radaUIAldur();

            do
            {
                rettInntak = true;

                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _service.rada("aldur", "asc");
                    prentaListaTolvuFolk(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _service.rada("aldur", "desc");
                    prentaListaTolvuFolk(radad);
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
            radaUIFaedingar();

            do
            {
                rettInntak = true;
                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _service.rada("faedingarar", "asc");
                    prentaListaTolvuFolk(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _service.rada("faedingarar", "desc");
                    prentaListaTolvuFolk(radad);
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
            radaUIDaudi();

            do
            {
                rettInntak = true;
                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _service.rada("danarar", "asc");
                    prentaListaTolvuFolk(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _service.rada("danarar", "desc");
                    prentaListaTolvuFolk(radad);
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

void NotendaUI::tortimaListaTolvuFolk() //Purge UI grein
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

        cout << "Enter machine name (-1 to cancel add): ";
        cin.ignore();
        getline(cin, vNafn);

        if (vNafn == "-1")
        {
            break;
        }

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

        while (byggdIn != 'Y' || byggdIn != 'y' || byggdIn != 'N' || byggdIn != 'n')
        {
            cout << "Was it built? (y/n)";
            cin >> byggdIn;

            if(byggdIn == 'y' || byggdIn == 'Y')
            {
                byggd = true;
                break;
            }
            else if(byggdIn == 'n' || byggdIn == 'N')
            {
                byggd = false;
                break;
            }
            else
            {
                cout << "Invalid input, try again!" << endl;
            }
        }

        _vService.baetaVidVelar(vNafn, bAr, byggd, tegund);

    }while(skipunaAframhald());
}

void NotendaUI::eydaVel() //Delete UI grein
{
    do
    {
        vector<velar> gogn = _vService.getVelar();
        prentaListaTolvuVelar(gogn);
        int velNR;
        cout << "Delete machine number (-1 to cancel deletion): ";
        cin >> velNR;
        while (velNR <= 0)
        {
            if (velNR == -1)
            {
                break;
            }
            cerr << "Input not valid, try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> velNR;
        }
        if (velNR == -1)
        {
            break;
        }
        velNR--;
        int id = gogn[velNR].getID();
        cout << _vService.getStaktVelar(id).getVelaNafn() << " has been removed.\n";
        _vService.eydaStakiVel(id);

    }while(skipunaAframhald());
}

void NotendaUI::uppfaeraVelar() //Update UI grein
{
    string vNafn, nyttTegund;
    char byggdIn;
    int velNR, nyttbAr;
    velar target;
    bool byggd;
    vector<velar> gogn = _vService.getVelar();
    prentaListaTolvuVelar(gogn);

    cout << "Update machine number (-1 to cancel update): ";
    cin >> velNR;
    if (velNR == -1)
    {
        return;
    }
    while (velNR > _vService.getSize() || velNR <= 0)
    {
        if (velNR == -1)
        {
            break;
        }
        cerr << "Input not valid, try again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> velNR;
    }

    velNR--;
    int id = gogn[velNR].getID();
    target = _vService.getStaktVelar(id);

    system("cls");
    cout << "Updating information for: " << endl << endl;

    prentaVel(target, velNR);

    cout << "To hold section as is, enter 0." << endl << endl;

    cout << "Enter updated machine name: ";
    cin >> vNafn;

     if (vNafn == "0")
    {
        vNafn = target.getVelaNafn();
    }

        cout << "Enter updated built year: ";
        cin >> nyttbAr;

        while (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "Input not valid, try again: ";
            cin >> nyttbAr;
        }

        if (nyttbAr == 0)
        {
            nyttbAr = target.getByggingarAr();
        }

        cout << "Enter updated type: ";
        cin >> nyttTegund;


        do
        {
            cout << "Was it built? (y/n)";
            cin >> byggdIn;

            if (byggdIn == '0')
            {
                byggdIn = target.getByggd();
                break;
            }

            else if(byggdIn == 'y' || byggdIn == 'Y')
            {
                byggd = true;
                break;
            }
            else if(byggdIn == 'n' || byggdIn == 'N')
            {
                byggd = false;
                break;
            }
            else
            {
                cout << "Invalid input, try again!" << endl;
            }
        }while (byggdIn != 'Y' || byggdIn != 'y' || byggdIn != 'N' || byggdIn != 'n' || byggdIn != '0');

    _vService.uppfaeraVelar((target.getID()), vNafn, nyttbAr, byggd, nyttTegund);

    system("cls");
    cout << "Updated information:" << endl << endl;
    prentaVel((_vService.getStaktVelar(id)), velNR);
}

void NotendaUI::leitaGreinVelar() //Search / Filter UI grein
{
    vector<velar> gogn;
    do
    {
        leitarMoguleikarVelar();
        string skipunin;
        cin >> skipunin;

        if (skipunin == "name" || skipunin == "n")
        {
            string nafn;

            leitarMoguleikarVelar();

            cout << "---Searching by name---" << endl;
            cout << "Enter name: ";
            cin >> nafn;
            cout << endl;
            gogn = _vService.leitaStreng("Nafn", nafn, 'a');
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No machine with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaListaTolvuVelar(gogn);
            }
        }

        else if (skipunin == "create" || skipunin == "c")
        {
            int artal;
            leitarMoguleikarVelar();
            cout << "Year to search: ";
            cin >> artal;
            while (!cin)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Input not valid, try again: ";
                cin >> artal;
            }
            cout << endl;
            gogn = _vService.leitaHeiltolu("Byggingarar", '=', artal);
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No machine with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }else
            {
                prentaListaTolvuVelar(gogn);
            }
        }

        else if (skipunin == "type" || skipunin == "t")
        {
            leitarMoguleikarVelar();
            string tegund;
            cout << "Type to search: ";
            cin >> tegund;

            cout << endl;
            gogn = _vService.leitaStreng("Tegund", tegund, 'a');
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No machine with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }
            else
            {
                prentaListaTolvuVelar(gogn);
            }
        }

        else if (skipunin == "made" || skipunin == "m")
        {
            leitarMoguleikarVelar();
            int byggd;
            char byggdIn;

            do
            {
                cout << "Was it built? (y/n): ";
                cin >> byggdIn;

                if(byggdIn == 'y' || byggdIn == 'Y')
                {
                    byggd = 1;
                    break;
                }
                else if(byggdIn == 'n' || byggdIn == 'N')
                {
                    byggd = 0;
                    break;
                }
                else
                {
                    cout << "Invalid input, try again!" << endl;
                }
            }while (byggdIn != 'Y' || byggdIn != 'y' || byggdIn != 'N' || byggdIn != 'n');

            cout << endl;
            gogn = _vService.leitaHeiltolu("Byggd", '=', byggd);
            if (gogn.size() == 0)
            {
                hausUI();
                cout << "|No machine with those parameters exists in the database.                                                 |" << endl;
                cout << "----------------------------------------------------------------------------------------------------------" << endl;
            }
            else
            {
                prentaListaTolvuVelar(gogn);
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

void NotendaUI::flokkunarMoguleikarVelar() //Sort UI grein
{
    string skipunin;
    vector<velar> radad;
    bool rettInntak = true;
    rodunarMoguleikarVelar();

    do
    {
        rettInntak = true;
        cin >> skipunin;

        if (skipunin == "name" || skipunin == "n")
        {
            radaUINafn();

            do
            {
                rettInntak = true;

                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _vService.rada("Nafn", "asc");
                    prentaListaTolvuVelar(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _vService.rada("Nafn", "desc");
                    prentaListaTolvuVelar(radad);
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

        else if(skipunin == "create" || skipunin == "c")
        {
            radaUIbAr();

            do
            {
                rettInntak = true;

                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _vService.rada("byggingarar", "asc");
                    prentaListaTolvuVelar(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _vService.rada("byggingarar", "desc");
                    prentaListaTolvuVelar(radad);
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

        else if(skipunin == "type" || skipunin == "t")
        {
            radaUITypa();

            do
            {
                rettInntak = true;
                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _vService.rada("tegund", "asc");
                    prentaListaTolvuVelar(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _vService.rada("tegund", "desc");
                    prentaListaTolvuVelar(radad);
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

        else if(skipunin == "made" || skipunin == "m")
        {
            radaUIByggd();

            do
            {
                rettInntak = true;
                cin >> skipunin;

                if(skipunin == "ascending" || skipunin == "a")
                {
                    radad = _vService.rada("byggd", "asc");
                    prentaListaTolvuVelar(radad);
                }

                else if(skipunin == "descending" || skipunin == "d")
                {
                    radad = _vService.rada("byggd", "desc");
                    prentaListaTolvuVelar(radad);
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

void NotendaUI::tortimaListaVelar() //Purge UI grein
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

            _vService.tortimaTolvuVelar();

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

//------------------------------- Svæði fyrir UI greinar endar ---------------------------------

//------------------------------- Svæði fyrir bool flögg byrjar --------------------------------
bool NotendaUI::aframhaldandiUIAdal()
{
    skrifaUt();
    return true;
}

bool NotendaUI::aframhaldandiUITolvuVelar()
{
    skrifaUtTolvuVelar();
    return true;
}

bool NotendaUI::aframhaldandiUITolvuFolk()
{
    skrifaUtTolvuFolk();
    return true;
}

bool NotendaUI::aframhaldandiUIAlmennt()
{
    string svar = "o";

    cout << "Input anything to continue: ";
    cin >> svar;
    return true;
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


bool NotendaUI::sjaVelarVensl()
{
    string svar;
    do
    {

        cin >> svar;

        if (svar == "Y" || svar == "y")
        {
            return true;
        }

        else if(svar == "N" || svar == "n")
        {
            return false;
        }
        else
        {
            cout << "Invalid input, try again: ";
        }

    }while (svar != "Y" || svar != "y" || svar != "N" || svar != "n");

    return false;
}

//------------------------------- Svæði fyrir bool flögg endar ---------------------------------

//------------------------------- Svæði fyrir cout blokkir byrjar ------------------------------



void NotendaUI::skrifaUt()
{
    system("cls");

    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following commands - Main Menu        ||*" << endl;
    cout << "*==================================================================*" << endl;
    cout << "*||machines  - Access options to the computer machine database.  ||*" << endl;
    cout << "*||people    - Access options to the people database.            ||*" << endl;
    cout << "*||quit      - Exits/quits the program.                          ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::skrifaUtTolvuVelar()
{
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following commands - Machine Database ||*" << endl;
    skrifaUtVal();
}

void NotendaUI::skrifaUtTolvuFolk()
{
    system("cls");
    cout << "*==================================================================*" << endl;
    cout << "*||Please enter one of the following commands - People Database  ||*" << endl;
    skrifaUtVal();
}

void NotendaUI::skrifaUtVal()
{
    cout << "*==================================================================*" << endl;
    cout << "*||list   - Shows a list of all known entries in the database.   ||*" << endl;
    cout << "*||link   - Link scientist and machines together.                ||*" << endl;
    cout << "*||add    - Add a new entry into the database.                   ||*" << endl;
    cout << "*||delete - Removes an entry from the database.                  ||*" << endl;
    cout << "*||update - Updates an entry from the database.                  ||*" << endl;
    cout << "*||search - Search for an entry from the database.               ||*" << endl;
    cout << "*||sort   - Sort the entries in the database.                    ||*" << endl;
    cout << "*||purge  - Removes every entry from the database.               ||*" << endl;
    cout << "*||return - Return to the main menu.                             ||*" << endl;
    cout << "*==================================================================*" << endl;
}

void NotendaUI::skipunaGluggi()
{
    system("cls");

    cout << "*==========================================================================================*" << endl;
    cout << "*||Please enter one of the following command                                             ||*" << endl;
    cout << "*==========================================================================================*" << endl;

}

void NotendaUI::haettaLeit()
{
    cout << "*||quit   - Quit searching.                                                              ||*" << endl;
    cout << "*==========================================================================================*" << endl;
}

void NotendaUI::haettaSort()
{
    cout << "*||quit   - Quit sorting.                                                                ||*" << endl;
    cout << "*==========================================================================================*" << endl;
}

void NotendaUI::leitarMoguleikarTolvuFolk()
{
    skipunaGluggi();
    cout << "*||name   - Search by name, please write 'name'.                                         ||*" << endl;
    cout << "*||age    - Search by age, please write 'age'.                                           ||*" << endl;
    cout << "*||birth  - Search by year of birth, please write 'birth'.                               ||*" << endl;
    cout << "*||death  - Search by year of death, please write 'death'.                               ||*" << endl;
    haettaLeit();
}

void NotendaUI::leitarMoguleikarVelar()
{
    skipunaGluggi();
    cout << "*||name   - Search by name, please write 'name'.                                         ||*" << endl;
    cout << "*||create - Search by date of creation, please write 'create'.                           ||*" << endl;
    cout << "*||type   - Search by type, please write 'type'.                                         ||*" << endl;
    cout << "*||made   - To search based on if machine was created or not, please write 'made'.       ||*" << endl;
    haettaLeit();
}

void NotendaUI::rodunarMoguleikarTolvuFolk()
{
    skipunaGluggi();
    cout << "*||name   - Sort by name, please write 'name'                                            ||*" << endl;
    cout << "*||age    - Sort by age, please write 'age'                                              ||*" << endl;
    cout << "*||birth  - Sort by year of birth, please write 'birth'                                  ||*" << endl;
    cout << "*||death  - Sort by year of death, please write 'death'                                  ||*" << endl;
    haettaSort();
}

void NotendaUI::rodunarMoguleikarVelar()
{
    skipunaGluggi();
    cout << "*||name   - Sort by name, please write 'name'                                            ||*" << endl;
    cout << "*||create - Sort by date of creation, please write 'create'.                             ||*" << endl;
    cout << "*||type   - sort by type, please write 'type'.                                           ||*" << endl;
    cout << "*||made   - sort by if machine was built or not, please write 'made'.                    ||*" << endl;
    haettaSort();
}

void NotendaUI::radaUINafn()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort name by ascending order, please write 'ascending'                   ||*" << endl;
    cout << "*||descending - Sort name by descending order, please write 'descending'                 ||*" << endl;
    haettaSort();
}


void NotendaUI::radaUIAldur()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort age by ascending order, please write 'ascending'                    ||*" << endl;
    cout << "*||descending - Sort age by descending order, please write 'descending'                  ||*" << endl;
    haettaSort();
}

void NotendaUI::radaUIFaedingar()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort birth by ascending order, please write 'ascending'                  ||*" << endl;
    cout << "*||descending - Sort birth by descending order, please write 'descending'                ||*" << endl;
    haettaSort();
}

void NotendaUI::radaUIDaudi()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort death by ascending order, please write 'ascending'                  ||*" << endl;
    cout << "*||descending - Sort death by descending order, please write 'descending'                ||*" << endl;
    haettaSort();
}

void NotendaUI::radaUIbAr()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort year of creation by ascending order, please write 'ascending'       ||*" << endl;
    cout << "*||descending - Sort year of creation by descending order, please write 'descending'     ||*" << endl;
    haettaSort();
}

void NotendaUI::radaUITypa()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort type by ascending order, please write 'ascending'                   ||*" << endl;
    cout << "*||descending - Sort type by descending order, please write 'descending'                 ||*" << endl;
    haettaSort();
}

void NotendaUI::radaUIByggd()
{
    skipunaGluggi();
    cout << "*||ascending  - Sort if machine was built by ascending order, please write 'ascending'   ||*" << endl;
    cout << "*||descending - Sort if machine was built by descending order, please write 'descending' ||*" << endl;
    haettaSort();
}

void NotendaUI::hausUI()
{
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Machine ID \t |Name of Machine \t |Year of Creation |Type of Machine \t  |Was it built? \t\t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}

void NotendaUI::hausUITolvuFolk()
{
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
    cout << "|Scientist ID \t |Name \t\t\t\t |Gender \t |Year of Birth  |Year of death  |Age \t |" << endl;
    cout << "----------------------------------------------------------------------------------------------------------" << endl;
}
//------------------------------- Svæðu fyrir cout blokkir endar -------------------------------
