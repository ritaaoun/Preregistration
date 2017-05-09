#ifndef SYSTEMWINDOW_H
#define SYSTEMWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "apiservice.h"

namespace Ui {
class SystemWindow;
}

class SystemWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemWindow(QWidget *parent = 0);
    ~SystemWindow();

private:
    std::vector<Course> courses;
    std::vector<Course> userCourses;

    void setUpCoursesComboBox();
    void displaySchedule();
    void clearSchedule();
    void setUpUserCourses();

    void refresh();

private slots:
    void on_pbAddCourse_clicked();

    void on_pbRefresh_clicked();

    void on_cbCoursesList_currentIndexChanged(int index);

    void on_pbRemoveCourse_clicked();

    void removeCourse(int index);

private:
    Ui::SystemWindow *ui;
};

#endif // SYSTEMWINDOW_H
