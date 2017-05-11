#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "systemwindowprofessor.h"
#include "systemwindowadminstrator.h"

namespace Ui {
class LogInWindow;
}

class LogInWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LogInWindow(QWidget *parent = 0);
    ~LogInWindow();

private slots:
    void on_pbLogIn_clicked();

private:
    Ui::LogInWindow *ui;
};

#endif // LOGINWINDOW_H
