#include "mainwindow.h"



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
    ui->addFlightButton_2->hide();
    ui->LogoutButton->hide();
    ui->myFlightsButton->hide();ui->myFlightsLabel->hide();ui->myFlightsList->hide();ui->myFlightsBack->hide();

   std::vector<Airport*> Airports = readAirports();
   QStringList airportNames;
   QStringList airportCountries;

   for (int i=0; i<Airports.size();i++){
       QString airportCountry = Airports[i]->getCountry();
       QString airportName = Airports[i]->getName();
       airportCountries.append(airportCountry);
       airportNames.append(airportName);
   }

   ui->fromAirportList->addItems(airportCountries);
   ui->toAirportList->addItems(airportCountries);
   ui->addFlightTo->addItems(airportNames);
   ui->addFlightFrom->addItems(airportNames);

   connect(ui->loginButton_2,SIGNAL(clicked()),ui->menuButtons,SLOT(close()));
   connect(ui->loginButton_2,SIGNAL(clicked()),ui->popups,SLOT(show()));

}

MainWindow::~MainWindow()
{

    delete ui;
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
//    //Tesing Testing
//    //std::vector<std::vector<float>> matrix(V, std::vector<float>(V));

//    std::vector<Flight*> Flights = readFlights();

//    fillFlightGrid(Flights, matrix);

//    int parent[V];
//    int airportID = 1;

//    //getConnectingFlight(parent [V],int airportCode);
//    dijkstra(matrix, airportID, parent);

//    for (int i = 0; i < V; i++)
//    {
//        for (int j = 0; j < V; j++)
//        {
//            std::cout << matrix[i][j] << "              ";
//        }
//        std::cout  << std::endl;
//    }
//    for(int i = 0; i < 4; i++)
//    {
//        std::cout << parent[i] << std::endl;
//    }
    //Tesing Testing

       QString email = ui->emailInput->text();
       QString firstName = ui->firstNameInput->text();
       QString lastName = ui->lastNameInput->text();
       QString password;
       if (ui->passwordInput->text() == ui->passwordInput_2->text()){
           password = ui->passwordInput->text();

           if (email == NULL || firstName == NULL || lastName == NULL || password == NULL) {
               QMessageBox::about(this, "ERROR", "Please fill out all fields.");
           } else {
               User* user = new User(email,firstName,lastName,password,"1");
               writeUsers(user);

               ui->popups->hide();
               ui->menuButtons->show();

               QMessageBox::about(this, "SUCCESS", ("You have been registered, " + firstName));

           }

       }
       else{
            QMessageBox::about(this, "ERROR", "Passwords don't match.");
       }


}

void MainWindow::on_searchFlightButton_2_clicked()
{
    QString destinationCountry = ui->toAirportList->currentText();
    QString departureCountry = ui->fromAirportList->currentText();
    QString date = ui->flightDateEdit->text();

    QString dest, dep;
    std::vector<Airport*> airports = readAirports();

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i]->getCountry() == destinationCountry) {
            dest = airports[i]->getName();
        }
        if (airports[i]->getCountry() == departureCountry) {
            dep = airports[i]->getName();
        }
    }

    std::vector<Flight*> correctFlights = searchForFlights(dest, dep, date);

    ui->outboundFlightList->clear();
    for (int i = 0; i < correctFlights.size(); i++) {
        QString flightToAdd = (QString::number(correctFlights[i]->getID()) + " | £" + QString::number(correctFlights[i]->getPrice()) + "  |  " + correctFlights[i]->getDate()) + "  |  " +
                                correctFlights[i]->getDeparture() + " --> " + correctFlights[i]->getDestination() + "  |  " +
                                QString::number(correctFlights[i]->getCapacity()) + " seats remaining.";

        ui->outboundFlightList->addItem(flightToAdd);
    }

    if (ui->returnCheckBox->isChecked()) {
        QString returnDate = ui->returnDateEdit->text();
        std::vector<Flight*> correctReturnFlights = searchForFlights(dep, dest, returnDate);

        ui->returnFlightList->clear();
        for (int i = 0; i < correctReturnFlights.size(); i++) {
            QString returnFlightToAdd = ("£" + QString::number(correctReturnFlights[i]->getPrice()) + "  |  " + correctReturnFlights[i]->getDate()) + "  |  " +
                                    correctReturnFlights[i]->getDeparture() + " --> " + correctReturnFlights[i]->getDestination() + "  |  " +
                                    QString::number(correctReturnFlights[i]->getCapacity()) + " seats remaining.";

            ui->returnFlightList->addItem(returnFlightToAdd);
        }
    }
}

