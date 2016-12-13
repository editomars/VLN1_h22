#ifndef UPPFAERAFOLKGLUGGI_H
#define UPPFAERAFOLKGLUGGI_H

#include <QDialog>
#include "services/tolvufolkservice.h"

namespace Ui {
class uppfaeraFolkGluggi;
}

class uppfaeraFolkGluggi : public QDialog
{
    Q_OBJECT

public:
    explicit uppfaeraFolkGluggi(QWidget *parent = 0);
    ~uppfaeraFolkGluggi();

private slots:
    void on_UppfHaettaTakki_clicked();

private:
    Ui::uppfaeraFolkGluggi *ui;

    tolvufolkService _fService;
};

#endif // UPPFAERAFOLKGLUGGI_H
