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

    void setFolk(tolvufolk folk);

    ~uppfaeraFolkGluggi();

private slots:
    void on_UppfHaettaTakki_clicked();

private:
    Ui::uppfaeraFolkGluggi *ui;

    tolvufolkService _fService;
    tolvufolk _target;
};

#endif // UPPFAERAFOLKGLUGGI_H
