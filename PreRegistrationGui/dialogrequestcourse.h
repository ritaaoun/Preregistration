#ifndef DIALOGREQUESTCOURSE_H
#define DIALOGREQUESTCOURSE_H

#include <QDialog>
#include "apiservice.h"

namespace Ui {
class DialogRequestCourse;
}

class DialogRequestCourse : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRequestCourse(QWidget *parent = 0);
    ~DialogRequestCourse();

private slots:
    void on_pbSendRequest_clicked();

private:
    Ui::DialogRequestCourse *ui;
};

#endif // DIALOGREQUESTCOURSE_H
