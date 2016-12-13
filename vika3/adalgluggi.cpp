#include "adalgluggi.h"
#include "ui_adalgluggi.h"

#include <QDebug>
adalgluggi::adalgluggi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adalgluggi)
{
    ui->setupUi(this);
}

adalgluggi::~adalgluggi()
{
    delete ui;
}

void adalgluggi::on_velar_clicked()
{
    qDebug () << "Vélar hnappur clicked";
}

void adalgluggi::on_folk_clicked()
{
    qDebug () << "Folk hnappur clicked";
}

void adalgluggi::on_haetta_clicked()
{

}
