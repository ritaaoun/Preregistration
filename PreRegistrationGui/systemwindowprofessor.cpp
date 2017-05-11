#include "systemwindowprofessor.h"
#include "ui_systemwindowprofessor.h"
#include <QDebug>

SystemWindowProfessor::SystemWindowProfessor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowProfessor)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome " + User::getUser()->getName());

    dialogAddEditSectionOpened = false;
    dialogRemoveSectionOpened = false;
    dialogRequestCourseOpened = false;

    professorCourses = APIService::getInstance()->getUserSetions();
    departmentCourses = APIService::getInstance()->getDepartmentCourses();

    refresh();
}

SystemWindowProfessor::~SystemWindowProfessor()
{
    delete ui;
}

void SystemWindowProfessor::setUpCoursesComboBox()
{
    courses = APIService::getInstance()->getCoursesList();

    for(int i = 0; i < courses.size(); i++)
    {
        ui->cbCoursesList->addItem(courses[i].getName());
    }
}

void SystemWindowProfessor::on_cbCoursesList_currentIndexChanged(int index)
{
    Course course = courses[index];

    ui->tableCourses->setRowCount(0);

    for(int i = 0; i < course.getSections().size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        Section section = course.getSections()[i];

        items.push_back(new QTableWidgetItem(QString::number(section.getNumber())));
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
        items.push_back(new QTableWidgetItem(QString::number(section.getActual())));

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
    std::vector<Course> userCourses = APIService::getInstance()->getUserCourses();

    for(int i = 0; i < userCourses.size(); i++)
    {
        std::vector<TimeSlot> timeSlots = userCourses[i].getSections()[0].getTimeSlots();

        for(int j = 0; j < timeSlots.size(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(userCourses[i].getName());
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
    userCourses = APIService::getInstance()->getUserCourses();

    ui->tableMyCourses->setRowCount(0);

    for(int i = 0; i < courses.size(); i++)
    {
        for(int j = 0; j < courses[i].getSections().size(); j++)
        {
            std::vector<QTableWidgetItem*> items;

            Section section = courses[i].getSections()[j];

            items.push_back(new QTableWidgetItem(courses[i].getName()));
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
            items.push_back(new QTableWidgetItem(QString::number(section.getActual())));

            QPushButton* removeButton = new QPushButton("Remove");
            QObject::connect(removeButton, SIGNAL(clicked()), this, SLOT(removeCourse(i)));

            ui->tableMyCourses->insertRow(j);
            for(int k = 0; k < items.size(); k++)
            {
                 ui->tableMyCourses->setItem(j, k, items[k]);
            }

            ui->tableMyCourses->setCellWidget(j, items.size(), removeButton);
        }
    }
}

void SystemWindowProfessor::refresh()
{
    setUpCoursesComboBox();
    setUpUserCourses();
    displaySchedule();
}

void SystemWindowProfessor::dialogAddEditSectionClosed()
{
    dialogAddEditSectionOpened = false;
}

void SystemWindowProfessor::dialogRemoveSectionClosed()
{
    dialogRemoveSectionOpened = false;
}

void SystemWindowProfessor::dialogRequestCourseClosed()
{
    dialogRequestCourseOpened = false;
}

void SystemWindowProfessor::on_pbAddSection_clicked()
{
    if(!dialogAddEditSectionOpened && professorCourses.size() != 0)
    {
        dialogAddEditSection = new DialogAddSection(true, professorCourses);
        QObject::connect(dialogAddEditSection, SIGNAL(finished(int)), this, SLOT(dialogAddEditSectionClosed()));
        dialogAddEditSection->show();

        dialogAddEditSectionOpened = true;
    }
}

void SystemWindowProfessor::on_pbEditSection_clicked()
{
    if(!dialogAddEditSectionOpened && professorCourses.size() != 0)
    {
        dialogAddEditSection = new DialogAddSection(false, professorCourses);
        QObject::connect(dialogAddEditSection, SIGNAL(finished(int)), this, SLOT(dialogAddEditSectionClosed()));
        dialogAddEditSection->show();

        dialogAddEditSectionOpened = true;
    }
}

void SystemWindowProfessor::on_pbRemoveSection_clicked()
{
    if(!dialogRemoveSectionOpened && professorCourses.size() != 0)
    {
        dialogRemoveSection = new DialogRemoveSection(professorCourses);
        QObject::connect(dialogRemoveSection, SIGNAL(finished(int)), this, SLOT(dialogRemoveSectionClosed()));
        dialogRemoveSection->show();

        dialogRemoveSectionOpened = true;
    }
}

void SystemWindowProfessor::on_pbRequestCourse_clicked()
{
    if(!dialogRequestCourseOpened)
    {
        dialogRequestCourse = new DialogRequestCourse(professorCourses);
        QObject::connect(dialogRequestCourse, SIGNAL(finished(int)), this, SLOT(dialogRequestCourseClosed());
        dialogRequestCourse->show();

        dialogRequestCourse = true;
    }
}
