#include "adalgluggi.h"
#include "ui_adalgluggi.h"

#include <QDebug>
adalgluggi::adalgluggi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adalgluggi)
{
    ui->setupUi(this);
    ui->velar;
    ui->folk;
}

adalgluggi::~adalgluggi()
{
    delete ui;
}

void adalgluggi::on_pushButton_clicked()
{
    vector<tolvufolk> folk = _fService.getTolvufolk();
    for (size_t i = 0; i < folk.size(); ++i)
    {
        qDebug() << QString(folk[i].getNafn().c_str());
    }
}

void adalgluggi::on_velar_clicked()
{
    qDebug () << ui->velar;
}

void adalgluggi::on_folk_clicked()
{
    qDebug () << ui->folk;
}

/*void adalgluggi::on_haetta_clicked()
{

}*/
