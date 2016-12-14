#ifndef TORTIMAVEL_H
#define TORTIMAVEL_H

#include <QDialog>
#include <QMessageBox>
#include "services/velarservice.h"

namespace Ui {
class tortimavel;
}

class tortimavel : public QDialog
{
    Q_OBJECT

public:
    explicit tortimavel(QWidget *parent = 0);
    ~tortimavel();

private slots:
    void on_button_confirm_clicked();

    void on_Button_cancel_clicked();

private:
    Ui::tortimavel *ui;
    velarService _service;
};

#endif // TORTIMAVEL_H
