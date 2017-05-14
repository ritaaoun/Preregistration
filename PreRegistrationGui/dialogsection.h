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
    explicit DialogSection(bool fromAddSection, std::vector<Course> professorCourses, QWidget *parent = 0);
    ~DialogSection();

private slots:
    void on_pdAddTimeSLot_clicked();

    void on_pbRemoveTimeSlots_clicked();

    void on_pbAddSection_clicked();

    void on_cbCourseCode_activated(const QString &text);

private:
    Ui::DialogSection *ui;

    //int count;

    std::vector<QComboBox*> comboBoxes;
    std::vector<QLineEdit*> startHour;
    std::vector<QLineEdit*> startMinutes;
    std::vector<QLineEdit*> endHour;
    std::vector<QLineEdit*> endMinutes;

    bool fromAddSection;
    std::vector<Course> professorCourses;

    void addSection();
    void editSection();


    void resetTable();

};

#endif // DIALOGSECTION_H
