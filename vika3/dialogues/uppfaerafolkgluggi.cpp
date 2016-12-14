#include "uppfaerafolkgluggi.h"
#include "ui_uppfaerafolkgluggi.h"

uppfaeraFolkGluggi::uppfaeraFolkGluggi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uppfaeraFolkGluggi)
{
    ui->setupUi(this);
}

uppfaeraFolkGluggi::~uppfaeraFolkGluggi()
{
    delete ui;
}

void uppfaeraFolkGluggi::setFolk(tolvufolk folk)
{
    _target = folk;
    getFolk();
}

void uppfaeraFolkGluggi::getFolk()
{
    QString name = QString::fromStdString(_target.getNafn());
    QString faed = QString::fromStdString(std::to_string(_target.getFaedingarar()));
    QString danar = QString::fromStdString(std::to_string(_target.getDanarar()));
    if (_target.getKyn() == 'm')
    {
        ui->radio_male->setChecked(true);
    }
    else
    {
        ui->radio_female->setChecked(true);
    }

    ui->input_name->setText(name);
    ui->input_birth->setText(faed);
    ui->input_death->setText(danar);
}

void uppfaeraFolkGluggi::on_UppfaeraFolkTakki_clicked()
{
    //QMessageBox box;
    string nafn = ui->input_name->text().toStdString();
    int id = _target.getID();
    int fAr = (ui->input_birth->text().length() > 0 && ui->input_birth->text().toInt() > 0 ? ui->input_birth->text().toInt() : -1);
    int dAr = (ui->input_death->text().length() > 0 && ui->input_birth->text().toInt() > 0 ? ui->input_death->text().toInt() : -1);
    char kyn = (ui->radio_male->isChecked() ? 'm' : 'f');

    _fService.uppfaeraStakTolvuFolk(id, nafn, kyn, fAr, dAr);
    /*
    folkValidation f = _fService.baetaVidTolvufolk(nafn, kyn, fAr, dAr);
    switch(f)
    {
        case fSuccess:
            //What to do when succeess
            box.setText("Success!");
            getFolk();
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
            //What to do if age is too high
            box.setText("Age is too high!!");
            break;
        case birthAfterCurrentYear:
            //What to do if birth is after current year
            box.setText("Birth after current year!");
            break;
    }
    box.exec();*/

    this->done(0); //Should dialogue exit after adding?
}

void uppfaeraFolkGluggi::on_UppfHaettaTakki_clicked()
{
    this->done(0);
}
