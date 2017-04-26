#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setHidden(true);

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
    ui->pages->setCurrentIndex(3);
}


