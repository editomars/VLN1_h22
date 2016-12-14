#include "tortimafolk.h"
#include "ui_tortimafolk.h"



tortimafolk::tortimafolk(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tortimafolk)
{
    ui->setupUi(this);
}

tortimafolk::~tortimafolk()
{
    delete ui;
}

void tortimafolk::on_button_cancel_clicked()
{
    this->done(0);
}

void tortimafolk::on_button_confirm_clicked()
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
                _service.tortimaTolvufolk();
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