void MainWindow::on_loginuserButton_2_clicked()
{
    QString loginName = ui->usernameField_2->text();
    QString loginPassword = ui->passwordField_2->text();

    if (loginName!=NULL && loginPassword!=NULL) {
       // User* currentUser = checkLogin(loginName, loginPassword);
        currentUser = checkLogin(loginName, loginPassword);
        if(currentUser == NULL) {
            QMessageBox::about(this, "ERROR", "Incorrect Login Details.");
        } else {
            QMessageBox::about(this, "SUCCESS", ("Logged in as " + currentUser->getFirstName()));
            ui->popups->hide();
            ui->menuButtons->show();
            ui->loginButton_2->hide();
            ui->LogoutButton->show();
            ui->myFlightsButton->show();

            std::cout << currentUser->getAdmin().toStdString() << std::endl;
            this->setWindowTitle("Takeoff - "+currentUser->getFirstName());

            if (currentUser->getAdmin() == "1") {
                ui->addFlightButton_2->show();
            }


        }

    } else {
        QMessageBox::about(this, "ERROR", "Please fill out both fields.");
    }
}

void MainWindow::on_loginBackButton_2_clicked()
{
    ui->popups->hide();
    ui->menuButtons->show();
}

void MainWindow::on_cancelRegister_clicked()
{
    ui->popups->hide();
    ui->menuButtons->show();
}


void MainWindow::on_registerButton_2_clicked()
{
    ui->popups->show();
    ui->popups->setCurrentIndex(1);
    ui->menuButtons->hide();
}

void MainWindow::on_addFlightButton_2_clicked()
{
    ui->popups->show();
    ui->popups->setCurrentIndex(3);
    ui->menuButtons->hide();
}


void MainWindow::on_cancelAddFlightButton_clicked()
{
    ui->popups->hide();
    ui->menuButtons->show();
}

void MainWindow::on_addFlightButton_clicked()
{
    std::vector<Airport*> Airports = readAirports();
    ui->popups->hide();
    ui->menuButtons->show();
    int ID = ui->IDInput->value();
    QString date = ui->addFlightDate->date().toString("dd.MM.yyyy");
    int capacity = ui->capacityNumber->value();
    QString addFlightTo = ui->addFlightTo->currentText();
    QString addFlightFrom = ui->addFlightFrom->currentText();
    Airport* fromAirport;
    Airport* toAirport;

    for (int i = 0; i<Airports.size();i++){
        if (addFlightTo == Airports[i]->getName()){
            toAirport = Airports[i];
        }
        else if(addFlightFrom == Airports[i]->getName()){
            fromAirport = Airports[i];
        }
    }

    Flight* f = new Flight(ID,date,capacity,toAirport,fromAirport);
    writeFlights(f);
}

void MainWindow::on_loginButton_2_clicked()
{
    ui->popups->show();
    ui->popups->setCurrentIndex(0);
    ui->menuButtons->hide();
}

void MainWindow::on_bookFlightButton_clicked()
{
    ui->popups->show();
    ui->popups->setCurrentIndex(2);
    ui->menuButtons->hide();
}

void MainWindow::on_cancelPushButton_clicked()
{
    ui->popups->hide();
    ui->menuButtons->show();
}

void MainWindow::on_bookPushButton_clicked()
{
    std::string flight = ui->outboundFlightList->currentItem()->text().toStdString();

    std::size_t found = flight.find("|");

    std::string str = flight.substr(0, found - 1);

    currentUser->addBookedFlight(str);



}

void MainWindow::on_LogoutButton_clicked()
{
    QMessageBox::about(this, "SUCCESS", ("You are now logged out!"));
    this->setWindowTitle("Takeoff");
    ui->LogoutButton->hide();
    ui->loginButton_2->show();
    currentUser = NULL;
}

void MainWindow::on_myFlightsButton_clicked()
{
    ui->flightDetailsBox->setEnabled(false);
    ui->myFlightsBack->show();
    ui->myFlightsButton->hide();
    ui->myFlightsLabel->show();ui->myFlightsList->show();
    ui->returnFlightList->hide();ui->returnFlightLabel->hide();
    ui->outboundFlightList->hide();ui->outboundFlightLabel->hide();
}

void MainWindow::on_myFlightsBack_clicked()
{
    ui->myFlightsBack->hide();
    ui->flightDetailsBox->setEnabled(true);
    ui->myFlightsLabel->hide();ui->myFlightsList->hide();ui->myFlightsButton->show();
    ui->returnFlightList->show();ui->returnFlightLabel->show();
    ui->outboundFlightList->show();ui->outboundFlightLabel->show();
}

