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

    void on_tabsList_currentChanged(int index);

private:
    Ui::adalgluggi *ui;

    void synaFolk(const vector<tolvufolk>& folk);
    void synaVelar(const vector<velar>& velar);

    tolvufolkService _fService;
    velarService _vService;
    vector<tolvufolk> _folkCurrent;
    vector<velar> _velarCurrent;
};

#endif // ADALGLUGGI_H