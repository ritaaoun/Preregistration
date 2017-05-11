#ifndef DIALOGADDSECTION_H
#define DIALOGADDSECTION_H

#include <QDialog>
#include <QComboBox>
#include <QSignalMapper>
#include "apiservice.h"
#include "timeslot.h"

namespace Ui {
class DialogAddSection;
}

class DialogAddSection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddSection(std::vector<Course> professorCourses, QWidget *parent = 0);
    ~DialogAddSection();

private slots:
    void on_pdAddTimeSLot_clicked();

    void on_pbRemoveTimeSlots_clicked();

    void on_pbAddSection_clicked();

private:
    Ui::DialogAddSection *ui;

    //int count;

    std::vector<QComboBox*> comboBoxes;
    std::vector<QLineEdit*> startHour;
    std::vector<QLineEdit*> startMinutes;
    std::vector<QLineEdit*> endHour;
    std::vector<QLineEdit*> endMinutes;


    void resetTable();

};

#endif // DIALOGADDSECTION_H
