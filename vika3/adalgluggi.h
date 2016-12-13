#ifndef ADALGLUGGI_H
#define ADALGLUGGI_H

#include <QMainWindow>
#include "services/tolvufolkservice.h"
#include "services/velarservice.h"

namespace Ui {
class adalgluggi;
}

class adalgluggi : public QMainWindow
{
    Q_OBJECT

public:
    explicit adalgluggi(QWidget *parent = 0);
    ~adalgluggi();

private slots:
    void on_pushButton_clicked();

    void on_velar_clicked();

    void on_folk_clicked();

    void on_haetta_clicked();

private:
    Ui::adalgluggi *ui;

    tolvufolkService _fService;
    velarService _vService;
};

#endif // ADALGLUGGI_H
