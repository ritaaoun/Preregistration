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


void DialogMessage::setUpUserMessages()
{
    std::vector<Message> messages = APIService::getInstance()->getUserMessages();

    for(int i = 0; i < messages.size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        items.push_back(new QTableWidgetItem(messages[i].getFrom()));
        items.push_back(new QTableWidgetItem(messages[i].getTo()));
        items.push_back(new QTableWidgetItem(messages[i].getSubject()));
        items.push_back(new QTableWidgetItem(messages[i].getMessage()));

        ui->tableMessages->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
            ui->tableMessages->setItem(i, j, items[j]);
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

    APIService::getInstance()->sendMessage(theMessage);
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
    setUpUserMessages();
}
