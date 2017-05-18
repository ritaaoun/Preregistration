#include "systemwindowstudent.h"
#include "ui_systemwindowstudent.h"

SystemWindowStudent::SystemWindowStudent(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemWindowStudent)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Welcome " + User::getUser()->getName());
    ui->labelId->setText(QString::number(User::getUser()->getId()));

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
    departmentSections = APIService::getInstance()->getDepartmentSections();

    QObject::disconnect(ui->cbCoursesList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cbCoursesList_currentIndexChanged(int)));
    ui->cbCoursesList->clear();

    for(int i = 0; i < departmentSections.size(); i++)
    {
        ui->cbCoursesList->addItem(departmentSections[i].getCode());
    }

    QObject::connect(ui->cbCoursesList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_cbCoursesList_currentIndexChanged(int)));

}

void SystemWindowStudent::on_cbCoursesList_currentIndexChanged(int index)
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

        QString course_section = QString::number(index) + "_" + QString::number(i);

        QSignalMapper* smAddSection = new QSignalMapper(this);
        QPushButton* addSectionButton = new QPushButton("Add");
        QObject::connect(addSectionButton, SIGNAL(clicked(bool)), smAddSection, SLOT(map()));
        smAddSection->setMapping(addSectionButton, course_section);
        QObject::connect(smAddSection, SIGNAL(mapped(QString)), this, SLOT(addSection(QString)));

        if(studentInSection(section))
        {
            addSectionButton->setEnabled(false);
        }

        ui->tableSections->insertRow(i);
        for(int j = 0; j < items.size(); j++)
        {
             ui->tableSections->setItem(i, j, items[j]);
        }

        ui->tableSections->setCellWidget(i, items.size(), addSectionButton);
    }
}

bool SystemWindowStudent::studentInSection(Section section)
{
    for(int i = 0; i < studentSections.size(); i++)
    {
        std::vector<Section> sections = studentSections[i].getSections();

        for(int j = 0; j < sections.size(); j++)
        {
            if(section.getCrn() == sections[j].getCrn())
            {
                return true;
            }
        }
    }
    return false;
}

void SystemWindowStudent::on_pbRefresh_clicked()
{
    refresh();
}

void SystemWindowStudent::displaySchedule()
{
    studentSections = APIService::getInstance()->getUserSections();

    clearSchedule();

    for(int i = 0; i < studentSections.size(); i++)
    {
        std::vector<Section> sections = studentSections[i].getSections();

        for(int j = 0; j < sections.size(); j++)
        {
            std::vector<TimeSlot> timeSlots = sections[j].getTimeSlots();

            for(int k = 0; k < timeSlots.size(); k++)
            {
                for(int l = timeSlots[k].getStartHour(); l <= timeSlots[k].getEndHour(); l++)
                {
                    QTableWidgetItem* it = ui->tableSchedule->item(l - 8, timeSlots[k].getDay());
                    QString content = "";
                    if(it)
                    {
                        content = "/" + it->text();
                    }
                    ui->tableSchedule->setItem(l - 8, timeSlots[k].getDay(), new QTableWidgetItem(studentSections[i].getCode() + "-" + QString::number(sections[j].getNumber()) + content));

                    if(it)
                    {
                        logError("Conflict with those courses: " + studentSections[i].getCode() + "-" + QString::number(sections[j].getNumber()) + content);
                        ui->tableSchedule->item(l - 8, timeSlots[k].getDay())->setBackground(Qt::yellow);
                    }
                    else
                    {
                        ui->tableSchedule->item(l - 8, timeSlots[k].getDay())->setBackground(Qt::red);
                    }
                }
            }
        }
    }
}

void SystemWindowStudent::clearSchedule()
{
    ui->tableSchedule->clearContents();
}

void SystemWindowStudent::setUpUserCourses()
{
    studentSections = APIService::getInstance()->getUserSections();

    ui->tableMyCourses->setRowCount(0);

    for(int i = 0; i < studentSections.size(); i++)
    {
        for(int j = 0; j < studentSections[i].getSections().size(); j++)
        {
            std::vector<QTableWidgetItem*> items;

            Section section = studentSections[i].getSections()[j];

            items.push_back(new QTableWidgetItem(studentSections[i].getCode()));
            items.push_back(new QTableWidgetItem(studentSections[i].getName()));
            items.push_back(new QTableWidgetItem(QString::number(studentSections[i].getCredits())));
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

void SystemWindowStudent::setUpDepartmentCourses()
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

void SystemWindowStudent::refresh()
{
    setUpCoursesComboBox();
    setUpUserCourses();
    displaySchedule();
    setUpDepartmentCourses();
    if(departmentSections.size() > 0)
    {
        on_cbCoursesList_currentIndexChanged(0);
    }
}

void SystemWindowStudent::removeSection(QString course_section)
{
    QStringList list = course_section.split('_');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int crn = studentSections[courseIndex].getSections()[sectionIndex].getCrn();

    if(APIService::getInstance()->removeSection(crn))
    {
        log("Succesfuly removed section " + QString::number(departmentSections[courseIndex].getSections()[sectionIndex].getNumber()) + " of course: " + departmentSections[courseIndex].getCode());
    }
    else
    {
        logError("Failed to remove section " + QString::number(departmentSections[courseIndex].getSections()[sectionIndex].getNumber()) + " of course: " + departmentSections[courseIndex].getCode());
    }
    refresh();
}

void SystemWindowStudent::addSection(QString course_section)
{
    QStringList list = course_section.split('_');

    int courseIndex = list.at(0).toInt();
    int sectionIndex = list.at(1).toInt();

    int crn = departmentSections[courseIndex].getSections()[sectionIndex].getCrn();

    if(APIService::getInstance()->addSection(crn))
    {
        log("Succesfuly added section " + QString::number(departmentSections[courseIndex].getSections()[sectionIndex].getNumber()) + " of course: " + departmentSections[courseIndex].getCode());
    }
    else
    {
        logError("Failed to add section " + QString::number(departmentSections[courseIndex].getSections()[sectionIndex].getNumber()) + " of course: " + departmentSections[courseIndex].getCode());
    }
    refresh();
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

        QObject::connect(dialogChangePassword, SIGNAL(finished(int)), this, SLOT(dialogChangePasswordClosed()));
        dialogChangePassword->show();

        dialogChangePasswordOpened = true;
    }
}

void SystemWindowStudent::dialogChangePasswordClosed()
{
    dialogChangePasswordOpened = false;
}

void SystemWindowStudent::logError(QString message)
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

void SystemWindowStudent::log(QString message)
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

