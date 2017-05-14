#ifndef DIALOGREMOVESECTION_H
#define DIALOGREMOVESECTION_H

#include <QDialog>
#include "course.h"
#include "section.h"
#include <QComboBox>
#include <QSignalMapper>
#include "apiservice.h"

namespace Ui {
class DialogRemoveSection;
}

class DialogRemoveSection : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRemoveSection(std::vector<Course> professorCourses, QWidget *parent = 0);
    ~DialogRemoveSection();

private slots:
    void on_cbCourseCode_activated(const QString &arg1);

    void on_pbRemoveSection_clicked();

private:
    Ui::DialogRemoveSection *ui;
    std::vector<Course> professorCourses;
};

#endif // DIALOGREMOVESECTION_H
