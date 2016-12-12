#include "adalgluggi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    adalgluggi w;
    w.show();

    return a.exec();
}
