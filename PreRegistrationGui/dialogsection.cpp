#include "dialogsection.h"
#include "ui_dialogsection.h"

DialogSection::DialogSection(Course course, int sectionIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSection)
{
    ui->setupUi(this);

    hourValidator = new QIntValidator(8, 21, this);
    minutesValidator = new QIntValidator(0, 59, this);

    if(sectionIndex != -1 )// From editSection
    {
        fromAddSection = false;
        courseToEdit = course;
        sectionToEdit = course.getSections()[sectionIndex];

        ui->label_title->setText("Edit Section");
        ui->pbAddSection->setText("Edit Section");
        ui->widgetCourseCode->setVisible(false);

        fillSectionInfo();
    }
    else // From addSection
    {
        fromAddSection = true;
        ui->label_title->setText("Add Section");
        ui->pbAddSection->setText("Add Section");
        ui->widgetCourseCode->setVisible(true);

        departmentCourses = APIService::getInstance()->getUserDepartmentCourses();
        for(int i = 0; i < departmentCourses.size(); i++)
        {
            ui->cbCourseCode->addItem(departmentCourses[i].getCode(), QVariant(departmentCourses[i].getId()));
        }
    }

    //count = 0;
}

DialogSection::~DialogSection()
{
    delete ui;
}

void DialogSection::on_pdAddTimeSLot_clicked()
{
    int row = comboBoxes.size();

    ui->tableTimeSlots->insertRow(row);

    QComboBox* cb = new QComboBox();
    cb->addItem("M", QVariant(0));
    cb->addItem("T", QVariant(1));
    cb->addItem("W", QVariant(2));
    cb->addItem("R", QVariant(3));
    cb->addItem("F", QVariant(4));
    cb->addItem("Sa", QVariant(5));

    comboBoxes.push_back(cb);
    ui->tableTimeSlots->setCellWidget(row, 0, cb);

    QLineEdit* leStartHour = new QLineEdit();
    leStartHour->setValidator(hourValidator);
    ui->tableTimeSlots->setCellWidget(row, 1, leStartHour);
    startHour.push_back(leStartHour);

    QLineEdit* leStartMinutes = new QLineEdit();
    leStartMinutes->setValidator(minutesValidator);
    ui->tableTimeSlots->setCellWidget(row, 2, leStartMinutes);
    startMinutes.push_back(leStartMinutes);

    QLineEdit* leEndHour = new QLineEdit();
    leEndHour->setValidator(hourValidator);
    ui->tableTimeSlots->setCellWidget(row, 3, leEndHour);
    endHour.push_back(leEndHour);

    QLineEdit* leEndMinutes = new QLineEdit();
    leEndMinutes->setValidator(minutesValidator);
    ui->tableTimeSlots->setCellWidget(row, 4, leEndMinutes);
    endMinutes.push_back(leEndMinutes);

//    QPushButton* removeTimeSlot = new QPushButton("Remove");
//    ui->tableTimeSlots->setCellWidget(row, 5, removeTimeSlot);

//    QSignalMapper* signalMapperRemove = new QSignalMapper(this);
//    QObject::connect(removeTimeSlot, SIGNAL(clicked(bool)), signalMapperRemove, SLOT(map()));
//    signalMapperRemove->setMapping(removeTimeSlot, count);
//    QObject::connect(signalMapperRemove, SIGNAL(mapped(int)), this, SLOT(removeTimeSlot(int)));

//    count++;
}

void DialogSection::on_pbRemoveTimeSlots_clicked()
{
    resetTable();
}

void DialogSection::resetTable()
{
    comboBoxes.clear();
    startHour.clear();
    startMinutes.clear();
    endHour.clear();
    endMinutes.clear();
    ui->tableTimeSlots->setRowCount(0);
}

void DialogSection::on_pbAddSection_clicked()
{
    if(fromAddSection)
    {
        addSection();
    }
    else
    {
        editSection();
    }
}

