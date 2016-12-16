#include "adalgluggi.h"
#include "ui_adalgluggi.h"
#include "dialogues/uppfaerafolkgluggi.h"
#include "dialogues/uppfaeravelgluggi.h"
#include "dialogues/addscientist.h"
#include "dialogues/addmachine.h"
#include "dialogues/tortimafolk.h"
#include "dialogues/tortimavel.h"
#include "dialogues/help.h"

#include <string>
#include <QFileDialog>
#include <QDebug>
#include <QString>
#include <istream>
#include <Qpixmap>
#include <QMenu>
#include <QKeyEvent>
#include <QDesktopServices>
#include <QUrl>
#include <QWidget>
#include <Qset>

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
    _unlinking = false;
    ui->folkTable->setColumnHidden(0,true); //Hide ID columns in table widgets
    ui->velTable->setColumnHidden(0,true);
    ui->button_warning->setStyleSheet("background-color: red");
    ui->button_back->setVisible(false);
    ui->vButton_back->setVisible(false);
    this->installEventFilter(this);

}

adalgluggi::~adalgluggi()
{
    delete ui;
}

void adalgluggi::synaAlltFolk()
{
    _folkCurrent = _fService.getTolvufolk();
    synaFolk(_folkCurrent);
    ui->folkDisplayLabel->setText("<h3>Displaying all scientists</h3>");
}

void adalgluggi::synaAllarVelar()
{
    _velarCurrent = _vService.getVelar();
    synaVelar(_velarCurrent);
    ui->velDisplayLabel->setText("<h3>Displaying all machines</h3>");
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
    {
        if (_unlinking)
        {
            if (index == 0)
            {
                ui->velDisplayLabel->setText(ui->velDisplayLabel->text() + "f5 to refresh");
            }
            else if (index == 1)
            {
                ui->folkDisplayLabel->setText(ui->folkDisplayLabel->text() + "f5 to refresh");
            }
        }
        _linking = _unlinking = false;
    }
    defaultVButtons();
    defaultFButtons();
}

void adalgluggi::on_folkFilterText_textChanged(const QString &arg1)
{
    string flokkur = ui->folkFilterBox->currentText().toStdString();

    if (arg1.toStdString() == ""){
        synaAlltFolk();
        return;
    }

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

    ui->folkDisplayLabel->setText("<h4>Displaying scientists filtered by " + QString(flokkur.c_str()) + " '" + arg1 + "'</h4>f5 to refresh");
}

void adalgluggi::on_velFilterText_textChanged(const QString &arg1)
{
    string flokkur = ui->velFilterBox->currentText().toStdString();

    if (arg1.toStdString() == ""){
        synaAllarVelar();
        return;
    }

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

    ui->velDisplayLabel->setText("<h4>Displaying machines filtered by " + QString(flokkur.c_str()) + " '" + arg1 + "'</h4>f5 to refresh");
}

void adalgluggi::on_button_add_clicked()
{
    AddScientist gluggiBaeta;

    if (gluggiBaeta.exec() == 0)
    {
        synaAlltFolk();
        ui->statusBar->showMessage("Scientist(s) added", 1500);
    }

}

void adalgluggi::on_button_delete_clicked()
{
    if(deleteConfirmation("scientist")){
        _fService.eydaStakiTolvufolk(getFolkID());
        ui->statusBar->showMessage("Scientist deleted", 1500);
    }
    else
        return;
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
    if (uppFolkGluggi.exec() == 0){
        synaAlltFolk();
        ui->statusBar->showMessage("Scientist updated", 1500);
    }
}

void adalgluggi::on_button_purge_clicked()
{
    tortimafolk torTimaFolk;
    if (torTimaFolk.exec() == 0){
        synaAlltFolk();
        ui->statusBar->showMessage("Scientists purged", 1500);
    }
}

void adalgluggi::on_folkTable_clicked(const QModelIndex &index)
{
    if (!_linking)
    {
        toggleFButtons(true);
    }
    else
    {
        if (!_unlinking)
        {
            if (_vService.venslaVidVel(getFolkID(), _vSelect.getID()))
            {
                ui->statusBar->showMessage("Linking successful", 1500);
            }
            else
            {
                ui->statusBar->showMessage("Linking failed, duplicate links", 1500);
            }
        }
        else
        {
            _vService.eydaStakiVensl(getFolkID(), _vSelect.getID());
            ui->statusBar->showMessage("link deleted", 1500);
            _unlinking = false;
        }
        _linking = false;
        ui->tabsList->setCurrentIndex(1);
    }
}

