#include <QtGui>
#include <QtCore>
#include <QApplication>
#include "home.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Home homeScreen;
    homeScreen.show();

    return app.exec();
}
