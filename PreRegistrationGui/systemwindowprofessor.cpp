#include "systemwindowprofessor.h"
#include "ui_systemwindowprofessor.h"
#include <QDebug>

SystemWindowProfessor::SystemWindowProfessor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowProfessor)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome " + User::getUser()->getName());

    dialogAddSectionOpened = false;

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

void SystemWindowProfessor::removeCourse(int index)
{

}

void SystemWindowProfessor::on_pbRequestCourse_clicked()
{

}

void SystemWindowProfessor::on_pbAddSection_clicked()
{
    if(!dialogAddSectionOpened && professorCourses.size() != 0)
    {
        dialogAddSection = new DialogAddSection(professorCourses);
        QObject::connect(dialogAddSection, SIGNAL(finished(int)), this, SLOT(dialogAddSectionClosed()));
        dialogAddSection->show();

        dialogAddSectionOpened = true;
    }
}

void SystemWindowProfessor::dialogAddSectionClosed()
{
    dialogAddSectionOpened = false;
}