void adalgluggi::on_vButton_add_clicked()
{
    addmachine gluggiBaetaV;

    if(gluggiBaetaV.exec() == 0){
        synaAllarVelar();
        ui->statusBar->showMessage("Machine(s) added", 1500);
    }
}

void adalgluggi::on_vButton_delete_clicked()
{
    if(deleteConfirmation("machine")){
        _vService.eydaStakiVel(getVelarID());
        ui->statusBar->showMessage("Machine deleted", 1500);
    }
    else
        return;
    ui->velFilterText->setText("");
    synaAllarVelar();
    ui->vButton_delete->setEnabled(false);
    ui->vButton_update->setEnabled(false);
}

void adalgluggi::on_vButton_update_clicked()
{
    velar velarCurrent = _vService.getStaktVelar(getVelarID());

    uppfaeravelgluggi uppVelGluggi;
    uppVelGluggi.setVel(velarCurrent);

    if (uppVelGluggi.exec()){
        synaAllarVelar();
        ui->statusBar->showMessage("Machine updated", 1500);
    }
}

void adalgluggi::on_vButton_purge_clicked()
{
    tortimavel torTimaVel;
    if (torTimaVel.exec() == 0){
        synaAllarVelar();
        ui->statusBar->showMessage("Machines purged", 1500);
    }
}

void adalgluggi::on_velTable_clicked(const QModelIndex &index)
{
    if (!_linking)
    {
        toggleVButtons(true);
    }
    else
    {
        if (!_unlinking)
        {
            if (_fService.venslaVidVel(_fSelect.getID(),getVelarID()))
            {
                ui->statusBar->showMessage("Linking successful", 1500);
            }
            else
            {
                ui->statusBar->showMessage("Linking failed, duplicate links", 1500);
            }
        }
        else
        {
            _fService.eydaStakiVensl(_fSelect.getID(), getVelarID());
            ui->statusBar->showMessage("Link deleted", 1500);
            _unlinking = false;
        }
        _linking = false;
        ui->tabsList->setCurrentIndex(0);
    }
}

void adalgluggi::on_button_AddLink_clicked()
{
    _fSelect = _fService.getStaktTolvufolk(getFolkID());

    ui->tabsList->setCurrentIndex(1);
    ui->vButton_back->setVisible(true);
    _linking = true;
    _unlinking = false;
    toggleVButtons(false);
}

void adalgluggi::on_vButton_AddLink_clicked()
{
    _vSelect = _vService.getStaktVelar(getVelarID());

    ui->tabsList->setCurrentIndex(0);
    ui->button_back->setVisible(true);
    _linking = true;
    _unlinking = false;
    toggleFButtons(false);
}

void adalgluggi::on_button_showLinks_clicked()
{
    _fSelect = _fService.getStaktTolvufolk(getFolkID());

    ui->vButton_back->setVisible(true);
    ui->tabsList->setCurrentIndex(1);
    synaVelar(_vService.getVelarVensl(_fSelect.getID()));
    ui->velDisplayLabel->setText("<h4>Displaying machines linked to " + QString(_fSelect.getNafn().c_str()) + "</h4>f5 to refresh");
}

void adalgluggi::on_vButton_showLinks_clicked()
{
    _vSelect = _vService.getStaktVelar(getVelarID());

    ui->button_back->setVisible(true);
    ui->tabsList->setCurrentIndex(0);
    synaFolk(_fService.getTolvufolkVensl(_vSelect.getID()));
    ui->folkDisplayLabel->setText("<h4>Displaying scientists linked to " + QString(_vSelect.getVelaNafn().c_str()) + "</h4>f5 to refresh");
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
    ui->button_showLinks->setEnabled(false);
    ui->button_removeLink->setEnabled(false);
}

void adalgluggi::defaultVButtons()
{
    ui->vButton_add->setEnabled(true);
    ui->vButton_delete->setEnabled(false);
    ui->vButton_update->setEnabled(false);
    ui->vButton_purge->setEnabled(true);
    ui->vButton_AddLink->setEnabled(false);
    ui->vButton_showLinks->setEnabled(false);
    ui->vButton_removeLink->setEnabled(false);
}

