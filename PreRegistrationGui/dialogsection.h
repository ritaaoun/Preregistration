#ifndef DIALOGSECTION_H
#define DIALOGSECTION_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QSignalMapper>
#include "apiservice.h"
#include "timeslot.h"

namespace Ui {
class DialogSection;
}

class DialogSection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSection(Course course = Course(), int sectionIndex = -1, QWidget *parent = 0);
    ~DialogSection();

private slots:
    void on_pdAddTimeSLot_clicked();

    void on_pbRemoveTimeSlots_clicked();

    void on_pbAddSection_clicked();

private:
    Ui::DialogSection *ui;

    //int count;

    std::vector<QComboBox*> comboBoxes;
    std::vector<QLineEdit*> startHour;
    std::vector<QLineEdit*> startMinutes;
    std::vector<QLineEdit*> endHour;
    std::vector<QLineEdit*> endMinutes;

    bool fromAddSection;
    Course courseToEdit;
    Section sectionToEdit;

    std::vector<Course> departmentCourses;

    void addSection();
    void editSection();

    void fillSectionInfo();
    void resetTable();

};

#endif // DIALOGSECTION_H
