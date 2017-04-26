#ifndef CALENDAR_H
#define CALENDAR_H

#include <QDialog>

namespace Ui {
class calendar;
}

class calendar : public QDialog
{
    Q_OBJECT

public:
    explicit calendar(QWidget *parent = 0);
    ~calendar();

private:
    Ui::calendar *ui;
};

#endif // CALENDAR_H