void adalgluggi::toggleVButtons(bool enabled)
{
    ui->vButton_add->setEnabled(enabled);
    ui->vButton_delete->setEnabled(enabled);
    ui->vButton_update->setEnabled(enabled);
    ui->vButton_purge->setEnabled(enabled);
    ui->vButton_AddLink->setEnabled(enabled);
    ui->vButton_showLinks->setEnabled(enabled);
    ui->vButton_removeLink->setEnabled(enabled);
}

void adalgluggi::toggleFButtons(bool enabled)
{
    ui->button_add->setEnabled(enabled);
    ui->button_delete->setEnabled(enabled);
    ui->button_update->setEnabled(enabled);
    ui->button_purge->setEnabled(enabled);
    ui->button_AddLink->setEnabled(enabled);
    ui->button_showLinks->setEnabled(enabled);
    ui->button_removeLink->setEnabled(enabled);
}


bool adalgluggi::eventFilter(QObject * obj, QEvent * event)
{
    if(event->type()==QEvent::KeyPress) {

        pressedKeys += ((QKeyEvent*)event)->key();

        if(pressedKeys.contains(constants::CONTROL_KEY_NUMBER) && pressedKeys.contains(constants::L_KEY_NUMBER) )
        {
            LkeyPressed();
            //cmd and A are pressed
        }
        if(pressedKeys.contains(constants::CONTROL_KEY_NUMBER) && pressedKeys.contains(constants::S_KEY_NUMBER) )
        {
            SkeyPressed();
            //cmd and A are pressed
        }
        if(pressedKeys.contains(constants::CONTROL_KEY_NUMBER) && pressedKeys.contains(constants::R_KEY_NUMBER) )
        {
            RkeyPressed();
            //cmd and A are pressed
        }

    }
    else if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
    }

    return false;
}

void adalgluggi::keyReleaseEvent(QKeyEvent* event)
{
    qDebug () << event->key();

    switch (event->key())
    {
        case constants::DELETE_KEY_NUMBER:
            if(ui->tabsList->currentIndex() == 0)
            deleteKeyPressed("scientist");
            if(ui->tabsList->currentIndex() == 1)
            deleteKeyPressed("machine");
            break;
        case constants::ESCAPE_KEY_NUMBER:
            escapeKeyPressed();
            break;
        case constants::F5_KEY_NUMBER:
            F5keyPressed();
            break;
        case constants::LEFT_ARROW:
            tabToLeft();
            break;
        case constants::RIGHT_ARROW:
            tabToRight();
            break;

    }
}

void adalgluggi::tabToLeft()
{
    int index = ui->tabsList->currentIndex();
    if(index != 0)
    {
        index--;
        ui->tabsList->setCurrentIndex(index);
    }
}

void adalgluggi::tabToRight()
{
    int index = ui->tabsList->currentIndex();
    if(index != ui->tabsList->count()-1)
    {
        index++;
        ui->tabsList->setCurrentIndex(index);
    }
}

void adalgluggi::LkeyPressed()
{
    if(ui->folkTable->currentRow() != -1 && ui->tabsList->currentIndex() == 0)
        on_button_AddLink_clicked();

    if(ui->velTable->currentRow() != -1 && ui->tabsList->currentIndex() == 1)
        on_vButton_AddLink_clicked();
}

void adalgluggi::SkeyPressed()
{
    if(ui->folkTable->currentRow() != -1 && ui->tabsList->currentIndex() == 0)
        on_button_showLinks_clicked();

    if(ui->velTable->currentRow() != -1 && ui->tabsList->currentIndex() == 1)
        on_button_showLinks_clicked();
}

void adalgluggi::RkeyPressed()
{
    if(ui->folkTable->currentRow() != -1 && ui->tabsList->currentIndex() == 0)
        on_button_removeLink_clicked();

    if(ui->velTable->currentRow() != -1 && ui->tabsList->currentIndex() == 1)
        on_button_removeLink_clicked();
}


void adalgluggi::F5keyPressed()
{
    if(ui->tabsList->currentIndex() == 0 && !_unlinking)
    {
        synaAlltFolk();
        ui->folkFilterText->setText("");
    }

    else if(ui->tabsList->currentIndex() == 1 && !_unlinking)
    {
        synaAllarVelar();
        ui->velFilterText->setText("");

    }
}

