#include "addmachine.h"
#include "ui_addmachine.h"

addmachine::addmachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmachine)
{
    ui->setupUi(this);
}

bool byggd;

addmachine::~addmachine()
{
    delete ui;
}

void addmachine::on_vButton_add_clicked()
{
    string vNafn = ui->input_vName->text().toStdString();
    int bAr = ui->input_builtYear->text().toInt();
    //bool byggd = ui->input_built->text().toStdString();
    string tegund = ui->input_type->text().toStdString();

    if (true)
    {
        byggd = 'yes';
    }
    else
    {
        byggd = 'no';
    }

    _vService.baetaVidVelar(vNafn, bAr, byggd, tegund);
    this->done(0);
}

void addmachine::on_vButton_cancel_clicked()
{
    this->done(0);
}

void addmachine::on_vRadio_built_clicked()
{
    byggd = true;
}

void addmachine::on_vRadio_notBuilt_clicked()
{
    byggd = false;
}
