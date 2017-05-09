#ifndef SYSTEMWINDOWADMINSTRATOR_H
#define SYSTEMWINDOWADMINSTRATOR_H

#include <QMainWindow>
#include "apiservice.h"
#include <unordered_map>
#include <QDebug>
#include <QSignalMapper>
#include "userinfo.h"
#include "loginwindow.h"

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
    void on_pbAction_clicked();

    void acceptCourseRequest(int index);
    void rejectCourseRequest(int index);

    void on_pbConfirmPriviliges_clicked();

    void on_rbCreate_clicked();

    void on_rbEdit_clicked();

    void on_pbLogout_clicked();

    void on_cbUserList_currentIndexChanged(int index);

private:
    Ui::SystemWindowAdminstrator *ui;

    std::vector<CourseRequest> courseRequests;
    std::vector<UserInfo> userInfo;
    std::unordered_map<int, QString> departments;
    std::unordered_map<int, QString> terms;


    void setUpAdminCourseRequests();
    void setUpDepartments();
    void setUpUserInfo();
    void setUpAdminUsers();

    void setCreateUserMode();
    void setEditUserMode();

    void refresh();

    void clearUserInputs();
    void setUserInputs(UserInfo user);
};

#endif // SYSTEMWINDOWADMINSTRATOR_H
