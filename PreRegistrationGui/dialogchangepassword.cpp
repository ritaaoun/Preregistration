#include "dialogchangepassword.h"
#include "ui_dialogchangepassword.h"

DialogChangePassword::DialogChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChangePassword)
{
    ui->setupUi(this);
    ui->labelMessage->setStyleSheet("QLabel { color : red; }");
}

DialogChangePassword::~DialogChangePassword()
{
    delete ui;
}

void DialogChangePassword::on_pbConfirm_clicked()
{
    QString oldPassword = ui->leOldPassword->text();
    QString newPassword = ui->leNewPassword->text();
    QString confirmPassowrd = ui->leConfirmPassowrd->text();

    if(confirmPassowrd != newPassword)
    {
        ui->labelMessage->setStyleSheet("QLabel { color : red; }");
        ui->labelMessage->setText("New password doesn't match");
        clearInputs();
        return;
    }



    if(APIService::getInstance()->changePassword(oldPassword, newPassword))
    {
        ui->labelMessage->setStyleSheet("QLabel { color : green; }");
        ui->labelMessage->setText("Succesfully changed password");
        clearInputs();
    }
    else
    {
        ui->labelMessage->setStyleSheet("QLabel { color : red; }");
        ui->labelMessage->setText("Old password incorrect");
        clearInputs();
    }
}

void DialogChangePassword::clearInputs()
{
    ui->leOldPassword->clear();
    ui->leNewPassword->clear();
    ui->leConfirmPassowrd->clear();
}