void adalgluggi::deleteKeyPressed(const char* flokkur)
{

    if(ui->folkTable->currentRow() != -1 && ui->tabsList->currentIndex() == 0)
    {
        if(!(ui->radiobutton_delete_confirmation->isChecked()))
        {
            if(deleteConfirmation(flokkur))
            _fService.eydaStakiTolvufolk(getFolkID());
            ui->folkFilterText->setText("");
            synaAlltFolk();
            ui->button_delete->setEnabled(false);
            ui->button_update->setEnabled(false);

        }
        else
        {
            _fService.eydaStakiTolvufolk(getFolkID());
            ui->folkFilterText->setText("");
            synaAlltFolk();
            ui->button_delete->setEnabled(false);
            ui->button_update->setEnabled(false);
        }
    }
    else if(ui->velTable->currentRow() != -1 && ui->tabsList->currentIndex() == 1)
    {
        if(!(ui->radiobutton_delete_confirmation->isChecked()))
        {
            if(deleteConfirmation(flokkur))
            _vService.eydaStakiVel(getVelarID());
            ui->velFilterText->setText("");
            synaAllarVelar();
            ui->button_delete->setEnabled(false);
            ui->button_update->setEnabled(false);

        }
        else
        {
            _vService.eydaStakiVel(getVelarID());
            ui->velFilterText->setText("");
            synaAllarVelar();
            ui->button_delete->setEnabled(false);
            ui->button_update->setEnabled(false);
        }
    }
}


bool adalgluggi::deleteConfirmation(const char* flokkur)
{
    QMessageBox* box = new QMessageBox;
    box->setAttribute(Qt::WA_DeleteOnClose, true);
    box->setWindowTitle(QString("Delete ") + QString(flokkur));
    box->setInformativeText(QString("Do you want to remove this ") +QString(flokkur)+ QString(" from the database? "));
    box->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    box->setWindowIcon(QIcon(":/Icons/delete.png"));

    if(box->exec() == QMessageBox::Yes)
        return true;
    else
        return false;
}

void adalgluggi::escapeKeyPressed()
{
    QMessageBox* box = new QMessageBox;
    box->setAttribute(Qt::WA_DeleteOnClose, true);
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



void adalgluggi::on_button_removeLink_clicked()
{
    _fSelect = _fService.getStaktTolvufolk(getFolkID());

    ui->vButton_back->setVisible(true);
    ui->tabsList->setCurrentIndex(1);
    synaVelar(_vService.getVelarVensl(_fSelect.getID()));
    _linking = _unlinking = true;
    toggleVButtons(false);
    ui->velDisplayLabel->setText("<h3>Displaying machines linked to " + QString(_fSelect.getNafn().c_str()) + "</h3>");
}

void adalgluggi::on_vButton_removeLink_clicked()
{
    _vSelect = _vService.getStaktVelar(getVelarID());

    ui->tabsList->setCurrentIndex(0);
    ui->button_back->setVisible(true);
    synaFolk(_fService.getTolvufolkVensl(_vSelect.getID()));
    _linking = _unlinking = true;
    toggleFButtons(false);
    ui->folkDisplayLabel->setText("<h3>Displaying scientists linked to " + QString(_vSelect.getVelaNafn().c_str()) + "</h3>");
}

void adalgluggi::on_tabsList_tabBarClicked(int index)
{
    //Smella á current tab þá refreshast allur listinn
    if (index == ui->tabsList->currentIndex() && !_unlinking)
    {
        if (index == 0)
        {
            synaAlltFolk();
            ui->folkFilterText->setText("");
        }
        else if (index == 1)
        {
            synaAllarVelar();
            ui->velFilterText->setText("");
        }
    }
}

void adalgluggi::on_button_warning_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=3WSe9ugpXIw", QUrl::TolerantMode));
}

void adalgluggi::on_button_back_clicked()
{
        ui->tabsList->setCurrentIndex(1);
        ui->button_back->setVisible(false);

}

void adalgluggi::on_vButton_back_clicked()
{
        ui->tabsList->setCurrentIndex(0);
        ui->vButton_back->setVisible(false);
}

void adalgluggi::on_velFilterBox_currentIndexChanged(const QString &arg1)
{
    on_velFilterText_textChanged(ui->velFilterText->text());
}

void adalgluggi::on_folkFilterBox_currentIndexChanged(const QString &arg1)
{
    on_folkFilterText_textChanged(ui->folkFilterText->text());
}

void adalgluggi::on_actionHelp_triggered()
{
    hhelp = new help(this);
    hhelp->show();
}
