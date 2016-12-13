#include "adalgluggi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    adalgluggi gluggi;
    gluggi.show();

    return application.exec();
}
