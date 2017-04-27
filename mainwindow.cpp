#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "user.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pages->setCurrentIndex(0);
    ui->returnBox->hide();
    ui->returnFlightLabel->hide();
    ui->returnFlightList->hide();
    MainWindow::setWindowIcon(QIcon("/Images/aeroplane.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginButton_clicked()
{
    ui->pages->setCurrentIndex(1);
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
    ui->pages->setCurrentIndex(2);
}

void MainWindow::on_returnCheckBox_stateChanged(int arg1)
{
    if (arg1 == 2){
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnBox,SLOT(show()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightList,SLOT(show()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightLabel,SLOT(show()));
    }
    else
    {
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnBox,SLOT(close()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightList,SLOT(close()));
        connect(ui->returnCheckBox,SIGNAL(clicked()),ui->returnFlightLabel,SLOT(close()));
    }
}


void MainWindow::on_registerUserButton_clicked()
{
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
