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
#include <QKeyEvent>

adalgluggi::adalgluggi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adalgluggi)
{
    ui->setupUi(this);
    //init stillingar
    ui->tabsList->setCurrentIndex(0); //Force program to start in scientist tab
    ui->folkTable->horizontalHeader()->setVisible(true); //Fix missing headers
    synaAlltFolk();
    synaAllarVelar();
    _linking = false;
    ui->folkTable->setColumnHidden(0,true); //Hide ID columns in table widgets
    ui->velTable->setColumnHidden(0,true);
}

adalgluggi::~adalgluggi()
{
    delete ui;
}

void adalgluggi::synaAlltFolk()
{
    _folkCurrent = _fService.getTolvufolk();
    synaFolk(_folkCurrent);
}

void adalgluggi::synaAllarVelar()
{
    _velarCurrent = _vService.getVelar();
    synaVelar(_velarCurrent);
}

void adalgluggi::synaFolk(const vector<tolvufolk>& folk)
{
    ui->folkTable->clearContents();
    ui->folkTable->setSortingEnabled(false);

    ui->folkTable->setRowCount(folk.size());

    for (size_t row = 0; row < folk.size(); ++row)
    {
        QString ID = QString::number(folk[row].getID());
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
        ui->folkTable->setItem(row, 0, new QTableWidgetItem(ID));
        ui->folkTable->setItem(row, 1, new QTableWidgetItem(nafn));
        ui->folkTable->setItem(row, 2, new QTableWidgetItem(gender));
        ui->folkTable->setItem(row, 3, new QTableWidgetItem(aldur));
        ui->folkTable->setItem(row, 4, new QTableWidgetItem(fAr));
        ui->folkTable->setItem(row, 5, new QTableWidgetItem(dAr));
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
        QString ID = QString::number(velar[row].getID());
        QString nafn = QString::fromStdString(velar[row].getVelaNafn());
        QString bAr = QString::number(velar[row].getByggingarAr());
        QString byggd = QString(velar[row].getByggd() ? "Yes" : "No");
        QString tegund = QString::fromStdString(velar[row].getTegund());
        ui->velTable->setItem(row, 0, new QTableWidgetItem(ID));
        ui->velTable->setItem(row, 1, new QTableWidgetItem(nafn));
        ui->velTable->setItem(row, 2, new QTableWidgetItem(bAr));
        ui->velTable->setItem(row, 3, new QTableWidgetItem(byggd));
        ui->velTable->setItem(row, 4, new QTableWidgetItem(tegund));
    }

    _velarCurrent = velar;
    ui->velTable->setSortingEnabled(true);
}



void adalgluggi::on_tabsList_currentChanged(int index)
{
    switch (index)
    {
        case 0: //Scientist tab

            ui->vButton_delete->setEnabled(false);
            ui->vButton_update->setEnabled(false);
            ui->vButton_AddLink->setEnabled(false);

            synaFolk(_folkCurrent);
            break;
        case 1: //Computer tab

            ui->button_update->setEnabled(false);
            ui->button_delete->setEnabled(false);
            ui->button_AddLink->setEnabled(false);

            synaVelar(_velarCurrent);
            break;
        default:
            break;
    }
    if (_linking)
        _linking = false;
    defaultVButtons();
    defaultFButtons();
}

void adalgluggi::on_folkFilterText_textChanged(const QString &arg1)
{
    string flokkur = ui->folkFilterBox->currentText().toStdString();

    if (arg1.toStdString() == "")
        synaAlltFolk();

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
        synaAllarVelar();

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
        synaAlltFolk();
    }

}

void adalgluggi::on_button_delete_clicked()
{
    _fService.eydaStakiTolvufolk(getFolkID());

    ui->folkFilterText->setText("");
    synaAlltFolk();
    ui->button_delete->setEnabled(false);
    ui->button_update->setEnabled(false);

}

