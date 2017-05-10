#ifndef DIALOGCHANGEPASSWORD_H
#define DIALOGCHANGEPASSWORD_H

#include <QDialog>
#include "apiservice.h"

namespace Ui {
class DialogChangePassword;
}

class DialogChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChangePassword(QWidget *parent = 0);
    ~DialogChangePassword();

private slots:
    void on_pbConfirm_clicked();

private:
    Ui::DialogChangePassword *ui;

    void clearInputs();
};

#endif // DIALOGCHANGEPASSWORD_H
