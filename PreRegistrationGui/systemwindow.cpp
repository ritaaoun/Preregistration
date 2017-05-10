#include "systemwindow.h"
#include "ui_systemwindow.h"
#include <QDebug>

SystemWindow::SystemWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindow)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome " + User::getUser()->getName());

    refresh();
}

SystemWindow::~SystemWindow()
{
    delete ui;
}

void SystemWindow::on_pbAddCourse_clicked()
{
    APIService::getInstance()->addCourse(courses[ui->cbCoursesList->currentIndex()]);
    refresh();
}


void SystemWindow::on_pbRemoveCourse_clicked()
{
    APIService::getInstance()->removeCourse(userCourses[ui->cbMyCoursesList->currentIndex()]);
    refresh();
}

void SystemWindow::setUpCoursesComboBox()
{
    courses = APIService::getInstance()->getCoursesList();

    for(int i = 0; i < courses.size(); i++)
    {
        ui->cbCoursesList->addItem(courses[i].getName());
    }
}

void SystemWindow::on_cbCoursesList_currentIndexChanged(int index)
{
    Course course = courses[index];

    ui->tableCourses->setRowCount(0);
    ui->cbSectionsList->clear();

    for(int i = 0; i < course.getSections().size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        Section section = course.getSections()[i];

        ui->cbSectionsList->addItem(QString::number(section.getNumber()));

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

void SystemWindow::on_pbRefresh_clicked()
{
    refresh();
}

void SystemWindow::displaySchedule()
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

void SystemWindow::clearSchedule()
{
    ui->tableSchedule->setRowCount(0);
}

void SystemWindow::setUpUserCourses()
{
    userCourses = APIService::getInstance()->getUserCourses();

    ui->tableMyCourses->setRowCount(0);
    ui->cbMyCoursesList->clear();

    for(int i = 0; i < courses.size(); i++)
    {
        for(int j = 0; j < courses[i].getSections().size(); j++)
        {
            std::vector<QTableWidgetItem*> items;

            Section section = courses[i].getSections()[j];
            ui->cbMyCoursesList->addItem(courses[i].getName() + " " + QString::number(section.getNumber()));

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

void SystemWindow::refresh()
{
    setUpCoursesComboBox();
    setUpUserCourses();
    displaySchedule();
}

void SystemWindow::removeCourse(int index)
{

}



