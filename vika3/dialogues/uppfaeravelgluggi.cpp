#include "uppfaeravelgluggi.h"
#include "ui_uppfaeravelgluggi.h"

uppfaeravelgluggi::uppfaeravelgluggi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uppfaeravelgluggi)
{
    ui->setupUi(this);
}

uppfaeravelgluggi::~uppfaeravelgluggi()
{
    delete ui;
}

void uppfaeravelgluggi::setVel(velar vel)
{
    _target = vel;
    getVel();
}
void uppfaeravelgluggi::getVel()
{
    QString name = QString::fromStdString(_target.getVelaNafn());
    QString year = QString::fromStdString(std::to_string(_target.getByggingarAr()));
    QString type = QString::fromStdString(_target.getTegund());
    if (_target.getByggd() == 1)
    {
        ui->vRadio_built->setChecked(true);
    }
    else
    {
        ui->vRadio_notBuilt->setChecked(true);
    }

    ui->input_vName->setText(name);
    ui->input_builtYear->setText(year);
    ui->input_type->setText(type);
}

void uppfaeravelgluggi::on_UppfaeraVelTakki_clicked()
{
    QMessageBox box;
    string vNafn = ui->input_vName->text().toStdString();
    int id = _target.getID();
    int bAr = (ui->input_builtYear->text().length() > 0 && ui->input_builtYear->text().toInt() > 0 ? ui->input_builtYear->text().toInt() : -1);
    bool byggd;
    string tegund = ui->input_type->text().toStdString();

    if (ui->vRadio_built->isChecked())
    {
        byggd = 1;
    }
    else
    {
        byggd = 0;
    }


    velValidation v = _vService.uppfaeraVelar(id, vNafn, bAr, byggd, tegund);
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

void uppfaeravelgluggi::on_UppfHaettaTakki_clicked()
{
    this->done(0);
}
