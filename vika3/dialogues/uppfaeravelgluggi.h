#ifndef UPPFAERAVELGLUGGI_H
#define UPPFAERAVELGLUGGI_H

#include <QDialog>
#include "services/velarservice.h"

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
};

#endif // UPPFAERAVELGLUGGI_H
