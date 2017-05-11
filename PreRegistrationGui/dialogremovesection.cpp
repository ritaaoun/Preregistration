#include "dialogremovesection.h"
#include "ui_dialogremovesection.h"

DialogRemoveSection::DialogRemoveSection(std::vector<Course> professorCourses, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRemoveSection)
{
    ui->setupUi(this);
    this->professorCourses = professorCourses;
    ui->cbSectionNumber->setVisible(false);
    ui->cbSectionNumber->setEnabled(false);
    for(int i = 0; i < professorCourses.size(); i++)
    {
        ui->cbCourseCode->addItem(professorCourses[i].getCode(), QVariant(professorCourses[i].getId()));
    }
}

DialogRemoveSection::~DialogRemoveSection()
{
    delete ui;
}

void DialogRemoveSection::on_cbCourseCode_activated(const QString &arg1)
{
    ui->cbSectionNumber->clear();
    Course selectedCourse;
    bool foundCourse = false;
    int courseId = ui->cbCourseCode->currentData().toInt();
    for(Course course : professorCourses)
    {
        if(course.getId() == courseId)
        {
            selectedCourse = course;
            foundCourse = true;

        }
    }
    if(foundCourse)
    {
        for(Section section : selectedCourse.getSections())
            ui->cbSectionNumber->addItem(section.getNumber());

        ui->cbSectionNumber->setVisible(true);
        ui->cbSectionNumber->setEnabled(true);
    }
    else
    {
        ui->cbSectionNumber->setEnabled(false);
        ui->cbSectionNumber->setVisible(false);

    }
}

void DialogRemoveSection::on_pbRemoveSection_clicked()
{
    int courseId = ui->cbCourseCode->currentData().toInt();
    int sectionNumber = ui->cbSectionNumber->currentData().toInt();
    //TODO: check if combox was not selected
    if()
    {
        return;
    }
    APIService::getInstance()->removeSection(courseId, sectionNumber);
    this->close();
}
