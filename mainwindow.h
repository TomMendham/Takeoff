#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "system.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public System
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_returnCheckBox_stateChanged(int arg1);
    void on_registerUserButton_clicked();
    void on_searchFlightButton_2_clicked();
    void on_loginuserButton_2_clicked();
    void on_loginBackButton_2_clicked();
    void on_cancelRegister_clicked();
    void on_registerButton_2_clicked();
    void on_addFlightButton_2_clicked();

    void on_cancelAddFlightButton_clicked();

    void on_addFlightButton_clicked();

    void on_loginButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
