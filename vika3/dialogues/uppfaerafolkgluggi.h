#ifndef UPPFAERAFOLKGLUGGI_H
#define UPPFAERAFOLKGLUGGI_H

#include "services/tolvufolkservice.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class uppfaeraFolkGluggi;
}

class uppfaeraFolkGluggi : public QDialog
{
    Q_OBJECT

public:
    explicit uppfaeraFolkGluggi(QWidget *parent = 0);

    void setFolk(tolvufolk folk);
    void getFolk();

    ~uppfaeraFolkGluggi();

private slots:
    void on_UppfHaettaTakki_clicked();

    void on_UppfaeraFolkTakki_clicked();

private:
    Ui::uppfaeraFolkGluggi *ui;

    tolvufolkService _fService;
    tolvufolk _target;
};

#endif // UPPFAERAFOLKGLUGGI_H
