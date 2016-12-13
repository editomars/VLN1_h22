#include "uppfaerafolkgluggi.h"
#include "ui_uppfaerafolkgluggi.h"

uppfaeraFolkGluggi::uppfaeraFolkGluggi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::uppfaeraFolkGluggi)
{
    ui->setupUi(this);
}

void uppfaeraFolkGluggi::setFolk(tolvufolk folk)
{
    _target = folk;
}

uppfaeraFolkGluggi::~uppfaeraFolkGluggi()
{
    delete ui;
}

void uppfaeraFolkGluggi::on_UppfHaettaTakki_clicked()
{

}
