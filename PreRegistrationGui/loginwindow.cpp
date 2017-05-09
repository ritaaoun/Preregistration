#include "loginwindow.h"
#include "ui_loginwindow.h"

LogInWindow::LogInWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogInWindow)
{
    ui->setupUi(this);
    ui->labelMessage->setStyleSheet("QLabel { color : red; }");
}

LogInWindow::~LogInWindow()
{
    delete ui;
}

void LogInWindow::on_pbLogIn_clicked()
{
    ui->labelMessage->setText("");

    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();

    bool success = APIService::getInstance()->userLogIn(username, password);

    if(success)
    {
        this->close();

        if(User::getUser()->getType() == User::Type::ADMINISTRATOR)
        {
            SystemWindowAdminstrator* w = new SystemWindowAdminstrator();
            w->show();
        }
        else
        {
            SystemWindow* w = new SystemWindow();
            w->show();
        }

    }
    else
    {
        ui->labelMessage->setText("Username or password incorrect.");
        ui->lePassword->clear();
    }
}
