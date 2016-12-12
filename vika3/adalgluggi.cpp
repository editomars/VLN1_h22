#include "adalgluggi.h"
#include "ui_adalgluggi.h"

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

void adalgluggi::on_pushButton_clicked()
{
    vector<tolvufolk> folk = _fService.getTolvufolk();
    for (size_t i = 0; i < folk.size(); ++i)
    {
        qDebug() << QString(folk[i].getNafn().c_str());
    }
}
