#ifndef SYSTEMWINDOWSTUDENT_H
#define SYSTEMWINDOWSTUDENT_H

#include <QMainWindow>
#include <QTableWidget>
#include "apiservice.h"
#include "loginwindow.h"

namespace Ui {
class SystemWindowStudent;
}

class SystemWindowStudent : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemWindowStudent(QWidget *parent = 0);
    ~SystemWindowStudent();

private slots:
    void on_pbRefresh_clicked();

    void on_cbCoursesList_currentIndexChanged(int index);

    void removeSection(QString course_section);
    void addSection(QString course_section);

    void dialogMessageClosed();
    void dialogChangePasswordClosed();

    void on_pbMessage_clicked();

    void on_pbLogout_clicked();

    void on_pbChangePassword_clicked();

private:
    Ui::SystemWindowStudent *ui;

    QDialog* dialogMessage;
    QDialog* dialogChangePassword;
    bool dialogMessageOpened;
    bool dialogChangePasswordOpened;

    std::vector<Course> departmentSections;
    std::vector<Course> studentSections;
    std::vector<Course> departmentCourses;

    bool studentInSection(Section section);

    void setUpCoursesComboBox();
    void displaySchedule();
    void clearSchedule();
    void setUpDepartmentCourses();
    void setUpUserCourses();

    void refresh();

    void logError(QString message);
    void log(QString message);
};

#endif // SYSTEMWINDOWSTUDENT_H
