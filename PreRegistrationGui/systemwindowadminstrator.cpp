#include "systemwindowadminstrator.h"
#include "ui_systemwindowadminstrator.h"

SystemWindowAdminstrator::SystemWindowAdminstrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowAdminstrator)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome Admin " + User::getUser()->getName());


    ui->tableCourseRequests->setColumnWidth(3, 60);
    ui->tableCourseRequests->setColumnWidth(4, 60);

    int currentYear = QDate::currentDate().year();

    for(int i = 0; i < 10; i++)
    {
        ui->cbStartYear->addItem(QString::number(currentYear - i));
    }

    ui->cbStartTerm->addItem("Fall");
    ui->cbStartTerm->addItem("Winter");
    ui->cbStartTerm->addItem("Spring");
    ui->cbStartTerm->addItem("Summer");

    setUpDepartments();
    setUpAdminCourseRequests();
}

SystemWindowAdminstrator::~SystemWindowAdminstrator()
{
    delete ui;
}

void SystemWindowAdminstrator::on_pbCreate_clicked()
{
    QString firstName = ui->leFirstName->text();
    QString lastName = ui->leLastName->text();
    QString middleName = ui->leMiddleName->text();
    QString department = QString::number(ui->cbDepartmentUser->currentData().toInt());
    QString dateOfBirth = ui->dateEditDateOfBirth->text();
    QString startTerm = QString::number(ui->cbStartTerm->currentIndex());
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
            || userType.isEmpty() || middleName.isEmpty()
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
    userInfo.push_back(userType);

    qDebug() << APIService::getInstance()->createUser(userInfo);
}

void SystemWindowAdminstrator::setUpAdminCourseRequests()
{
     courseRequests = APIService::getInstance()->getCourseRequests();

     ui->tableCourseRequests->clearContents();

     for(int i = 0; i < courseRequests.size(); i++)
     {
        std::vector<QTableWidgetItem*> items;

        items.push_back(new QTableWidgetItem(courseRequests[i].getCourseName()));
        items.push_back(new QTableWidgetItem(courseRequests[i].getDepartment()));
        items.push_back(new QTableWidgetItem(courseRequests[i].getProfessor()));

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
    qDebug() << "accept " << index;
}

void SystemWindowAdminstrator::rejectCourseRequest(int index)
{
    qDebug() << "reject " << index;
}

void SystemWindowAdminstrator::on_pbConfirmPriviliges_clicked()
{
    QString adminUsername = ui->leAdminUsername->text();
    QString adminDepartment = ui->cbDepartmentAdmin->currentText();

    if(adminUsername.isEmpty() || adminDepartment.isEmpty())
        return;

    APIService::getInstance()->sendPriviliges(adminUsername, adminDepartment);

    ui->leAdminUsername->clear();
}

void SystemWindowAdminstrator::setUpDepartments()
{
    std::unordered_map<int, QString> departments = APIService::getInstance()->getDepartments();

    for(std::unordered_map<int, QString>::iterator it = departments.begin(); it != departments.end(); ++it)
    {
        ui->cbDepartmentAdmin->addItem(it->second, QVariant(it->first));
        ui->cbDepartmentUser->addItem(it->second, QVariant(it->first));

        ui->label_departments->setText(ui->label_departments->text() + it->second + " ");
    }
}
