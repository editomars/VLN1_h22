#include "adalgluggi.h"
#include "ui_adalgluggi.h"
#include "dialogues/uppfaerafolkgluggi.h"
#include "dialogues/uppfaeravelgluggi.h"
#include "dialogues/addscientist.h"
#include "dialogues/addmachine.h"
#include "dialogues/tortimafolk.h"
#include "dialogues/tortimavel.h"

#include <string>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <istream>
#include <Qpixmap>
#include <QMenu>

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
    _linking = false;
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



void adalgluggi::disableVButtons()
{
    ui->vButton_add->setEnabled(false);
    ui->vButton_delete->setEnabled(false);
    ui->vButton_update->setEnabled(false);
    ui->vButton_purge->setEnabled(false);
    ui->vButton_AddLink->setEnabled(false);
}

void adalgluggi::disableFButtons()
{
    ui->button_add->setEnabled(false);
    ui->button_delete->setEnabled(false);
    ui->button_update->setEnabled(false);
    ui->button_purge->setEnabled(false);
    ui->button_AddLink->setEnabled(false);
}

void adalgluggi::defaultFButtons()
{
    ui->button_add->setEnabled(true);
    ui->button_delete->setEnabled(false);
    ui->button_update->setEnabled(false);
    ui->button_purge->setEnabled(true);
    ui->button_AddLink->setEnabled(false);
}

void adalgluggi::defaultVButtons()
{
    ui->vButton_add->setEnabled(true);
    ui->vButton_delete->setEnabled(false);
    ui->vButton_update->setEnabled(false);
    ui->vButton_purge->setEnabled(true);
    ui->vButton_AddLink->setEnabled(false);
}

void adalgluggi::on_tabsList_currentChanged(int index)
{
    switch (index)
    {
        case 0:

            ui->vButton_delete->setEnabled(false);
            ui->vButton_update->setEnabled(false);
            ui->vButton_AddLink->setEnabled(false);

            synaFolk(_folkCurrent);

            if (_linking)
            {
                _linking = false;
                defaultVButtons();
                defaultFButtons();
            }
            break;
        case 1:

            ui->button_update->setEnabled(false);
            ui->button_delete->setEnabled(false);
            ui->button_AddLink->setEnabled(false);

            synaVelar(_velarCurrent);

            if (_linking)
            {
                _linking = false;
                defaultFButtons();
                defaultVButtons();
            }
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
    AddScientist gluggiBaeta;

    if (gluggiBaeta.exec() == 0)
    {
        synaFolk(_fService.getTolvufolk());
    }

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
    ui->button_update->setEnabled(false);

}

void adalgluggi::on_button_update_clicked()
{
    //Highlited gæji verður target
    int folkCurrentIndex = ui->folkTable->currentIndex().row();
    tolvufolk folkCurrent = _folkCurrent.at(folkCurrentIndex);

    uppfaeraFolkGluggi uppFolkGluggi;
    uppFolkGluggi.setFolk(folkCurrent);
    uppFolkGluggi.exec();
}

void adalgluggi::on_button_purge_clicked()
{
    tortimafolk torTimaFolk;
    if (torTimaFolk.exec() == 0)
    {
        synaFolk(_fService.getTolvufolk());
    }
}

void adalgluggi::on_folkTable_clicked(const QModelIndex &index)
{
    if (!_linking)
    {
        ui->button_update->setEnabled(true);
        ui->button_delete->setEnabled(true);
        ui->button_AddLink->setEnabled(true);
    }
    else
    {
        int folkCurrentIndex = ui->folkTable->currentIndex().row();
        tolvufolk folkCurrent = _folkCurrent.at(folkCurrentIndex);

        _vService.venslaVidVel(folkCurrent.getID(),_vSelect.getID());

        _linking = false;

        ui->tabsList->setCurrentIndex(1);
    }
}

void adalgluggi::on_vButton_add_clicked()
{
    addmachine gluggiBaetaV;

    gluggiBaetaV.exec();

}

void adalgluggi::on_vButton_delete_clicked()
{
    int velarCurrentIndex = ui->velTable->currentIndex().row();

    velar velarCurrent = _velarCurrent.at(velarCurrentIndex);

    _vService.eydaStakiVel(velarCurrent.getID());

    //vantar að gera að ef þetta virkaði þá fer í þetta annars error message
    ui->velFilterText->setText("");
    synaVelar(_vService.getVelar());
    ui->vButton_delete->setEnabled(false);
    ui->vButton_update->setEnabled(false);


}

void adalgluggi::on_vButton_update_clicked()
{
    //Highlited gæji verður target
    int velarCurrentIndex = ui->velTable->currentIndex().row();
    velar velarCurrent = _velarCurrent.at(velarCurrentIndex);

    uppfaeravelgluggi uppVelGluggi;
    uppVelGluggi.setVel(velarCurrent);
    uppVelGluggi.exec();
}

void adalgluggi::on_vButton_purge_clicked()
{
    tortimavel torTimaVel;
    if (torTimaVel.exec() == 0)
    {
        synaVelar(_vService.getVelar());
    }
}

void adalgluggi::on_velTable_clicked(const QModelIndex &index)
{
    if (!_linking)
    {
        ui->vButton_delete->setEnabled(true);
        ui->vButton_update->setEnabled(true);
        ui->vButton_AddLink->setEnabled(true);
    }
    else
    {
        int velarCurrentIndex = ui->velTable->currentIndex().row();
        velar velarCurrent = _velarCurrent.at(velarCurrentIndex);

        _fService.venslaVidVel(_fSelect.getID(),velarCurrent.getID());

        _linking = false;

        ui->tabsList->setCurrentIndex(0);
    }
}

void adalgluggi::on_button_AddLink_clicked()
{
    int folkCurrentIndex = ui->folkTable->currentIndex().row();
    _fSelect = _folkCurrent.at(folkCurrentIndex);

    ui->tabsList->setCurrentIndex(1);
    _linking = true;
    disableVButtons();



}

void adalgluggi::on_vButton_AddLink_clicked()
{
    int velarCurrentIndex = ui->velTable->currentIndex().row();
    _vSelect = _velarCurrent.at(velarCurrentIndex);

    ui->tabsList->setCurrentIndex(0);
    _linking = true;
    disableFButtons();


}

void adalgluggi::on_button_showVLinks_clicked()
{

}
