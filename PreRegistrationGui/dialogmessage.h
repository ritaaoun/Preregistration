#ifndef DIALOGMESSAGE_H
#define DIALOGMESSAGE_H

#include <QDialog>
#include "message.h"
#include "apiservice.h"

namespace Ui {
class DialogMessage;
}

class DialogMessage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogMessage(QWidget *parent = 0);
    ~DialogMessage();

private slots:
    void on_pbRefresh_clicked();

    void on_pbSend_clicked();

private:
    Ui::DialogMessage *ui;

    void setUpUserReceivedMessages();
    void setUpUserSentMessages();
    void clearInputs();
    void refresh();
};

#endif // DIALOGMESSAGE_H
