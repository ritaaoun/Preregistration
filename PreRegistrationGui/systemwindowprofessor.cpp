#include "systemwindowprofessor.h"
#include "ui_systemwindowprofessor.h"
#include <QDebug>

SystemWindowProfessor::SystemWindowProfessor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowProfessor)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome " + User::getUser()->getName());

    dialogSectionOpened = false;
    dialogMessageOpened = false;
    dialogRequestCourseOpened = false;
    dialogChangePasswordOpened = false;

    refresh();
}

SystemWindowProfessor::~SystemWindowProfessor()
{
    delete ui;
}

void SystemWindowProfessor::setUpCoursesComboBox()
{
    departmentCourses = APIService::getInstance()->getDepartmentCourses();

    for(int i = 0; i < departmentCourses.size(); i++)
    {
        ui->cbCoursesList->addItem(departmentCourses[i].getName());
    }
}

void SystemWindowProfessor::on_cbCoursesList_currentIndexChanged(int index)
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

        ui->tableCourses->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
             ui->tableCourses->setItem(i, j, items[j]);
        }
    }
}

void SystemWindowProfessor::on_pbRefresh_clicked()
{
    refresh();
}

void SystemWindowProfessor::displaySchedule()
{
    professorCourses = APIService::getInstance()->getUserCourses();

    for(int i = 0; i < professorCourses.size(); i++)
    {
        std::vector<TimeSlot> timeSlots = professorCourses[i].getSections()[0].getTimeSlots();

        for(int j = 0; j < timeSlots.size(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(professorCourses[i].getName());
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

void SystemWindowProfessor::clearSchedule()
{
    ui->tableSchedule->setRowCount(0);
}

void SystemWindowProfessor::setUpUserCourses()
{
    professorCourses = APIService::getInstance()->getUserSetions();

    ui->tableMyCourses->setRowCount(0);

    for(int i = 0; i < professorCourses.size(); i++)
    {
        for(int j = 0; j < professorCourses[i].getSections().size(); j++)
        {
            std::vector<QTableWidgetItem*> items;

            Section section = professorCourses[i].getSections()[j];

            items.push_back(new QTableWidgetItem(professorCourses[i].getCode()));
            items.push_back(new QTableWidgetItem(professorCourses[i].getName()));
            items.push_back(new QTableWidgetItem(QString::number(professorCourses[i].getCredits())));
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

            QSignalMapper* smEditSection = new QSignalMapper(this);
            QPushButton* editSectionButton = new QPushButton("Edit");
            QObject::connect(editSectionButton, SIGNAL(clicked(bool)), smEditSection, SLOT(map()));
            smEditSection->setMapping(editSectionButton, course_section);
            QObject::connect(smEditSection, SIGNAL(mapped(QString)), this, SLOT(editSection(QString)));

            ui->tableMyCourses->insertRow(j);
            for(int k = 0; k < items.size(); k++)
            {
                 ui->tableMyCourses->setItem(j, k, items[k]);
            }

            ui->tableMyCourses->setCellWidget(j, items.size(), removeSectionButton);
            ui->tableMyCourses->setCellWidget(j, items.size() + 1, editSectionButton);
        }
    }
}

void SystemWindowProfessor::refresh()
{
    setUpCoursesComboBox();
    setUpUserCourses();
    displaySchedule();
    if(departmentCourses.size() > 0)
    {
        on_cbCoursesList_currentIndexChanged(0);
    }
}

void SystemWindowProfessor::dialogSectionClosed()
{
    dialogSectionOpened = false;
}

void SystemWindowProfessor::dialogRequestCourseClosed()
{
    dialogRequestCourseOpened = false;
}

void SystemWindowProfessor::on_pbAddSection_clicked()
{
    if(!dialogSectionOpened && professorCourses.size() != 0)
    {
        dialogSection = new DialogSection();
        QObject::connect(dialogSection, SIGNAL(finished(int)), this, SLOT(dialogAddEditSectionClosed()));
        dialogSection->show();

        dialogSectionOpened = true;
    }
}

void SystemWindowProfessor::on_pbRequestCourse_clicked()
{
    if(!dialogRequestCourseOpened)
    {
        dialogRequestCourse = new DialogRequestCourse();
        QObject::connect(dialogRequestCourse, SIGNAL(finished(int)), this, SLOT(dialogRequestCourseClosed()));
        dialogRequestCourse->show();

        dialogRequestCourseOpened = true;
    }
}

void SystemWindowProfessor::removeSection(QString course_section)
{
    QStringList list = course_section.split('-');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int courseId = professorCourses[courseIndex].getId();
    int sectionNumber = professorCourses[courseIndex].getSections()[sectionIndex].getNumber();

    APIService::getInstance()->removeSection(courseId, sectionNumber);
    setUpUserCourses();
}

void SystemWindowProfessor::editSection(QString course_section)
{
    QStringList list = course_section.split('-');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    Course course = professorCourses[courseIndex];

    if(!dialogSectionOpened && professorCourses.size() != 0)
    {
        dialogSection = new DialogSection(course, sectionIndex);
        QObject::connect(dialogSection, SIGNAL(finished(int)), this, SLOT(dialogSectionClosed()));
        dialogSection->show();

        dialogSectionOpened = true;
    }
}

void SystemWindowProfessor::on_pbMessage_clicked()
{
    if(!dialogMessageOpened)
    {
        dialogMessage = new DialogMessage();

        QObject::connect(dialogMessage, SIGNAL(finished(int)), this, SLOT(dialogMessageClosed()));
        dialogMessage->show();

        dialogMessageOpened = true;
    }
}

void SystemWindowProfessor::dialogMessageClosed()
{
    dialogMessageOpened = false;
}

void SystemWindowProfessor::on_pbLogout_clicked()
{
    User::removeUser();

    LogInWindow* login = new LogInWindow();
    login->show();

    if(dialogMessageOpened)
    {
        dialogMessage->close();
    }

    if(dialogRequestCourseOpened)
    {
        dialogRequestCourse->close();
    }

    if(dialogSectionOpened)
    {
        dialogSection->close();
    }

    if(dialogChangePasswordOpened)
    {
        dialogChangePassword->close();
    }

    this->close();
}

void SystemWindowProfessor::on_pbChangePassword_clicked()
{
    if(!dialogChangePasswordOpened)
    {
        dialogChangePassword = new DialogChangePassword();

        QObject::connect(dialogChangePassword, SIGNAL(finished(int)), this, SLOT(dialogChangePaswordClosed()));
        dialogChangePassword->show();

        dialogChangePasswordOpened = true;
    }
}

void SystemWindowProfessor::dialogChangePasswordClosed()
{
    dialogChangePasswordOpened = false;
}
