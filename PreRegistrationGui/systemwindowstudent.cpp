#include "systemwindowstudent.h"
#include "ui_systemwindowstudent.h"

SystemWindowStudent::SystemWindowStudent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowStudent)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome " + User::getUser()->getName());

    dialogMessageOpened = false;
    dialogChangePasswordOpened = false;

    refresh();
}

SystemWindowStudent::~SystemWindowStudent()
{
    delete ui;
}

void SystemWindowStudent::setUpCoursesComboBox()
{
    departmentCourses = APIService::getInstance()->getDepartmentCourses();

    for(int i = 0; i < departmentCourses.size(); i++)
    {
        ui->cbCoursesList->addItem(departmentCourses[i].getName());
    }
}

void SystemWindowStudent::on_cbCoursesList_currentIndexChanged(int index)
{
    Course course = departmentCourses[index];

    ui->tableCourses->setRowCount(0);
    ui->labelCourseName->setText(course.getName());

    for(int i = 0; i < course.getSections().size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        Section section = course.getSections()[i];

        items.push_back(new QTableWidgetItem(QString::number(section.getNumber())));
        items.push_back(new QTableWidgetItem(section.getProfessorName()));
        items.push_back(new QTableWidgetItem(section.getRoom()));

        QString days, time;

        for(int j = 0; j < section.getTimeSlots().size(); j++)
        {
            days += section.getTimeSlots()[j].getDayString();
            time = section.getTimeSlots()[j].getTimeString();
        }

        items.push_back(new QTableWidgetItem(days));
        items.push_back(new QTableWidgetItem(time));

        items.push_back(new QTableWidgetItem(QString::number(section.getCapacity())));
        items.push_back(new QTableWidgetItem(QString::number(section.getStudentCount())));

        QString course_section = QString::number(index) + "_" + QString::number(i);

        QSignalMapper* smAddSection = new QSignalMapper(this);
        QPushButton* addSectionButton = new QPushButton("Add");
        QObject::connect(addSectionButton, SIGNAL(clicked(bool)), smAddSection, SLOT(map()));
        smAddSection->setMapping(addSectionButton, course_section);
        QObject::connect(smAddSection, SIGNAL(mapped(QString)), this, SLOT(addSection(QString)));

        ui->tableCourses->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
             ui->tableCourses->setItem(i, j, items[j]);
        }

        ui->tableCourses->setCellWidget(i, items.size(), addSectionButton);
    }
}

void SystemWindowStudent::on_pbRefresh_clicked()
{
    refresh();
}

