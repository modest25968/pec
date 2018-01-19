#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("TestOrg");
    QCoreApplication::setApplicationName("Pec");
    MainWindow w;
    w.show();

    return a.exec();
}
