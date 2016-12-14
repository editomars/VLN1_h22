#include "addmachine.h"
#include "ui_addmachine.h"

addmachine::addmachine(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addmachine)
{
    ui->setupUi(this);
}

addmachine::~addmachine()
{
    delete ui;
}

void addmachine::on_vButton_add_clicked()
{
    QMessageBox box;
    string vNafn = ui->input_vName->text().toStdString();
    int bAr = (ui->input_builtYear->text().length() > 0 && ui->input_builtYear->text().toInt() > 0 ? ui->input_builtYear->text().toInt() : -1);
    bool byggd = ui->vRadio_built->isChecked();
    string tegund = ui->input_type->text().toStdString();

    velValidation v = _vService.baetaVidVelar(vNafn, bAr, byggd, tegund);
    switch (v)
    {
        case vSuccess:
            //What to do when success
            box.setText("Success!");
            break;
        case builtFieldMissing:
            //What to do if built field is missing
            box.setText("Build field missing");
            break;
        case builtYearAfterCurrentYear:
            //What to do if built year is after current year
            box.setText("Built after current year");
            break;
        case builtYearMissing:
            //What to do if built year is missing
            box.setText("No built year");
            break;
    }

    box.exec();

    //this->done(0);
}

void addmachine::on_vButton_cancel_clicked()
{
    this->done(0);
}
