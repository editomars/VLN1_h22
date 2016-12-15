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

    void on_button_AddLink_clicked();

    void on_vButton_AddLink_clicked();

    void keyReleaseEvent(QKeyEvent* event);

    void on_button_showLinks_clicked();

    void on_vButton_showLinks_clicked();

    void on_radiobutton_delete_confirmation_clicked();
private:
    Ui::adalgluggi *ui;
    tolvufolkService _fService;
    velarService _vService;
    vector<tolvufolk> _folkCurrent;
    tolvufolk _fSelect;
    vector<velar> _velarCurrent;
    velar _vSelect;
    bool _linking;

    void synaAlltFolk();
    void synaAllarVelar();
    void synaFolk(const vector<tolvufolk>& folk);
    void synaVelar(const vector<velar>& velar);
    int getFolkID() const; //Sækir ID úr hidden column í folk table ef eitthver röð er valin
    int getVelarID() const; //sama og folk, nema fyrir velar
    void toggleVButtons(bool enabled); //setur alla UI takka í computers tab enabled = true eða false
    void toggleFButtons(bool enabled); //sama og VButtons nema fyrir scientist tab
    void defaultFButtons(); //Setur alla hnappa í scientist tab í default enabled state
    void defaultVButtons(); //sama og scientist nema fyrir vélar
    void escapeKeyPressed(); //Escape key release handler
    void deleteKeyPressed(); //Delete key release handler
};

#endif // ADALGLUGGI_H
