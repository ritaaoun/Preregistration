#ifndef SYSTEMWINDOWPROFESSOR_H
#define SYSTEMWINDOWPROFESSOR_H

#include <QMainWindow>
#include <QTableWidget>
#include "apiservice.h"
#include "dialogaddsection.h"
#include "dialogremovesection.h"
#include "dialogrequestcourse.h"
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

    void dialogAddEditSectionClosed();
    void dialogRemoveSectionClosed();
    void dialogRequestCourseClosed();


    void on_pushButton_clicked();

    void on_pbEditSection_clicked();

    void on_pbRemoveSection_clicked();

private:
    Ui::SystemWindowProfessor *ui;

    QDialog* dialogAddEditSection;
    QDialog* dialogRemoveSection;
    QDialog* dialogRequestCourse;
    bool dialogAddEditSectionOpened;
    bool dialogRemoveSectionOpened;
    bool dialogRequestCourseOpened;

    std::vector<Course> professorCourses;
    std::vector<Course> departmentCourses;
};

#endif // SYSTEMWINDOWPROFESSOR_H
