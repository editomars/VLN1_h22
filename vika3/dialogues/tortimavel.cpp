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

void tortimavel::on_button_confirm_clicked()
{
    int spurning_svar = QMessageBox::question(this, "Are you sure", "All that work down the drain","Confirm", "cancel" );
    if(spurning_svar == 0)
    {
        int spurning_svar2 = QMessageBox::question(this, "no takessies backsies", "Are you super serius about deleting everything","Confirm", "cancel" );
        if (spurning_svar2 == 0)
        {
            int spurning_svar3 = QMessageBox::question(this, "you will have to start over", "By Thors hammer are you sure","Confirm", "cancel" );

            if(spurning_svar3 == 0)
            {
                _service.tortimaTolvuVelar();
                this->done(0);
            }
            else
                this->done(1);
        }
        else
            this->done(1);
    }
    else
        this->done(1);

    this->done(1);
}


void tortimavel::on_Button_cancel_clicked()
{
    this->done(1);
}
