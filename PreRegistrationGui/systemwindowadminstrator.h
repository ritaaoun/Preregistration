#ifndef SYSTEMWINDOWADMINSTRATOR_H
#define SYSTEMWINDOWADMINSTRATOR_H

#include <QMainWindow>
#include "apiservice.h"
#include <unordered_map>
#include <QDebug>
#include <QSignalMapper>

namespace Ui {
class SystemWindowAdminstrator;
}

class SystemWindowAdminstrator : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemWindowAdminstrator(QWidget *parent = 0);
    ~SystemWindowAdminstrator();

private slots:
    void on_pbCreate_clicked();

    void acceptCourseRequest(int index);
    void rejectCourseRequest(int index);

    void on_pbConfirmPriviliges_clicked();

private:
    Ui::SystemWindowAdminstrator *ui;

    std::vector<CourseRequest> courseRequests;

    void setUpAdminCourseRequests();
    void setUpDepartments();
};

#endif // SYSTEMWINDOWADMINSTRATOR_H
