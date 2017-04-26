#include "calendar.h"
#include "ui_calendar.h"

calendar::calendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calendar)
{
    ui->setupUi(this);
}

calendar::~calendar()
{
    delete ui;
}
