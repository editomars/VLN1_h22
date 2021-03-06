#ifndef UPPFAERAVELGLUGGI_H
#define UPPFAERAVELGLUGGI_H

#include "services/velarservice.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class uppfaeravelgluggi;
}

class uppfaeravelgluggi : public QDialog
{
    Q_OBJECT

public:
    explicit uppfaeravelgluggi(QWidget *parent = 0);

    void setVel(velar vel);
    void getVel();

    ~uppfaeravelgluggi();

private slots:
    void on_UppfHaettaTakki_clicked();



    void on_UppfaeraVelTakki_clicked();

private:
    Ui::uppfaeravelgluggi *ui;

    velarService _vService;
    velar _target;
    bool _updated;
};

#endif // UPPFAERAVELGLUGGI_H
