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

    void on_folkFilterText_textChanged(const QString &arg1);

    void on_velFilterText_textChanged(const QString &arg1);

    void on_button_add_clicked();

    void on_button_delete_clicked();

    void on_button_update_clicked();

    void on_button_purge_clicked();

    void on_folkTable_clicked(const QModelIndex &index);

    void on_vButton_add_clicked();

    void on_vButton_delete_clicked();

    void on_vButton_update_clicked();

    void on_vButton_purge_clicked();

    void on_velTable_clicked(const QModelIndex &index);

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
