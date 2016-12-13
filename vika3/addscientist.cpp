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
