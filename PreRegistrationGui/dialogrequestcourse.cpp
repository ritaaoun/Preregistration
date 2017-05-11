#include "dialogrequestcourse.h"
#include "ui_dialogrequestcourse.h"

DialogRequestCourse::DialogRequestCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogRequestCourse)
{
    ui->setupUi(this);
}

DialogRequestCourse::~DialogRequestCourse()
{
    delete ui;
}

void DialogRequestCourse::on_pbSendRequest_clicked()
{
    QString courseName = ui->leCourseName->text();
    QString courseNumber = ui->leCourseNumber->text();
    QString courseDescription = ui->teCourseDescription->toPlainText();
    int numberOfCreadits = std::stoi(ui->sbCapacity->text());
    bool needsComputers = ui->cbNeedsComputer->isChecked();
    bool needsSpeakers = ui->cbNeedsSpeakers->isChecked();
    bool needsHighEnergyParticleAccelerator = ui->cbNeedsParticleAccelerator->isChecked();

    if(courseName == "" || courseNumber == "" || courseDescription == "" || numberOfCreadits == 0)
    {
        return;
    }

    APIService::getInstance()->requestCourse(courseName, courseNumber, courseDescription, numberOfCreadits,
                                             needsComputers, needsSpeakers, needsHighEnergyParticleAccelerator);
    this->close();
}
