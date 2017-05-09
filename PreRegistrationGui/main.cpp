#include <QApplication>
#include <QtGui>
#include <iostream>
#include "loginwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LogInWindow w;
    w.show();

    return app.exec();
}
