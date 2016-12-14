#ifndef TORTIMAVEL_H
#define TORTIMAVEL_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class tortimavel;
}

class tortimavel : public QDialog
{
    Q_OBJECT

public:
    explicit tortimavel(QWidget *parent = 0);
    ~tortimavel();

private:
    Ui::tortimavel *ui;
};

#endif // TORTIMAVEL_H
