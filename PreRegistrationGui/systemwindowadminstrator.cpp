#include "systemwindowadminstrator.h"
#include "ui_systemwindowadminstrator.h"

SystemWindowAdminstrator::SystemWindowAdminstrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowAdminstrator)
{
    ui->setupUi(this);

    dialogMessageOpened = false;
    dialogChangePasswordOpened = false;

    hasAdministratorPriviliges = false;

    ui->label_welcome->setText("Welcome Admin " + User::getUser()->getName());

    ui->tableCourseRequests->setColumnWidth(3, 60);
    ui->tableCourseRequests->setColumnWidth(4, 60);

    int currentYear = QDate::currentDate().year();

    for(int i = 0; i < 10; i++)
    {
        ui->cbStartYear->addItem(QString::number(currentYear - i));
    }

    terms[0] = "Fall";
    terms[1] = "Winter";
    terms[2] = "Spring";
    terms[3] = "Summer";

    ui->cbStartTerm->addItem(terms[0], QVariant(0));
    ui->cbStartTerm->addItem(terms[1], QVariant(1));
    ui->cbStartTerm->addItem(terms[2], QVariant(2));
    ui->cbStartTerm->addItem(terms[3], QVariant(3));

    ui->rbCreate->setChecked(true);
    ui->rbEdit->setChecked(false);

    refresh();
    clearUserInputs();
}

SystemWindowAdminstrator::~SystemWindowAdminstrator()
{
    delete ui;
}

void SystemWindowAdminstrator::on_pbAction_clicked()
{
    QString firstName = ui->leFirstName->text();
    QString lastName = ui->leLastName->text();
    QString middleName = ui->leMiddleName->text();
    QString department = QString::number(ui->cbDepartmentUser->currentData().toInt());
    QString dateOfBirth = ui->dateEditDateOfBirth->text();
    QString startTerm = QString::number(ui->cbStartTerm->currentData().toInt());
    QString startYear = ui->cbStartYear->currentText();

    QString userType;
    QString userTypeString;
    if(ui->rbProfessor->isChecked())
    {
        userType = QString("1");
        userTypeString = "Professor";
    }
    else if(ui->rbStudent->isChecked())
    {
        userType = QString("0");
        userTypeString = "Student";
    }
    else if(ui->rbAdministrator->isChecked())
    {
        userType = QString("2");
        userTypeString = "Administrator";
    }

    if(firstName.isEmpty() || lastName.isEmpty()
            || department.isEmpty() || dateOfBirth.isEmpty()
            || middleName.isEmpty()
            || startTerm.isEmpty() || startYear.isEmpty())
    {
        return;
    }

    std::vector<QString> userInfo;
    userInfo.push_back(firstName);
    userInfo.push_back(middleName);
    userInfo.push_back(lastName);
    userInfo.push_back(department);
    userInfo.push_back(dateOfBirth);
    userInfo.push_back(startYear);
    userInfo.push_back(startTerm);

    if(ui->rbCreate->isChecked())
    {
        userInfo.push_back(userType);
        if(APIService::getInstance()->createUser(userInfo))
        {
            log("Succesfuly created " + userTypeString + ": " + userInfo[0] + " " + userInfo[1] + userInfo[2]);
            clearUserInputs();
            refresh();
        }
        else
        {
            logError("Failed to create " + userTypeString);
        }
    }
    else
    {
        userInfo.push_back(ui->cbUserList->currentText());
        if(APIService::getInstance()->editUser(userInfo))
        {
            log("Succesfuly edited: " + userInfo[0] + " " + userInfo[1] + userInfo[2]);
        }
        else
        {
            logError("Failed to edit user");
        }
        refresh();
    }
}

void SystemWindowAdminstrator::setUpAdminCourseRequests()
{
     courseRequests = APIService::getInstance()->getCourseRequests();

     ui->tableCourseRequests->setRowCount(0);

     for(int i = 0; i < courseRequests.size(); i++)
     {
        std::vector<QTableWidgetItem*> items;

        items.push_back(new QTableWidgetItem(courseRequests[i].getCode()));
        items.push_back(new QTableWidgetItem(courseRequests[i].getName()));
        items.push_back(new QTableWidgetItem(QString::number(courseRequests[i].getCredits())));

        ui->tableCourseRequests->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
            ui->tableCourseRequests->setItem(i, j, items[j]);
        }

        QSignalMapper* signalMapperAccept = new QSignalMapper(this);

        QPushButton* buttonAccept = new QPushButton("Accept");
        QObject::connect(buttonAccept, SIGNAL(clicked(bool)), signalMapperAccept, SLOT(map()));
        signalMapperAccept->setMapping(buttonAccept, i);
        QObject::connect(signalMapperAccept, SIGNAL(mapped(int)), this, SLOT(acceptCourseRequest(int)));

        QSignalMapper* signalMapperReject = new QSignalMapper(this);

        QPushButton* buttonReject = new QPushButton("Reject");
        QObject::connect(buttonReject, SIGNAL(clicked(bool)), signalMapperReject, SLOT(map()));
        signalMapperReject->setMapping(buttonReject, i);
        QObject::connect(signalMapperReject, SIGNAL(mapped(int)), this, SLOT(rejectCourseRequest(int)));

        ui->tableCourseRequests->setCellWidget(i, items.size(), buttonAccept);
        ui->tableCourseRequests->setCellWidget(i, items.size() + 1, buttonReject);
     }
}

