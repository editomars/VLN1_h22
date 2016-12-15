#ifndef ADDMACHINE_H
#define ADDMACHINE_H

#include "services/velarservice.h"

#include <QDialog>
#include <QMessageBox>

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
private:
    Ui::addmachine *ui;
    velarService _vService;
    bool _added;
};

#endif // ADDMACHINE_H
