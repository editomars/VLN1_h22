#include "tortimavel.h"
#include "ui_tortimavel.h"
#include <QMessageBox>

tortimavel::tortimavel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tortimavel)
{
    ui->setupUi(this);
}

tortimavel::~tortimavel()
{
    delete ui;
}
