#include "tolvufolkservice.h"
//Smiður
tolvufolkService::tolvufolkService()
{

}

//----------------------- Svæði fyir sorting struct byrjar ---------------------
//rada aldri haekkandi
struct aldurHaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getAldur() < j.getAldur());
    }
};

struct aldurLaekkandi
{
    bool operator () (tolvufolk i, tolvufolk j)
    {
        return (i.getAldur() > j.getAldur());
    }
};
//----------------------- Svæði fyir sorting struct endar ---------------------

//----------------------- Svæði fyrir public föll byrjar ----------------------

//Get föll

tolvufolk tolvufolkService::getStaktTolvufolk(int id) const
{
    return _dataaccess.lesaFolk(id)[0];
}

vector<tolvufolk> tolvufolkService::getTolvufolk() const
{
    return _dataaccess.lesaFolk(-1);
}

vector<tolvufolk> tolvufolkService::getTolvufolkVensl(int vel_id) const
{
    return _dataaccess.lesaFolkVenslad(vel_id);
}

int tolvufolkService::getSize() const
{
    return _dataaccess.saekjaSize("folk");
}

//Föll sem breyta gagnagrunn

enum folkValidation tolvufolkService::baetaVidTolvufolk(string nafn, char kyn, int fAr, int dAr)
{

    folkValidation valid = validate(nafn, kyn, fAr, dAr);
    if (valid == fSuccess)
        _dataaccess.baetaVidFolk(nafn, kyn, fAr, dAr);
    return valid;
}

void tolvufolkService::tortimaTolvufolk()
{
    _dataaccess.tortimaFolki();
}

void tolvufolkService::eydaStakiTolvufolk(int id)
{
    _dataaccess.eydaFolk(id);
}

enum folkValidation tolvufolkService::uppfaeraStakTolvuFolk(int id, string nafn, char kyn, int fAr, int dAr)
{
    folkValidation valid = validate(nafn, kyn, fAr, dAr);
    if (valid == fSuccess)
        _dataaccess.uppfaeraFolk(id,nafn,kyn,fAr,dAr);
    return valid;
}

void tolvufolkService::venslaVidVel(int folk_id, int vel_id)
{
    _dataaccess.buaTilVensl(folk_id, vel_id);
}

void tolvufolkService::eydaStakiVensl(int folk_id, int vel_id)
{
    _dataaccess.eydaStakiVensl(folk_id, vel_id);
}

//Föll sem skila umbreyttum gögnum
vector<tolvufolk> tolvufolkService::leitaStreng(string flokkur, string leitarord, char pos)
{
    return _dataaccess.leitaFolk(flokkur, leitarord, pos);
}

vector<tolvufolk> tolvufolkService::leitaHeiltolu(string flokkur, char type, int leitarord)
{
    if (flokkur == "aldur")
    {
        return leitaAldur(type, leitarord);
    }
    return _dataaccess.leitaFolk(flokkur, type, leitarord);
}

vector<tolvufolk> tolvufolkService::leitaHeiltolubil(string flokkur, int laegraBil, int haerraBil)
{
    if (flokkur == "aldur")
    {
        return leitaAldur(laegraBil, haerraBil);
    }
    return _dataaccess.leitaFolk(flokkur, laegraBil, haerraBil);
}

vector<tolvufolk> tolvufolkService::rada(string flokkur, string rod)
{
    if (flokkur == "aldur"){
        if (rod == "asc"){
            return radaAldriHaekkandi(_dataaccess.lesaFolk(-1));
        }else if (rod == "desc"){
            return radaAldriLaekkandi(_dataaccess.lesaFolk(-1));
        }
    }
    return _dataaccess.lesaFolkSorted(flokkur,rod);
}
//--------------------------- Svæði fyrir public föll endar ---------------------------------------------

//------------------------ Svæði fyrir private föll byrjar ----------------------------------------------
//Sort föll --private
vector<tolvufolk> tolvufolkService::radaAldriHaekkandi(vector<tolvufolk> gogn)
{
    aldurHaekkandi temp;
    vector<tolvufolk> sorted = gogn;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

vector<tolvufolk> tolvufolkService::radaAldriLaekkandi(vector<tolvufolk> gogn)
{
    aldurLaekkandi temp;
    vector<tolvufolk> sorted = gogn;
    sort(sorted.begin(), sorted.end(), temp);
    return sorted;
}

//Leita föll
vector<tolvufolk> tolvufolkService::leitaAldur(char type, int leitarord)
{
    vector<tolvufolk> gogn = _dataaccess.lesaFolk(-1);
    vector<tolvufolk> filtered;

    for (size_t i = 0; i < gogn.size(); ++i)
    {
        if (type == '<'){
            if (gogn[i].getAldur() < leitarord){
                filtered.push_back(gogn[i]);
            }
        }else if (type == '>'){
            if (gogn[i].getAldur() > leitarord){
                filtered.push_back(gogn[i]);
            }
        }else if (type == '='){
            if (gogn[i].getAldur() == leitarord){
                filtered.push_back(gogn[i]);
            }
        }
    }
    return filtered;
}

vector<tolvufolk> tolvufolkService::leitaAldur(int laegraBil, int haerraBil)
{
    vector<tolvufolk> gogn = _dataaccess.lesaFolk(-1);
    vector<tolvufolk> filtered;

    for (size_t i = 0; i < gogn.size(); ++i){
        if (gogn[i].getAldur() >= laegraBil && gogn[i].getAldur() <= haerraBil){
            filtered.push_back(gogn[i]);
        }
    }

    return filtered;
}

enum folkValidation tolvufolkService::validate(string nafn, char kyn, int fAr, int dAr)
{
    int aldur = (dAr == -1 ? constants::CURRENT_YEAR - fAr : dAr - fAr);
    if (nafn == "")
        return nameEmpty;
    if (kyn != 'm' && kyn != 'f')
        return genderNotValid;
    if (dAr != -1 && dAr < fAr)
        return deathBeforeBirth;
    if (dAr != -1 && dAr > constants::CURRENT_YEAR)
        return deathAfterCurrentYear;
    if (fAr == -1)
        return noBirthYear;
    if (aldur > constants::MAXIMUM_AGE)
        return ageTooHigh;
    if (fAr > constants::CURRENT_YEAR)
        return birthAfterCurrentYear;
    return fSuccess;
}
