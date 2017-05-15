#ifndef SYSTEMWINDOWPROFESSOR_H
#define SYSTEMWINDOWPROFESSOR_H

#include <QMainWindow>
#include <QTableWidget>
#include "apiservice.h"
#include "loginwindow.h"
#include "dialogsection.h"
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

private slots:
    void on_pbRefresh_clicked();

    void on_cbCoursesList_currentIndexChanged(int index);

    void removeSection(QString course_section);

    void editSection(QString course_section);

    void on_pbRequestCourse_clicked();

    void on_pbAddSection_clicked();

    void dialogSectionClosed();
    void dialogMessageClosed();
    void dialogRequestCourseClosed();
    void dialogChangePasswordClosed();

    void on_pbMessage_clicked();

    void on_pbLogout_clicked();

    void on_pbChangePassword_clicked();

private:
    Ui::SystemWindowProfessor *ui;

    QDialog* dialogSection;
    QDialog* dialogMessage;
    QDialog* dialogRequestCourse;
    QDialog* dialogChangePassword;
    bool dialogSectionOpened;
    bool dialogMessageOpened;
    bool dialogRequestCourseOpened;
    bool dialogChangePasswordOpened;

    std::vector<Course> professorCourses;
    std::vector<Course> departmentCourses;


    void setUpCoursesComboBox();
    void displaySchedule();
    void clearSchedule();
    void setUpUserCourses();

    void refresh();
};

#endif // SYSTEMWINDOWPROFESSOR_H