void adalgluggi::on_button_update_clicked()
{
    //Highlited gæji verður target
    tolvufolk folkCurrent = _fService.getStaktTolvufolk(getFolkID());

    uppfaeraFolkGluggi uppFolkGluggi;
    uppFolkGluggi.setFolk(folkCurrent);
    if (uppFolkGluggi.exec() == 0)
        synaAlltFolk();
}

void adalgluggi::on_button_purge_clicked()
{
    tortimafolk torTimaFolk;
    if (torTimaFolk.exec() == 0)
        synaAlltFolk();
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
   _vService.eydaStakiVel(getVelarID());

    ui->velFilterText->setText("");
    synaAllarVelar();
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
        synaAllarVelar();
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
    toggleVButtons(false);
}

void adalgluggi::on_vButton_AddLink_clicked()
{
    int velarCurrentIndex = ui->velTable->currentIndex().row();
    _vSelect = _velarCurrent.at(velarCurrentIndex);

    ui->tabsList->setCurrentIndex(0);
    _linking = true;
    toggleFButtons(false);
}

void adalgluggi::on_button_showLinks_clicked()
{
    int folkCurrentIndex = ui->folkTable->currentIndex().row();
    _fSelect = _folkCurrent.at(folkCurrentIndex);
}

void adalgluggi::on_vButton_showLinks_clicked()
{
    int velarCurrentIndex = ui->velTable->currentIndex().row();
    _vSelect = _velarCurrent.at(velarCurrentIndex);
}

int adalgluggi::getFolkID() const
{
    //Ef row != -1, þá er eitthver röð valin, sækir ID úr hidden column í folktable
    int row = ui->folkTable->currentRow();
    if (row != -1)
        return ui->folkTable->item(row,0)->text().toInt();
    return -1;
}

int adalgluggi::getVelarID() const
{
    int row = ui->velTable->currentRow();
    if (row != -1)
        return ui->velTable->item(row,0)->text().toInt();
    return -1;
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

void adalgluggi::toggleVButtons(bool enabled)
{
    ui->vButton_add->setEnabled(enabled);
    ui->vButton_delete->setEnabled(enabled);
    ui->vButton_update->setEnabled(enabled);
    ui->vButton_purge->setEnabled(enabled);
    ui->vButton_AddLink->setEnabled(enabled);
}

void adalgluggi::toggleFButtons(bool enabled)
{
    ui->button_add->setEnabled(enabled);
    ui->button_delete->setEnabled(enabled);
    ui->button_update->setEnabled(enabled);
    ui->button_purge->setEnabled(enabled);
    ui->button_AddLink->setEnabled(enabled);
}

void adalgluggi::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case constants::DELETE_KEY_NUMBER:
            deleteKeyPressed();
            break;
        case constants::ESCAPE_KEY_NUMBER:
            escapeKeyPressed();
            break;
    }

    QMessageBox* box = new QMessageBox;
    box->setWindowTitle(QString("Quit program"));
    box->setInformativeText(QString::number(event->key()));
}

void adalgluggi::deleteKeyPressed()
{
    if(ui->folkTable->currentRow() != -1)
    {
        if(ui->radiobutton_delete_confirmation->isChecked())
        {
            on_button_delete_clicked();
            return;
        }
        QMessageBox* box = new QMessageBox;
        box->setWindowTitle(QString("Delete scientist"));
        box->setInformativeText(QString("Do you want to remove this scientist from the database? "));
        box->setStandardButtons(QMessageBox::No | QMessageBox::Yes);

        if(box->exec() == QMessageBox::Yes)
            on_button_delete_clicked();
        else
            return;
        delete box;
    }
    else
        return;
}

void adalgluggi::escapeKeyPressed()
{
    QMessageBox* box = new QMessageBox;
    box->setWindowTitle(QString("Quit program"));
    box->setInformativeText(QString("Do you want to quit? "));
    box->setStandardButtons(QMessageBox::No | QMessageBox::Yes);

    if(box->exec() == QMessageBox::Yes)
        this->close();
    else
        return;
    delete box;
}


void adalgluggi::on_radiobutton_delete_confirmation_clicked(){}


