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

void SystemWindowProfessor::setUpSectionsComboBox()
{
    departmentSections = APIService::getInstance()->getDepartmentSections();

    ui->cbCoursesList->clear();

    for(int i = 0; i < departmentSections.size(); i++)
    {
        ui->cbCoursesList->addItem(departmentSections[i].getCode());
    }
}

void SystemWindowProfessor::on_cbCoursesList_currentIndexChanged(int index)
{
    Course course = departmentSections[index];

    ui->tableSections->setRowCount(0);
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

        ui->tableSections->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
             ui->tableSections->setItem(i, j, items[j]);
        }
    }
}

void SystemWindowProfessor::on_pbRefresh_clicked()
{
    refresh();
}

void SystemWindowProfessor::displaySchedule()
{
    professorSections = APIService::getInstance()->getUserSections();

    clearSchedule();

    for(int i = 0; i < professorSections.size(); i++)
    {
        std::vector<TimeSlot> timeSlots = professorSections[i].getSections()[0].getTimeSlots();

        for(int j = 0; j < timeSlots.size(); j++)
        {
            QTableWidgetItem* item = new QTableWidgetItem(professorSections[i].getName());
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
    ui->tableSchedule->clearContents();
}

void SystemWindowProfessor::setUpUserCourses()
{
    professorSections = APIService::getInstance()->getUserSections();

    ui->tableMyCourses->setRowCount(0);

    for(int i = 0; i < professorSections.size(); i++)
    {
        for(int j = 0; j < professorSections[i].getSections().size(); j++)
        {
            std::vector<QTableWidgetItem*> items;

            Section section = professorSections[i].getSections()[j];

            items.push_back(new QTableWidgetItem(professorSections[i].getCode()));
            items.push_back(new QTableWidgetItem(professorSections[i].getName()));
            items.push_back(new QTableWidgetItem(QString::number(professorSections[i].getCredits())));
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

            QSignalMapper* smConfirmSection = new QSignalMapper(this);
            QPushButton* confirmSectionButton = new QPushButton("Confirm");
            QObject::connect(confirmSectionButton, SIGNAL(clicked(bool)), smConfirmSection, SLOT(map()));
            smConfirmSection->setMapping(confirmSectionButton, course_section);
            QObject::connect(smConfirmSection, SIGNAL(mapped(QString)), this, SLOT(confirmSection(QString)));

            ui->tableMyCourses->insertRow(j);
            for(int k = 0; k < items.size(); k++)
            {
                 ui->tableMyCourses->setItem(j, k, items[k]);
            }

            ui->tableMyCourses->setCellWidget(j, items.size(), removeSectionButton);
            ui->tableMyCourses->setCellWidget(j, items.size() + 1, editSectionButton);
            ui->tableMyCourses->setCellWidget(j, items.size() + 2, confirmSectionButton);
        }
    }
}

void SystemWindowProfessor::setUpDepartmentCourses()
{
    departmentCourses = APIService::getInstance()->getUserDepartmentCourses();

    ui->tableCourses->setRowCount(0);
    for(int i = 0; i < departmentCourses.size(); i++)
    {
        std::vector<QTableWidgetItem*> items;

        Course course = departmentCourses[i];

        items.push_back(new QTableWidgetItem(course.getCode()));
        items.push_back(new QTableWidgetItem(course.getName()));
        items.push_back(new QTableWidgetItem(course.getDescription()));
        items.push_back(new QTableWidgetItem(QString::number(course.getCredits())));

        ui->tableCourses->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
            ui->tableCourses->setItem(i, j, items[j]);
        }
    }
}

void SystemWindowProfessor::refresh()
{
    setUpSectionsComboBox();

    setUpUserCourses();

    setUpDepartmentCourses();

    displaySchedule();

    if(departmentSections.size() > 0)
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

void SystemWindowProfessor::on_pbActionSection_clicked()
{
    if(!dialogSectionOpened && departmentCourses.size() != 0)
    {
        dialogSection = new DialogSection();
        QObject::connect(dialogSection, SIGNAL(finished(int)), this, SLOT(dialogSectionClosed()));
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
    QStringList list = course_section.split('_');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int crn = professorSections[courseIndex].getSections()[sectionIndex].getCrn();

    APIService::getInstance()->removeSection(crn);
    refresh();
}

void SystemWindowProfessor::editSection(QString course_section)
{
    QStringList list = course_section.split('_');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    Course course = professorSections[courseIndex];

    if(!dialogSectionOpened && professorSections.size() != 0)
    {
        dialogSection = new DialogSection(course, sectionIndex);
        QObject::connect(dialogSection, SIGNAL(finished(int)), this, SLOT(dialogSectionClosed()));
        dialogSection->show();

        dialogSectionOpened = true;
    }
}

void SystemWindowProfessor::confirmSection(QString course_section)
{
    QStringList list = course_section.split('_');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int crn = professorSections[courseIndex].getSections()[sectionIndex].getCrn();

    APIService::getInstance()->confirmSection(crn);
    refresh();
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
