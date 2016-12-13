#include "adalgluggi.h"
#include "ui_adalgluggi.h"

#include <QDebug>
adalgluggi::adalgluggi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adalgluggi)
{
    ui->setupUi(this);
    //init stillingar
    _folkCurrent = _fService.getTolvufolk();
    _velarCurrent = _vService.getVelar();
    synaFolk(_folkCurrent);
}

adalgluggi::~adalgluggi()
{
    delete ui;
}

void adalgluggi::synaFolk(vector<tolvufolk> folk)
{
    ui->folkTable->clearContents();

    ui->folkTable->setRowCount(folk.size());

    for (size_t row = 0; row < folk.size(); ++row)
    {
        QString stak = QString::fromStdString(folk[row].getNafn());
        ui->folkTable->setItem(row, 0, new QTableWidgetItem(stak));
    }

    _folkCurrent = folk;
}
