#include "systemwindowadminstrator.h"
#include "ui_systemwindowadminstrator.h"

SystemWindowAdminstrator::SystemWindowAdminstrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowAdminstrator)
{
    ui->setupUi(this);

    dialogMessageOpened = false;
    dialogChangePasswordOpened = false;

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

    if(ui->rbProfessor->isChecked())
    {
        userType = QString("1");
    }
    else if(ui->rbStudent->isChecked())
    {
        userType = QString("0");
    }
    else if(ui->rbAdministrator->isChecked())
    {
        userType = QString("2");
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
        APIService::getInstance()->createUser(userInfo);

        clearUserInputs();
    }
    else
    {
        userInfo.push_back(ui->cbUserList->currentText());
        APIService::getInstance()->editUser(userInfo);
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
        items.push_back(new QTableWidgetItem(courseRequests[i].getCredits()));

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

    APIService::getInstance()->decideOnCourse(course, true);
    setUpAdminCourseRequests();
}

void SystemWindowAdminstrator::rejectCourseRequest(int index)
{
    Course course = courseRequests[index];

    APIService::getInstance()->decideOnCourse(course, false);
    setUpAdminCourseRequests();
}

void SystemWindowAdminstrator::on_pbConfirmPriviliges_clicked()
{
    QString adminUsername = ui->leAdminUsername->text();
    int adminDepartment = ui->cbDepartmentAdmin->currentData().toInt();

    if(adminUsername.isEmpty())
        return;

    APIService::getInstance()->sendPrivileges(adminUsername, adminDepartment);

    ui->leAdminUsername->clear();
}

void SystemWindowAdminstrator::setUpDepartments()
{
    departments = APIService::getInstance()->getDepartments();

    for(std::unordered_map<int, QString>::iterator it = departments.begin(); it != departments.end(); ++it)
    {
        ui->cbDepartmentAdmin->addItem(it->second, QVariant(it->first));
        ui->cbDepartmentUser->addItem(it->second, QVariant(it->first));

        ui->label_departments->setText(ui->label_departments->text() + it->second + " ");
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
        setOtherChoiceDepartment();
    }
}

void SystemWindowAdminstrator::on_rbEdit_clicked()
{
    clearUserInputs();
    setEditUserMode();
    setOtherChoiceDepartment();

    if(!userInfo.empty())
    {
        setUserInputs(userInfo[ui->cbUserList->currentIndex()]);
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

    for(int i = 0; i < userInfo.size(); i++)
    {
        ui->cbUserList->addItem(userInfo[i].getUsername());
    }
}

void SystemWindowAdminstrator::on_cbUserList_currentIndexChanged(int index)
{
    UserInfo user = userInfo[index];

    setUserInputs(user);
}

void SystemWindowAdminstrator::setUserInputs(UserInfo user)
{
    ui->leFirstName->setText(user.getFirstName());
    ui->leMiddleName->setText(user.getMiddleName());
    ui->leLastName->setText(user.getLastName());

    ui->dateEditDateOfBirth->setDate(user.getDateOfBirth());
    ui->cbStartTerm->setCurrentText(terms[user.getStartTerm()]);
    ui->cbStartYear->setCurrentText(QString::number(user.getStartYear()));
    ui->cbDepartmentUser->setCurrentText(departments[user.getDepartment()]);
}

void SystemWindowAdminstrator::refresh()
{
    setCreateUserMode();

    setUpDepartments();
    setUpAdminCourseRequests();
    setUpAdminUsers();
}

void SystemWindowAdminstrator::on_pushButton_clicked()
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
    qDebug() << dialogChangePasswordOpened;
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

    APIService::getInstance()->resetPassword(userUsername);
}

void SystemWindowAdminstrator::on_rbAdministrator_clicked()
{
    setAdminChoiceDepartment();
}

void SystemWindowAdminstrator::on_rbProfessor_clicked()
{
    setOtherChoiceDepartment();
}

void SystemWindowAdminstrator::on_rbStudent_clicked()
{
    setOtherChoiceDepartment();
}

void SystemWindowAdminstrator::setAdminChoiceDepartment()
{
    ui->cbDepartmentUser->setCurrentText(departments[0]);
   // ui->cbDepartmentUser->showPopup();
}

void SystemWindowAdminstrator::setOtherChoiceDepartment()
{
   // ui->cbDepartmentUser->hidePopup();
}
