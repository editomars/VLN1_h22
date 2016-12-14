#include "uppfaeravelgluggi.h"
#include "ui_uppfaeravelgluggi.h"

uppfaeravelgluggi::uppfaeravelgluggi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uppfaeravelgluggi)
{
    ui->setupUi(this);
}

void uppfaeravelgluggi::setVel(velar vel)
{
    _target = vel;
}

uppfaeravelgluggi::~uppfaeravelgluggi()
{
    delete ui;
}

void uppfaeravelgluggi::on_UppfHaettaTakki_clicked()
{

}
