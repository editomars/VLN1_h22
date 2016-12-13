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

void uppfaeraFolkGluggi::on_UppfHaettaTakki_clicked()
{

}
