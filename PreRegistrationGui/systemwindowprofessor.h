#ifndef SYSTEMWINDOWPROFESSOR_H
#define SYSTEMWINDOWPROFESSOR_H

#include <QMainWindow>
#include <QTableWidget>
#include "apiservice.h"
#include "dialogaddsection.h"
#include <QDebug>

namespace Ui {
class SystemWindowProfessor;
}

class SystemWindowProfessor : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemWindowProfessor(QWidget *parent = 0);
    ~SystemWindowProfessor();

private:
    std::vector<Course> courses;
    std::vector<Course> userCourses;

    void setUpCoursesComboBox();
    void displaySchedule();
    void clearSchedule();
    void setUpUserCourses();

    void refresh();

private slots:
    void on_pbRefresh_clicked();

    void on_cbCoursesList_currentIndexChanged(int index);

    void removeCourse(int index);

    void on_pbRequestCourse_clicked();

    void on_pbAddSection_clicked();

    void dialogAddSectionClosed();

private:
    Ui::SystemWindowProfessor *ui;

    QDialog* dialogAddSection;
    bool dialogAddSectionOpened;

    std::vector<Course> professorCourses;
    std::vector<Course> departmentCourses;
};

#endif // SYSTEMWINDOWPROFESSOR_H
