#include "addscientist.h"
#include "ui_addscientist.h"

AddScientist::AddScientist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddScientist)
{
    ui->setupUi(this);
}

AddScientist::~AddScientist()
{
    delete ui;
}

void AddScientist::on_button_add_clicked()
{
    QMessageBox box;
    string nafn = ui->input_name->text().toStdString();
    int fAr = (ui->input_birth->text().length() > 0 ? ui->input_birth->text().toInt() : -1);
    int dAr = (ui->input_death->text().length() > 0 ? ui->input_death->text().toInt() : -1);
    char kyn = (ui->radio_male->isChecked() ? 'm' : 'f');

    folkValidation f = _service.baetaVidTolvufolk(nafn, kyn, fAr, dAr);
    switch(f)
    {
        case fSuccess:
            //What to do when succeess
            box.setText("Success!");
            break;
        case nameEmpty:
            //What to do when name is empty
            box.setText("No name!");
            break;
        case noBirthYear:
            //What to do when birth year is empty
            box.setText("No birth year!");
            break;
        case deathBeforeBirth:
            //What to do when death is before birth
            box.setText("death before birth!");
            break;
        case deathAfterCurrentYear:
            //What to do if death is after current year
            box.setText("Died after current year!");
            break;
        case genderNotValid:
            //What to do if gender is not m or f
            box.setText("Gender not valid!");
            break;
        case ageTooHigh:
            //What to do if gender is too high
            box.setText("Age is too high!!");
            break;
        case birthAfterCurrentYear:
            //What to do if birth is after current year
            box.setText("Birth after current year!");
            break;
    }
    box.exec();

    //this->done(0); //Should dialogue exit after adding?
}

void AddScientist::on_button_cancel_clicked()
{
    this->done(0);
}
