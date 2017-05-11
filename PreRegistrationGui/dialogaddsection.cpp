#include "dialogaddsection.h"
#include "ui_dialogaddsection.h"

DialogAddSection::DialogAddSection(bool fromAddSection, std::vector<Course> professorCourses, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddSection)
{
    ui->setupUi(this);
    this->fromAddSection = fromAddSection;
    this->professorCourses = professorCourses;
    //count = 0;

    for(int i = 0; i < professorCourses.size(); i++)
    {
        ui->cbCourseCode->addItem(professorCourses[i].getCode(), QVariant(professorCourses[i].getId()));
    }
    ui->cbSectionNumber->setEnabled(false);

    //From addSection
    if(fromAddSection)
    {
        ui->label_title->setText("Add Section");
        ui->pbAddSection->setText("Add Section");
        ui->cbSectionNumber->setVisible(false);
    }


    // From editSection
    else
    {
        ui->label_title->setText("Edit Section");
        ui->pbAddSection->setText("Edit Section");
        ui->cbSectionNumber->setVisible(true);
    }

}

DialogAddSection::~DialogAddSection()
{
    delete ui;
}

void DialogAddSection::on_pdAddTimeSLot_clicked()
{
    int row = comboBoxes.size();

    ui->tableTimeSlots->insertRow(row);

    QComboBox* cb = new QComboBox();
    cb->addItem("M", QVariant(1));
    cb->addItem("T", QVariant(2));
    cb->addItem("W", QVariant(3));
    cb->addItem("R", QVariant(4));
    cb->addItem("F", QVariant(5));

    comboBoxes.push_back(cb);
    ui->tableTimeSlots->setCellWidget(row, 0, cb);

    QLineEdit* leStartHour = new QLineEdit();
    ui->tableTimeSlots->setCellWidget(row, 1, leStartHour);
    startHour.push_back(leStartHour);

    QLineEdit* leStartMinutes = new QLineEdit();
    ui->tableTimeSlots->setCellWidget(row, 2, leStartMinutes);
    startMinutes.push_back(leStartMinutes);

    QLineEdit* leEndHour = new QLineEdit();
    ui->tableTimeSlots->setCellWidget(row, 3, leEndHour);
    endHour.push_back(leEndHour);

    QLineEdit* leEndMinutes = new QLineEdit();
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

void DialogAddSection::on_pbRemoveTimeSlots_clicked()
{
    resetTable();
}

void DialogAddSection::resetTable()
{
    comboBoxes.clear();
    startHour.clear();
    startMinutes.clear();
    endHour.clear();
    endMinutes.clear();
    ui->tableTimeSlots->setRowCount(0);
}

void DialogAddSection::on_pbAddSection_clicked()
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

void DialogAddSection::on_cbCourseCode_activated(const QString & text)
{
    if(!fromAddSection)
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
            ui->cbSectionNumber->setEnabled(true);
        }
        else
            ui->cbSectionNumber->setEnabled(false);
    }
}

void DialogAddSection::addSection()
{
    if(comboBoxes.size() == 0 || std::stoi(ui->sbCapacity->text()) == 0)
    {
        return;
    }

    std::vector<TimeSlot> timeSlots;
    for(int i = 0; i < comboBoxes.size(); i++)
    {
        int dayCode = comboBoxes[i]->currentData().toInt();
        int startH = std::stoi(startHour[i]->text());
        int startM = std::stoi(startMinutes[i]->text());
        int endH = std::stoi(endHour[i]->text());
        int endM = std::stoi(endMinutes[i]->text());

        TimeSlot timeSlot(dayCode, startH, startM, endH, endM);
        timeSlots.push_back(timeSlot);
    }

    int courseId = ui->cbCourseCode->currentData().toInt();

    int capacity = std::stoi(ui->sbCapacity->text());

    APIService::getInstance()->addSection(courseId, capacity, timeSlots);
    this->close();
}

void DialogAddSection::editSection()
{
    int courseId = ui->cbCourseCode->currentData().toInt();
    int sectionNumber = ui->cbSectionNumber->currentData().toInt();
    // TODO: see how we can check if combobox not selected
    if(comboBoxes.size() == 0 || std::stoi(ui->sbCapacity->text()) == 0)
    {
        return;
    }

    std::vector<TimeSlot> timeSlots;
    for(int i = 0; i < comboBoxes.size(); i++)
    {
        int dayCode = comboBoxes[i]->currentData().toInt();
        int startH = std::stoi(startHour[i]->text());
        int startM = std::stoi(startMinutes[i]->text());
        int endH = std::stoi(endHour[i]->text());
        int endM = std::stoi(endMinutes[i]->text());

        TimeSlot timeSlot(dayCode, startH, startM, endH, endM);
        timeSlots.push_back(timeSlot);
    }

    int capacity = std::stoi(ui->sbCapacity->text());

    APIService::getInstance()->editSection(courseId, sectionNumber, capacity, timeSlots);
    this->close();
}
