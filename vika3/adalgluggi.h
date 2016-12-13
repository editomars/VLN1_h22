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

private:
    Ui::adalgluggi *ui;

    void synaFolk(vector<tolvufolk> folk);

    tolvufolkService _fService;
    velarService _vService;
    vector<tolvufolk> _folkCurrent;
    vector<velar> _velarCurrent;
};

#endif // ADALGLUGGI_H
