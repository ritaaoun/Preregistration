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
    int numberOfCreadits = ui->sbCredits->text().toInt();
    bool needsComputers = ui->cbNeedsComputer->isChecked();
    bool needsSpeakers = ui->cbNeedsSpeakers->isChecked();
    bool needsHighEnergyParticleAccelerator = ui->cbNeedsParticleAccelerator->isChecked();

    if(courseName == "" || courseNumber == "" || courseDescription == "" || numberOfCreadits == 0)
    {
        return;
    }

    if(APIService::getInstance()->requestCourse(courseName, courseNumber, courseDescription, numberOfCreadits,
                                             needsComputers, needsSpeakers, needsHighEnergyParticleAccelerator))
    {
        ui->labelMessage->setStyleSheet("QLabel { color : green; }");
        ui->labelMessage->setText("Succesfully sent request for course: " + courseName);
    }
    else
    {
        ui->labelMessage->setStyleSheet("QLabel { color : red; }");
        ui->labelMessage->setText("Failed to send request for course: " + courseName);
    }

    clearInputs();
}

void DialogRequestCourse::clearInputs()
{
    ui->leCourseName->clear();
    ui->leCourseNumber->clear();
    ui->teCourseDescription->clear();
    ui->sbCredits->clear();
    ui->cbNeedsComputer->setChecked(false);
    ui->cbNeedsParticleAccelerator->setChecked(false);
    ui->cbNeedsSpeakers->setChecked(false);
}
