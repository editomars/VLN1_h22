#include "adalgluggi.h"
#include "ui_adalgluggi.h"
#include "uppfaerafolkgluggi.h"

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
    synaVelar(_velarCurrent);
}

adalgluggi::~adalgluggi()
{
    delete ui;
}

void adalgluggi::synaFolk(const vector<tolvufolk>& folk)
{
    ui->folkTable->clearContents();
    ui->folkTable->setSortingEnabled(false);

    ui->folkTable->setRowCount(folk.size());

    for (size_t row = 0; row < folk.size(); ++row)
    {
        QString nafn = QString::fromStdString(folk[row].getNafn());
        QString gender = QString((folk[row].getKyn() == 'm' ? "Male" : "Female"));
        QString fAr = QString::number(folk[row].getFaedingarar());
        QString dAr;
        if (folk[row].getDanarar() == -1){
            dAr = QString("Still alive");
        }else{
            dAr = QString::number(folk[row].getDanarar());
        }
        QString aldur = QString::number(folk[row].getAldur());
        ui->folkTable->setItem(row, 0, new QTableWidgetItem(nafn));
        ui->folkTable->setItem(row, 1, new QTableWidgetItem(gender));
        ui->folkTable->setItem(row, 2, new QTableWidgetItem(aldur));
        ui->folkTable->setItem(row, 3, new QTableWidgetItem(fAr));
        ui->folkTable->setItem(row, 4, new QTableWidgetItem(dAr));
    }

    _folkCurrent = folk;
    ui->folkTable->setSortingEnabled(true);
}

void adalgluggi::synaVelar(const vector<velar>& velar)
{
    ui->velTable->clearContents();
    ui->velTable->setSortingEnabled(false);

    ui->velTable->setRowCount(velar.size());

    for (size_t row = 0; row < velar.size(); ++row)
    {
        QString nafn = QString::fromStdString(velar[row].getVelaNafn());
        QString bAr = QString::number(velar[row].getByggingarAr());
        QString byggd = QString(velar[row].getByggd() ? "Yes" : "No");
        QString tegund = QString::fromStdString(velar[row].getTegund());
        ui->velTable->setItem(row, 0, new QTableWidgetItem(nafn));
        ui->velTable->setItem(row, 1, new QTableWidgetItem(bAr));
        ui->velTable->setItem(row, 2, new QTableWidgetItem(byggd));
        ui->velTable->setItem(row, 3, new QTableWidgetItem(tegund));
    }

    _velarCurrent = velar;
    ui->velTable->setSortingEnabled(true);
}

void adalgluggi::on_tabsList_currentChanged(int index)
{
    switch (index)
    {
        case 0:
            synaFolk(_folkCurrent);
            break;
        case 1:
            synaVelar(_velarCurrent);
            break;
    }
}

void adalgluggi::on_folkFilterText_textChanged(const QString &arg1)
{
    string flokkur = ui->folkFilterBox->currentText().toStdString();



    if (arg1.toStdString() == "")
        synaFolk(_fService.getTolvufolk());

    else if (flokkur == "Name")
        synaFolk(_fService.leitaStreng("Nafn", arg1.toStdString(), 'a'));

    else if (flokkur == "Gender")
    {
        string kynid = arg1.toStdString();
        for (size_t i = 0; i < kynid.length(); ++i)
        {
            kynid[i] = tolower(kynid[i]);
        }

        if (kynid == "male")
            synaFolk(_fService.leitaStreng("Kyn", "m", 'a'));
        else if (kynid == "female")
            synaFolk(_fService.leitaStreng("Kyn", "f", 'a'));
        else
            synaFolk(_fService.leitaStreng("Kyn", arg1.toStdString(), 'a'));
    }

    else if (flokkur == "Age")
        synaFolk(_fService.leitaHeiltolu("aldur", '=', arg1.toInt()));

    else if (flokkur == "Birth")
        synaFolk(_fService.leitaHeiltolu("faedingarar", '=', arg1.toInt()));

    else if (flokkur == "Death")
    {
        string aLifi = arg1.toStdString();
        for (size_t i = 0; i < aLifi.length(); ++i)
        {
            aLifi[i] = tolower(aLifi[i]);
        }
        if (aLifi == "still alive")
            synaFolk(_fService.leitaHeiltolu("danarar", '=', -1));
        else
            synaFolk(_fService.leitaHeiltolu("danarar", '=', arg1.toInt()));

    }
}

void adalgluggi::on_velFilterText_textChanged(const QString &arg1)
{
    string flokkur = ui->velFilterBox->currentText().toStdString();

    if (arg1.toStdString() == "")
        synaVelar(_vService.getVelar());

    else if (flokkur == "Name")
        synaVelar(_vService.leitaStreng("Nafn", arg1.toStdString(), 'a'));

    else if (flokkur == "Year built")
        synaVelar(_vService.leitaHeiltolu("ByggingarAr", '=', arg1.toInt() ));

    else if (flokkur == "Type")
        synaVelar(_vService.leitaStreng("Tegund", arg1.toStdString(), 'a'));

    else if (flokkur == "Built?")
    {
        synaVelar(_vService.leitaBool("Byggd", arg1.toInt() ));
    }


}

void adalgluggi::on_button_add_clicked()
{

}

void adalgluggi::on_button_delete_clicked()
{
    int folkCurrentIndex = ui->folkTable->currentIndex().row();

    tolvufolk folkCurrent = _folkCurrent.at(folkCurrentIndex);

    _fService.eydaStakiTolvufolk(folkCurrent.getID());

    //vantar að gera að ef þetta virkaði þá fer í þetta annars error message
    ui->folkFilterText->setText("");
    synaFolk(_fService.getTolvufolk());
    ui->button_delete->setEnabled(false);

}

void adalgluggi::on_button_update_clicked()
{
    uppfaeraFolkGluggi uppFolkGluggi;
    uppFolkGluggi.exec();
}

void adalgluggi::on_button_purge_clicked()
{

}

void adalgluggi::on_folkTable_clicked(const QModelIndex &index)
{
    ui->button_update->setEnabled(true);
    ui->button_delete->setEnabled(true);
}