void DialogSection::addSection()
{
    if(comboBoxes.size() == 0 || ui->sbCapacity->text().toInt() == 0)
    {
        return;
    }

    std::vector<TimeSlot> timeSlots;
    for(int i = 0; i < comboBoxes.size(); i++)
    {
        Day day = static_cast<Day>(comboBoxes[i]->currentData().toInt());
        int startH = startHour[i]->text().toInt();
        int startM = startMinutes[i]->text().toInt();
        int endH = endHour[i]->text().toInt();
        int endM = endMinutes[i]->text().toInt();

        TimeSlot timeSlot(day, startH, startM, endH, endM);
        timeSlots.push_back(timeSlot);
    }

    int courseId = ui->cbCourseCode->currentData().toInt();

    int capacity = ui->sbCapacity->text().toInt();

    if(APIService::getInstance()->publishSection(courseId, capacity, timeSlots))
    {
        ui->labelMessage->setStyleSheet("QLabel { color : green; }");
        ui->labelMessage->setText("Succesfuly published a section for course: " + ui->cbCourseCode->currentText());
    }
    else
    {
        ui->labelMessage->setStyleSheet("QLabel { color : red; }");
        ui->labelMessage->setText("Failed to publish section fro course: " + courseToEdit.getCode());
    }
}

void DialogSection::editSection()
{
    int courseId = ui->cbCourseCode->currentData().toInt();

    if(comboBoxes.size() == 0 || ui->sbCapacity->text().toInt() == 0)
    {
        return;
    }

    std::vector<TimeSlot> timeSlots;
    for(int i = 0; i < comboBoxes.size(); i++)
    {
        Day day = static_cast<Day>(comboBoxes[i]->currentData().toInt());
        int startH = startHour[i]->text().toInt();
        int startM = startMinutes[i]->text().toInt();
        int endH = endHour[i]->text().toInt();
        int endM = endMinutes[i]->text().toInt();

        TimeSlot timeSlot(day, startH, startM, endH, endM);
        timeSlots.push_back(timeSlot);
    }

    int capacity = ui->sbCapacity->text().toInt();

    if(APIService::getInstance()->editSection(sectionToEdit.getCrn(), capacity, timeSlots))
    {
        ui->labelMessage->setStyleSheet("QLabel { color : green; }");
        ui->labelMessage->setText("Succesfuly edited the section: " + QString::number(sectionToEdit.getNumber()) + " of course " + courseToEdit.getCode());
    }
    else
    {
        ui->labelMessage->setStyleSheet("QLabel { color : red; }");
        ui->labelMessage->setText("Failed to edit section");
    }
}

void DialogSection::fillSectionInfo()
{
    ui->sbCapacity->setValue(sectionToEdit.getCapacity());

    resetTable();

    std::vector<TimeSlot> timeSlots = sectionToEdit.getTimeSlots();

    for(int i = 0; i < timeSlots.size(); i++)
    {
        ui->tableTimeSlots->insertRow(i);

        QComboBox* cb = new QComboBox();
        cb->addItem("M", QVariant(0));
        cb->addItem("T", QVariant(1));
        cb->addItem("W", QVariant(2));
        cb->addItem("R", QVariant(3));
        cb->addItem("F", QVariant(4));
        cb->addItem("Sa", QVariant(5));

        comboBoxes.push_back(cb);
        ui->tableTimeSlots->setCellWidget(i, 0, cb);
        cb->setCurrentText(timeSlots[i].getDayString());

        QLineEdit* leStartHour = new QLineEdit();
        leStartHour->setValidator(hourValidator);
        ui->tableTimeSlots->setCellWidget(i, 1, leStartHour);
        startHour.push_back(leStartHour);
        leStartHour->setText(QString::number(timeSlots[i].getStartHour()));

        QLineEdit* leStartMinutes = new QLineEdit();
        leStartMinutes->setValidator(minutesValidator);
        ui->tableTimeSlots->setCellWidget(i, 2, leStartMinutes);
        startMinutes.push_back(leStartMinutes);
        leStartMinutes->setText(QString::number(timeSlots[i].getStartMinutes()));

        QLineEdit* leEndHour = new QLineEdit();
        leEndHour->setValidator(hourValidator);
        ui->tableTimeSlots->setCellWidget(i, 3, leEndHour);
        endHour.push_back(leEndHour);
        leEndHour->setText(QString::number(timeSlots[i].getEndHour()));

        QLineEdit* leEndMinutes = new QLineEdit();
        leEndMinutes->setValidator(minutesValidator);
        ui->tableTimeSlots->setCellWidget(i, 4, leEndMinutes);
        endMinutes.push_back(leEndMinutes);
        leEndMinutes->setText(QString::number(timeSlots[i].getEndMinutes()));
    }
}
