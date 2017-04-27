#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "user.h"
#include "airport.h"
#include "XMLhandler.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pages->setCurrentIndex(0);
    ui->returnDateEdit->hide();
    ui->returnFlightLabel->hide();
    ui->returnFlightList->hide();
    ui->popups->hide();

   std::vector<Airport*> Airports = readAirports();
   QStringList airportNames;

   for (int i=0; i<Airports.size();i++){
       QString airportName = Airports[i]->getName();
       airportNames.append(airportName);
   }

   ui->fromAirportList->addItems(airportNames);
   ui->toAirportList->addItems(airportNames);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
   ui->popups->show();
   ui->loginButton->hide();
   ui->registerButton->hide();
   ui->popups->setCurrentIndex(0);
}

void MainWindow::on_loginBackButton_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_registerBackButton_clicked()
{
    ui->pages->setCurrentIndex(0);
}

void MainWindow::on_registerButton_clicked()
{
    ui->popups->show();
    ui->popups->setCurrentIndex(1);
    ui->loginButton->hide();
    ui->registerButton->hide();
}

void MainWindow::on_returnCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnDateEdit,SLOT(show()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightList,SLOT(show()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightLabel,SLOT(show()));
    }
    else
    {
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnDateEdit,SLOT(close()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightList,SLOT(close()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightLabel,SLOT(close()));
    }
}


void MainWindow::on_registerUserButton_clicked()
{
    ui->popups->hide();
    ui->loginButton->show();
    ui->registerButton->show();


    QString email = ui->emailInput->text();
       QString firstName = ui->firstNameInput->text();
       QString lastName = ui->lastNameInput->text();
       QString password;
       if (ui->passwordInput->text() == ui->passwordInput_2->text()){
           password = ui->passwordInput->text();
       }
       else{

       }
       User* user = new User(email,firstName,lastName,password,false);
}

void MainWindow::on_searchFlightButton_2_clicked()
{
    QString toAirport = ui->toAirportList->itemData(ui->toAirportList->currentIndex()).toString();
    QString fromAirport = ui->toAirportList->itemData(ui->toAirportList->currentIndex()).toString();
}

void MainWindow::on_loginuserButton_2_clicked()
{
   ui->loginPopup->hide();
   ui->loginButton->show();
   ui->registerButton->show();
}

void MainWindow::on_loginBackButton_2_clicked()
{
    ui->popups->hide();
    ui->loginButton->show();
    ui->registerButton->show();
}

void MainWindow::on_cancelRegister_clicked()
{
    ui->popups->hide();
    ui->loginButton->show();
    ui->registerButton->show();
}