void SystemWindowStudent::displaySchedule()
{
    studentCourses = APIService::getInstance()->getUserCourses();

    for(int i = 0; i < studentCourses.size(); i++)
    {
        std::vector<TimeSlot> timeSlots = studentCourses[i].getSections()[0].getTimeSlots();

        for(int j = 0; j < timeSlots.size(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(studentCourses[i].getName());
            ui->tableSchedule->setItem(timeSlots[j].getStartHour() - 8, timeSlots[j].getDay(), item);
            ui->tableSchedule->item(timeSlots[j].getStartHour() - 8, timeSlots[j].getDay())->setBackground(Qt::red);

            for(int l = timeSlots[j].getStartHour() + 1; l <= timeSlots[j].getEndHour(); l++)
            {
                ui->tableSchedule->setItem(l - 8, timeSlots[j].getDay(), new QTableWidgetItem());
                ui->tableSchedule->item(l - 8, timeSlots[j].getDay())->setBackground(Qt::red);
            }
        }
    }
}

void SystemWindowStudent::clearSchedule()
{
    ui->tableSchedule->setRowCount(0);
}

void SystemWindowStudent::setUpUserCourses()
{
    studentCourses = APIService::getInstance()->getUserSetions();

    ui->tableMyCourses->setRowCount(0);

    for(int i = 0; i < studentCourses.size(); i++)
    {
        for(int j = 0; j < studentCourses[i].getSections().size(); j++)
        {
            std::vector<QTableWidgetItem*> items;

            Section section = studentCourses[i].getSections()[j];

            items.push_back(new QTableWidgetItem(studentCourses[i].getCode()));
            items.push_back(new QTableWidgetItem(studentCourses[i].getName()));
            items.push_back(new QTableWidgetItem(QString::number(studentCourses[i].getCredits())));
            items.push_back(new QTableWidgetItem(QString::number(section.getNumber())));
            items.push_back(new QTableWidgetItem(section.getRoom()));

            QString days, time;
            for(int k = 0; k < section.getTimeSlots().size(); k++)
            {
                days += section.getTimeSlots()[k].getDayString();
                time = section.getTimeSlots()[k].getTimeString();
            }

            items.push_back(new QTableWidgetItem(days));
            items.push_back(new QTableWidgetItem(time));

            items.push_back(new QTableWidgetItem(QString::number(section.getCapacity())));
            items.push_back(new QTableWidgetItem(QString::number(section.getStudentCount())));

            QString course_section = QString::number(i) + "_" + QString::number(j);

            QSignalMapper* smRemoveSection = new QSignalMapper(this);
            QPushButton* removeSectionButton = new QPushButton("Remove");
            QObject::connect(removeSectionButton, SIGNAL(clicked(bool)), smRemoveSection, SLOT(map()));
            smRemoveSection->setMapping(removeSectionButton, course_section);
            QObject::connect(smRemoveSection, SIGNAL(mapped(QString)), this, SLOT(removeSection(QString)));

            ui->tableMyCourses->insertRow(j);
            for(int k = 0; k < items.size(); k++)
            {
                 ui->tableMyCourses->setItem(j, k, items[k]);
            }

            ui->tableMyCourses->setCellWidget(j, items.size(), removeSectionButton);
        }
    }
}

void SystemWindowStudent::refresh()
{
    setUpCoursesComboBox();
    setUpUserCourses();
    displaySchedule();
    if(departmentCourses.size() > 0)
    {
        on_cbCoursesList_currentIndexChanged(0);
    }
}

void SystemWindowStudent::removeSection(QString course_section)
{
    QStringList list = course_section.split('-');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int courseId = studentCourses[courseIndex].getId();
    int sectionNumber = studentCourses[courseIndex].getSections()[sectionIndex].getNumber();

    APIService::getInstance()->removeSection(courseId, sectionNumber);
    setUpUserCourses();
}

void SystemWindowStudent::addSection(QString course_section)
{
    QStringList list = course_section.split('-');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int courseId = studentCourses[courseIndex].getId();
    int sectionNumber = studentCourses[courseIndex].getSections()[sectionIndex].getNumber();

    APIService::getInstance()->addSection(courseId, sectionNumber);
    setUpUserCourses();
}

void SystemWindowStudent::on_pbMessage_clicked()
{
    if(!dialogMessageOpened)
    {
        dialogMessage = new DialogMessage();

        QObject::connect(dialogMessage, SIGNAL(finished(int)), this, SLOT(dialogMessageClosed()));
        dialogMessage->show();

        dialogMessageOpened = true;
    }
}

void SystemWindowStudent::dialogMessageClosed()
{
    dialogMessageOpened = false;
}

void SystemWindowStudent::on_pbLogout_clicked()
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

void SystemWindowStudent::on_pbChangePassword_clicked()
{
    if(!dialogChangePasswordOpened)
    {
        dialogChangePassword = new DialogChangePassword();

        QObject::connect(dialogChangePassword, SIGNAL(finished(int)), this, SLOT(dialogChangePaswordClosed()));
        dialogChangePassword->show();

        dialogChangePasswordOpened = true;
    }
}

void SystemWindowStudent::dialogChangePasswordClosed()
{
    dialogChangePasswordOpened = false;
}

