#include "dialogmessage.h"
#include "ui_dialogmessage.h"

DialogMessage::DialogMessage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogMessage)
{
    ui->setupUi(this);

    setWindowTitle("Messages");

    refresh();
}

DialogMessage::~DialogMessage()
{
    delete ui;
}

void DialogMessage::setUpUserSentMessages()
{
    std::vector<Message> messages = APIService::getInstance()->getUserSentMessages();

    ui->tableSent->setRowCount(0);

    for(int i = 0; i < messages.size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        items.push_back(new QTableWidgetItem(messages[i].getTo()));
        items.push_back(new QTableWidgetItem(messages[i].getSubject()));
        items.push_back(new QTableWidgetItem(messages[i].getMessage()));

        ui->tableSent->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
            ui->tableSent->setItem(i, j, items[j]);
        }
    }
}

void DialogMessage::setUpUserReceivedMessages()
{
    std::vector<Message> messages = APIService::getInstance()->getUserReceivedMessages();

    ui->tableReceived->setRowCount(0);

    for(int i = 0; i < messages.size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        items.push_back(new QTableWidgetItem(messages[i].getFrom()));
        items.push_back(new QTableWidgetItem(messages[i].getSubject()));
        items.push_back(new QTableWidgetItem(messages[i].getMessage()));

        ui->tableReceived->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
            ui->tableReceived->setItem(i, j, items[j]);
        }
    }
}

void DialogMessage::on_pbRefresh_clicked()
{
    refresh();
}

void DialogMessage::on_pbSend_clicked()
{
    QString to = ui->leUser->text();
    QString subject = ui->leSubject->text();
    QString message = ui->teMessage->toPlainText();

    if(to.isEmpty() || subject.isEmpty() || message.isEmpty())
    {
        return;
    }

    Message theMessage;
    theMessage.setFrom(User::getUser()->getUsername());
    theMessage.setTo(to);
    theMessage.setSubject(subject);
    theMessage.setMessage(message);

    if(APIService::getInstance()->sendMessage(theMessage))
    {
        ui->labelMessage->setStyleSheet("QLabel { color : green; }");
        ui->labelMessage->setText("Succesfully sent message to: " + to);
    }
    else
    {
        ui->labelMessage->setStyleSheet("QLabel { color : red; }");
        ui->labelMessage->setText("Failed to send message to: " + to);
    }
    clearInputs();
    refresh();
}

void DialogMessage::clearInputs()
{
    ui->leUser->clear();
    ui->leSubject->clear();
    ui->teMessage->clear();
}

void DialogMessage::refresh()
{
    setUpUserSentMessages();
    setUpUserReceivedMessages();
}