void SystemWindowAdminstrator::acceptCourseRequest(int index)
{
    Course course = courseRequests[index];

    if(APIService::getInstance()->decideOnCourse(course, true))
    {
        log("Succesfully accepted course: " + course.getCode());
    }
    else
    {
        logError("Failed to accept course: " + course.getCode());
    }
    refresh();
}

void SystemWindowAdminstrator::rejectCourseRequest(int index)
{
    Course course = courseRequests[index];

    if(APIService::getInstance()->decideOnCourse(course, false))
    {
        log("Succesfully rejected course: " + course.getCode());
    }
    else
    {
        logError("Failed to reject course: " + course.getCode());
    }
    refresh();
}

void SystemWindowAdminstrator::on_pbConfirmPriviliges_clicked()
{
    QString adminUsername = ui->leAdminUsername->text();

    int adminDepartment = ui->cbDepartmentAdmin->currentData().toInt();

    if(adminUsername.isEmpty())
    {
        logError("Please enter a username for the privilges");
        return;
    }
    if(APIService::getInstance()->sendPrivileges(adminUsername, adminDepartment))
    {
        log("Succesfuly granted privileges on " + ui->cbDepartmentAdmin->currentText() + " for "  + adminUsername);
    }
    else
    {
        logError("Failed to grant privileges to " + adminUsername);
    }

    ui->leAdminUsername->clear();
    refresh();
}

void SystemWindowAdminstrator::setUpDepartments()
{
    departments = APIService::getInstance()->getDepartments();

    for(std::unordered_map<int, QString>::iterator it = departments.begin(); it != departments.end(); ++it)
    {
        if(it->second == "Administrator")
        {
            ui->rbAdministrator->setEnabled(true);
            hasAdministratorPriviliges = true;
        }

        ui->cbDepartmentAdmin->addItem(it->second, QVariant(it->first));
        ui->cbDepartmentUser->addItem(it->second, QVariant(it->first));

        ui->label_departments->setText(ui->label_departments->text() + it->second + " ");
    }

    if(!hasAdministratorPriviliges)
    {
        ui->rbAdministrator->setEnabled(false);
    }
}

void SystemWindowAdminstrator::setEditUserMode()
{
    ui->userListWidget->show();
    ui->userTypesWidget->hide();

    ui->pbAction->setText("Edit");
    ui->labelUserAction->setText("Edit User");

    ui->pbResetPassword->show();
}

void SystemWindowAdminstrator::setCreateUserMode()
{
    ui->userListWidget->hide();
    ui->userTypesWidget->show();

    ui->pbAction->setText("Create");
    ui->labelUserAction->setText("Create User");

    ui->pbResetPassword->hide();
}

void SystemWindowAdminstrator::on_rbCreate_clicked()
{
    clearUserInputs();
    setCreateUserMode();

    if(ui->rbAdministrator->isChecked())
    {
        setAdminChoiceDepartment();
    }
    else
    {
        if(hasAdministratorPriviliges)
        {
            setOtherChoiceDepartment();
        }
    }
}

void SystemWindowAdminstrator::on_rbEdit_clicked()
{
    clearUserInputs();
    setEditUserMode();

    if(!userInfo.empty())
    {
        setUserInputs(userInfo[ui->cbUserList->currentIndex()], ui->cbUserList->currentIndex());
    }
}

void SystemWindowAdminstrator::clearUserInputs()
{
    ui->leFirstName->clear();
    ui->leLastName->clear();
    ui->leMiddleName->clear();

    ui->cbDepartmentUser->setCurrentIndex(0);
    ui->cbStartTerm->setCurrentIndex(0);
    ui->cbStartYear->setCurrentIndex(0);

    QDate defaultDate(1,1,2000);
    ui->dateEditDateOfBirth->setDate(defaultDate);

    ui->rbAdministrator->setChecked(false);
    ui->rbProfessor->setChecked(false);
    ui->rbStudent->setChecked(false);
}

void SystemWindowAdminstrator::on_pbLogout_clicked()
{
    User::removeUser();

    LogInWindow* login = new LogInWindow();
    login->show();

    if(dialogMessageOpened)
    {
        dialogMessage->close();
    }

    if(dialogChangePasswordOpened)
    {
        dialogChangePassword->close();
    }

    this->close();
}

