#ifndef TORTIMAFOLK_H
#define TORTIMAFOLK_H

#include <QDialog>
#include <QMessageBox>
#include "services/tolvufolkservice.h"

namespace Ui {
class tortimafolk;
}

class tortimafolk : public QDialog
{
    Q_OBJECT

public:
    explicit tortimafolk(QWidget *parent = 0);
    ~tortimafolk();

private slots:
    void on_button_cancel_clicked();

    void on_button_confirm_clicked();

private:
    Ui::tortimafolk *ui;
    tolvufolkService _service;
};

#endif // TORTIMAFOLK_H
