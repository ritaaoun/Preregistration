#ifndef SYSTEMWINDOWADMINSTRATOR_H
#define SYSTEMWINDOWADMINSTRATOR_H

#include <QMainWindow>
#include "apiservice.h"
#include <unordered_map>
#include <QDebug>
#include <QSignalMapper>
#include "userinfo.h"
#include "loginwindow.h"
#include "dialogmessage.h"
#include "dialogchangepassword.h"

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

    void on_pbMessage_clicked();

    void dialogMessageClosed();

    void dialogChangePaswordClosed();

    void on_pbChangePassword_clicked();

    void on_pbResetPassword_clicked();

    void on_rbAdministrator_clicked();

    void on_rbProfessor_clicked();

    void on_rbStudent_clicked();

private:
    Ui::SystemWindowAdminstrator *ui;
    QDialog* dialogMessage;
    QDialog* dialogChangePassword;
    bool dialogMessageOpened;
    bool dialogChangePasswordOpened;

    bool hasAdministratorPriviliges;

    std::vector<Course> courseRequests;
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
    void setUserInputs(UserInfo user, int index);

    void setAdminChoiceDepartment();
    void setOtherChoiceDepartment();

    void logError(QString message);
    void log(QString message);
};

#endif // SYSTEMWINDOWADMINSTRATOR_H
