#ifndef ADDMACHINE_H
#define ADDMACHINE_H

#include "services/velarservice.h"

#include <QDialog>

namespace Ui {
class addmachine;
}

class addmachine : public QDialog
{
    Q_OBJECT

public:
    explicit addmachine(QWidget *parent = 0);
    ~addmachine();

private slots:
    void on_vButton_add_clicked();

    void on_vButton_cancel_clicked();

    void on_vRadio_built_clicked();

    void on_vRadio_notBuilt_clicked();


private:
    Ui::addmachine *ui;
    velarService _vService;
};

#endif // ADDMACHINE_H
