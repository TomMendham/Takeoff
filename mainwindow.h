#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "system.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "user.h"
#include "airport.h"
#include <QMessageBox>
#include <sstream>

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
    void on_bookFlightButton_clicked();
    void on_cancelPushButton_clicked();
    void on_bookPushButton_clicked();
    void on_LogoutButton_clicked();
    void on_myFlightsButton_clicked();
    void on_myFlightsBack_clicked();
    void on_outboundFlightList_clicked(const QModelIndex &index);

    void on_myFlightsList_clicked(const QModelIndex &index);

    void on_returnFlightList_clicked(const QModelIndex &index);

    void showDetails(bool returnFlight, QString departureAirportName, QString destinationAirportName);

private:
    Ui::MainWindow *ui;
    User* currentUser;
};

#endif // MAINWINDOW_H