void SystemWindowAdminstrator::setUpAdminUsers()
{
    userInfo = APIService::getInstance()->getAdminUsersInfo();

    QObject::disconnect(ui->cbDepartmentUser, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cbUserList_currentIndexChanged(int)));
    ui->cbDepartmentUser->clear();

    for(int i = 0; i < userInfo.size(); i++)
    {
        ui->cbUserList->addItem(userInfo[i].getUsername());
    }
}

void SystemWindowAdminstrator::on_cbUserList_currentIndexChanged(int index)
{
    UserInfo user = userInfo[index];

    setUserInputs(user, index);
}

void SystemWindowAdminstrator::setUserInputs(UserInfo user, int index)
{
    ui->leFirstName->setText(user.getFirstName());
    ui->leMiddleName->setText(user.getMiddleName());
    ui->leLastName->setText(user.getLastName());

    ui->dateEditDateOfBirth->setDate(user.getDateOfBirth());
    ui->cbStartTerm->setCurrentText(terms[user.getStartTerm()]);
    ui->cbStartYear->setCurrentText(QString::number(user.getStartYear()));

    if(user.getUserType() != 2)
    {
        ui->cbDepartmentUser->setCurrentText(departments[index]);
        if(hasAdministratorPriviliges)
        {
             setOtherChoiceDepartment();
        }
    }
    else
    {
        if(hasAdministratorPriviliges)
        {
            setAdminChoiceDepartment();
        }
    }

}

void SystemWindowAdminstrator::refresh()
{
    setCreateUserMode();
    setUpDepartments();
    setUpAdminCourseRequests();
    setUpAdminUsers();
}

void SystemWindowAdminstrator::on_pbMessage_clicked()
{
    if(!dialogMessageOpened)
    {
        dialogMessage = new DialogMessage();

        QObject::connect(dialogMessage, SIGNAL(finished(int)), this, SLOT(dialogMessageClosed()));
        dialogMessage->show();

        dialogMessageOpened = true;
    }
}
void SystemWindowAdminstrator::dialogMessageClosed()
{
    delete dialogMessage;
    dialogMessageOpened = false;
}

void SystemWindowAdminstrator::on_pbChangePassword_clicked()
{
    if(!dialogChangePasswordOpened)
    {
        dialogChangePassword = new DialogChangePassword();

        QObject::connect(dialogChangePassword, SIGNAL(finished(int)), this, SLOT(dialogChangePaswordClosed()));
        dialogChangePassword->show();

        dialogChangePasswordOpened = true;
    }
}

void SystemWindowAdminstrator::dialogChangePaswordClosed()
{
    delete dialogChangePassword;
    dialogChangePasswordOpened = false;
}

void SystemWindowAdminstrator::on_pbResetPassword_clicked()
{
    QString userUsername = ui->cbUserList->currentText();

    if(APIService::getInstance()->resetPassword(userUsername))
    {
        log("Succesfuly reset password for "  + userUsername);
    }
    else
    {
        logError("Failed to reset password for " + userUsername);
    }
}

void SystemWindowAdminstrator::on_rbAdministrator_clicked()
{
    setAdminChoiceDepartment();
}

void SystemWindowAdminstrator::on_rbProfessor_clicked()
{
    if(hasAdministratorPriviliges)
    {
        setOtherChoiceDepartment();
    }
}

void SystemWindowAdminstrator::on_rbStudent_clicked()
{
    if(hasAdministratorPriviliges)
    {
        setOtherChoiceDepartment();
    }
}

void SystemWindowAdminstrator::setAdminChoiceDepartment()
{
    QModelIndex index = ui->cbDepartmentUser->model()->index(0, 0);
    QVariant v(1|32);
    ui->cbDepartmentUser->model()->setData(index, v, Qt::UserRole - 1);

    ui->cbDepartmentUser->setCurrentIndex(0);
    ui->cbDepartmentUser->setEnabled(false);
}

void SystemWindowAdminstrator::setOtherChoiceDepartment()
{
    ui->cbDepartmentUser->setEnabled(true);
    QModelIndex index = ui->cbDepartmentUser->model()->index(0, 0);
    QVariant v(0);
    ui->cbDepartmentUser->model()->setData(index, v, Qt::UserRole - 1);

    if(ui->cbDepartmentUser->count()  > 2)
    {
        ui->cbDepartmentUser->setCurrentIndex(1);
    }
}

void SystemWindowAdminstrator::logError(QString message)
{
    QString content = ui->tbLog->toHtml()
            + "<font color=\"red\">"
            + message + "\n"
            + "</font>";

    ui->tbLog->setHtml(content);
    QTextCursor cursor = ui->tbLog->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->tbLog->setTextCursor(cursor);

}

void SystemWindowAdminstrator::log(QString message)
{
    QString content = ui->tbLog->toHtml()
            + "<font color=\"green\">"
            + message + "\n"
            + "</font>";

    ui->tbLog->setHtml(content);
    QTextCursor cursor = ui->tbLog->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->tbLog->setTextCursor(cursor);
}
