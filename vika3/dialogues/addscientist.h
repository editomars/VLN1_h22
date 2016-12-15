#ifndef ADDSCIENTIST_H
#define ADDSCIENTIST_H

#include "services/tolvufolkservice.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddScientist;
}

class AddScientist : public QDialog
{
    Q_OBJECT

public:
    explicit AddScientist(QWidget *parent = 0);
    ~AddScientist();

private slots:
    void on_button_add_clicked();

    void on_button_cancel_clicked();
private:
    Ui::AddScientist *ui;
    tolvufolkService _service;
    bool _added;
};

#endif // ADDSCIENTIST_H
