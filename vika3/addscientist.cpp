#include "addscientist.h"
#include "ui_addscientist.h"

AddScientist::AddScientist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddScientist)
{
    ui->setupUi(this);
}

bool karl;

AddScientist::~AddScientist()
{
    delete ui;
}

void AddScientist::on_button_add_clicked()
{
    string nafn = ui->input_name->text().toStdString();
    int fAr = ui->input_birth->text().toInt();
    int dAr = ui->input_death->text().toInt();
    char kKyn;

    if (karl)
    {
        kKyn = 'm';
    }
    else
    {
        kKyn = 'f';
    }

    _service.baetaVidTolvufolk(nafn, kKyn, fAr, dAr);
    this->done(0);
}

void AddScientist::on_button_cancel_clicked()
{
    this->done(0);
}

void AddScientist::on_radio_male_clicked()
{
    karl = true;
}

void AddScientist::on_radio_female_clicked()
{
    karl = false;
}
