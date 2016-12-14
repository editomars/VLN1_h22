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
    string vNafn = ui->input_vName->text().toStdString();
    int bAr = (ui->input_builtYear->text().length() > 0 && ui->input_builtYear->text().toInt() > 0 ? ui->input_builtYear->text().toInt() : -1);
    bool byggd;
    string tegund = ui->input_type->text().toStdString();
    int id = _target.getID();

    if (ui->vRadio_built->isChecked())
    {
        byggd = 1;
    }
    else
    {
        byggd = 0;
    }

    _vService.uppfaeraVelar(id, vNafn, bAr, byggd, tegund);

    this->done(0);

}

void uppfaeravelgluggi::on_UppfHaettaTakki_clicked()
{
    this->done(0);
}
