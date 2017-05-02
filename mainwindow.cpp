#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    //UI Setup
    ui->setupUi(this);
    ui->pages->setCurrentIndex(0);
    ui->returnDateEdit->hide();
    ui->returnFlightLabel->hide();
    ui->returnFlightList->hide();
    ui->popups->hide();
    ui->addFlightButton_2->hide();
    ui->LogoutButton->hide();
    ui->myFlightsButton->hide();ui->myFlightsLabel->hide();ui->myFlightsList->hide();ui->myFlightsBack->hide();

    //Declare values
   std::vector<Airport*> Airports = readAirports();
   QStringList airportNames;
   QStringList airportCountries;

   //Fill airport lists
   for (int i=0; i<Airports.size();i++){
       QString airportCountry = Airports[i]->getCountry();
       QString airportName = Airports[i]->getName();
       airportCountries.append(airportCountry);
       airportNames.append(airportName);
   }

   //Add items to UI lists
   ui->fromAirportList->addItems(airportCountries);
   ui->toAirportList->addItems(airportCountries);
   ui->addFlightTo->addItems(airportNames);
   ui->addFlightFrom->addItems(airportNames);

   //Signals wrote for connecting buttons
   connect(ui->loginButton_2,SIGNAL(clicked()),ui->menuButtons,SLOT(close()));
   connect(ui->loginButton_2,SIGNAL(clicked()),ui->popups,SLOT(show()));

   currentUser = NULL;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_returnCheckBox_stateChanged(int arg1)
{
    //Connect signals on returnCheckbox to change values depending on whats clicked
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
       //Get input from user
       QString email = ui->emailInput->text();
       QString firstName = ui->firstNameInput->text();
       QString lastName = ui->lastNameInput->text();
       QString password;

       //Check passwords are both the same
       if (ui->passwordInput->text() == ui->passwordInput_2->text()){
           //False user to use checkLogin
           User* user = new User(email,firstName,lastName,password,"0","");
           password = ui->passwordInput->text();
           user = checkLogin(email, password);
           //Check that user isn't already made return user

           //Check user is null
           if (user == NULL){
               //Check if boxes are filled
               if (email == NULL || firstName == NULL || lastName == NULL || password == NULL) {
                   QMessageBox::about(this, "ERROR", "Please fill out all fields.");
               } else {
                   //Create new user and write it
                   User* user = new User(email,firstName,lastName,password,"0","");
                   writeUsers(user);

                   ui->popups->hide();
                   ui->menuButtons->show();

                   QMessageBox::about(this, "SUCCESS", ("You have been registered, " + firstName));

              }
           }
           else
           {
               QMessageBox::about(this, "ERROR", "That user already exists");
           }

       }
       else{
            QMessageBox::about(this, "ERROR", "Passwords don't match.");
       }


}

void MainWindow::on_searchFlightButton_2_clicked()
{
    //Get destination country from lists
    QString destinationCountry = ui->toAirportList->currentText();
    QString departureCountry = ui->fromAirportList->currentText();
    QString date = ui->flightDateEdit->text();
    QString returnDate = ui->returnDateEdit->text();

    //Declare values and vectors
    QString dest, dep;
    std::vector<Airport*> airports = readAirports();
    std::vector<Flight*> flights = readFlights();

    bool isConnecting = true;
    bool isConnectingReturn = true;


    //Airport IDs
    int departureAirportID;
    int destinationAirportID;

    //Loop over current airports getting destination and departure ID
    for (int i = 0; i < airports.size(); i++) {
        if (airports[i]->getCountry() == destinationCountry) {
            dest = airports[i]->getName();
            destinationAirportID = airports[i]->getID();
        }
        if (airports[i]->getCountry() == departureCountry) {
            dep = airports[i]->getName();
            departureAirportID = airports[i]->getID();
        }
    }

    //Check to make sure that the user is not trying to search for a flight with same dist and dest
    if (departureAirportID == destinationAirportID){
        QMessageBox::about(this, "ERROR", "Cannot fly from and to the same airport");
        return;
    }

    //Get connecting airport ID and name
    int parentAirportID = getConnectingFlight(departureAirportID, destinationAirportID);
    QString connectingAirportName = airports[parentAirportID]->getName();

    std::vector<Flight*> correctFlights = searchForFlights(dest, dep, date, 3);

    //Cleared the lists so that there is no old information in them

    ui->outboundFlightList->clear();
    ui->returnFlightList->clear();
    QString flightToAdd = "";

    //Get all of the flight on specific dates
    std::vector<Flight*> connectingFlights = searchForFlights(dest, connectingAirportName, date, 1);
    std::vector<Flight*> connectingFlights2 = searchForFlights(connectingAirportName, dep, date, 1);
    std::vector<Flight*> connectingReturnFlights = searchForFlights(connectingAirportName, dest, returnDate, 1);
    std::vector<Flight*> connectingReturnFlights2 = searchForFlights(dep, connectingAirportName, returnDate, 1);
    //Checking if there are any connecting flights
    for (int i = 0; i < correctFlights.size(); i++)
    {
        if (correctFlights[i]->getDistance() > 15000)
        {
            //Check if there is a connecting flight on that date
            if (connectingFlights.size() == 0 || connectingFlights2.size() == 0)
            {
                isConnecting = false;
                QMessageBox::about(this, "ERROR", "No Connecting flights on this date.");
            }
            //Check if the return check box is ticked
            if (ui->returnCheckBox->isChecked())
            {
                //Check if there is a connecting flight on the return date
                if (connectingReturnFlights.size() == 0 || connectingReturnFlights2.size() == 0)
                {
                    isConnectingReturn = false;
                    QMessageBox::about(this, "ERROR", "No Connecting flights on the return date.");
                }
            }
        }
    }
    //Checking if the correct connecting flights exist
    for (int i = 0; i < connectingFlights.size(); i++)
    {
        if (connectingFlights[i]->getDestination() == dest && connectingFlights[i]->getDeparture() == connectingAirportName)
        {
            for (int i = 0; i < connectingFlights2.size(); i++)
            {
                if(connectingFlights2[i]->getDestination() == connectingAirportName && connectingFlights2[i]->getDeparture() == dep)
                {
                    isConnecting = true;
                }
            }
        }
    }
    //Checking if the correct return connecting flights exist
    for (int i = 0; i < connectingReturnFlights.size(); i++)
    {
        if (connectingReturnFlights[i]->getDestination() == connectingAirportName && connectingReturnFlights[i]->getDeparture() == dest)
        {
            for (int i = 0; i < connectingReturnFlights2.size(); i++)
            {
                if(connectingReturnFlights2[i]->getDestination() == dep && connectingReturnFlights2[i]->getDeparture() == connectingAirportName)
                {
                    isConnectingReturn = true;
                }
            }
        }
    }

    //If there is a connecting on that date dispaly the flight
    if(isConnecting)
    {
        for (int i = 0; i < correctFlights.size(); i++) {
                //Calculate flight to add from input fields
                flightToAdd = (QString::number(correctFlights[i]->getID()) + " | " + correctFlights[i]->getDate()) + "  |  " +
                                        correctFlights[i]->getDeparture() + " --> " + correctFlights[i]->getDestination();
            //Add fligths
            ui->outboundFlightList->addItem(flightToAdd);
        }

        //Check if needed to do for return
        if (ui->returnCheckBox->isChecked() && isConnectingReturn) {
            QString returnDate = ui->returnDateEdit->text();
            std::vector<Flight*> correctReturnFlights = searchForFlights(dep, dest, returnDate, 1);

            //Clear return flight list and fill with new return flights
            ui->returnFlightList->clear();
            for (int i = 0; i < correctReturnFlights.size(); i++) {
                QString returnFlightToAdd = (QString::number(correctReturnFlights[i]->getID()) + " | " +
                                             correctReturnFlights[i]->getDate()) + "  |  " +
                                        correctReturnFlights[i]->getDeparture() + " --> " + correctReturnFlights[i]->getDestination();

                ui->returnFlightList->addItem(returnFlightToAdd);
            }
        }
    }
}

void MainWindow::on_loginuserButton_2_clicked()
{
    //Get login and password
    QString loginName = ui->usernameField_2->text();
    QString loginPassword = ui->passwordField_2->text();

    //Check not empty
    if (loginName!=NULL && loginPassword!=NULL) {
       // User* currentUser = checkLogin(loginName, loginPassword);
        currentUser = checkLogin(loginName, loginPassword);
        if(currentUser == NULL) {
            QMessageBox::about(this, "ERROR", "Incorrect Login Details.");
        } else {
            //Set up home screen
            QMessageBox::about(this, "SUCCESS", ("Logged in as " + currentUser->getFirstName()));
            ui->popups->hide();
            ui->menuButtons->show();
            ui->loginButton_2->hide();
            ui->LogoutButton->show();
            ui->myFlightsButton->show();
            ui->registerButton_2->hide();

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
    ui->popups->setCurrentIndex(4);
    ui->menuButtons->hide();
}

void MainWindow::on_cancelAddFlightButton_clicked()
{
    ui->popups->hide();
    ui->menuButtons->show();
}

void MainWindow::on_addFlightButton_clicked()
{
    //Read in airports and change UI
    std::vector<Airport*> Airports = readAirports();
    std::vector<Flight*> Flights = readFlights();
    ui->popups->hide();
    ui->menuButtons->show();

    //Find ID number
    int ID = Flights.size();
    //Read in user input and declare variables
    QString date = ui->addFlightDate->date().toString("dd.MM.yyyy");
    int capacity = ui->capacityNumber->value();
    QString addFlightTo = ui->addFlightTo->currentText();
    QString addFlightFrom = ui->addFlightFrom->currentText();
    Airport* fromAirport;
    Airport* toAirport;

    //Find toAirport object and fromAirport object
    for (int i = 0; i<Airports.size();i++){
        if (addFlightTo == Airports[i]->getName()){
            toAirport = Airports[i];
        }
        else if(addFlightFrom == Airports[i]->getName()){
            fromAirport = Airports[i];
        }
    }

    //Write to flight object and use writeFlight to send to XML file
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
        //Check if user is null (if logged in it wouldnt be null)
        if (currentUser == NULL){
            QMessageBox::about(this, "NO ACCESS", ("You must login or register to do that!"));
            ui->popups->show();
            ui->popups->setCurrentIndex(0);
            ui->menuButtons->hide();
        }
        else
        {
            //Check there is an item selected in the list and if so show book flight tab
            if (ui->outboundFlightList->currentItem()!= NULL||ui->returnFlightList->currentItem() != NULL)
            {
            ui->popups->show();
            ui->popups->setCurrentIndex(2);
            ui->menuButtons->hide();
            }
            else
            {
                QMessageBox::about(this, "NO ACCESS", ("You must select a flight to book one"));
            }
        }
}

void MainWindow::on_cancelPushButton_clicked()
{
    ui->popups->hide();
    ui->menuButtons->show();
}

void MainWindow::on_bookPushButton_clicked()
{
     //If a return flight is needed do below
     if (ui->returnCheckBox->isChecked()) {
            //Check item selected
            if (ui->outboundFlightList->currentItem() != NULL && ui->returnFlightList->currentItem() != NULL) {

                //Get selected items from list for return and sending flight
                std::string flight = ui->outboundFlightList->currentItem()->text().toStdString();
                std::string returnFlight = ui->returnFlightList->currentItem()->text().toStdString();

                //Declare vector of strings (flight details)

                std::vector<std::string> strings;

                strings.push_back(flight);
                strings.push_back(returnFlight);

                //Loop over vector
                for (int i = 0; i < strings.size(); i++) {
                    //Find ID from start of string
                    std::size_t found = strings[i].find("|");

                    std::string id = strings[i].substr(0, found - 1);

                    QString qID = QString::fromStdString(id);

                    //Gets the date of the flight
                    std::string dateStr = strings[i].substr(found + 2, 10);
                    QString qDateStr = QString::fromStdString(dateStr);

                    //Finds the individual flights for the connecting flight
                    std::vector<Flight*> bothFlights = findBothFlights(qID, qDateStr);

                    //Loops though the individual flights to update the capacity
                    for (int j = 0; j < bothFlights.size(); j++) {
                        QString bothQID = QString::fromStdString(std::to_string(bothFlights[j]->getID()));

                        //Edits the flight capacity
                        editFlights(bothQID);
                    }

                    //Adds the flight to the users booked flights and write to file
                    currentUser->addBookedFlight(qID);
                    editUsers(currentUser->getEmail(), qID);

                    //Upadtes the capacity of the main flight
                    editFlights(qID);

                }



            } else {
                QMessageBox::about(this, "ERROR", "Please fill select an outgoing and return flight.");
            }
     } else {


         //Get flight ID
         std::string flight = ui->outboundFlightList->currentItem()->text().toStdString();
         std::size_t found = flight.find("|");

         std::string id = flight.substr(0, found - 1);

         QString qID = QString::fromStdString(id);

         //Gets the date
         std::string dateStr = flight.substr(found + 2, 10);
         QString qDateStr = QString::fromStdString(dateStr);

         //Finds the individual flights
         std::vector<Flight*> bothFlights = findBothFlights(qID, qDateStr);

         //Loops through the vector to edit the flight capacity
         for (int j = 0; j < bothFlights.size(); j++) {
             QString bothQID = QString::fromStdString(std::to_string(bothFlights[j]->getID()));

             editFlights(bothQID);
         }

         //Adds the flight to the users flight list and writes to file
         currentUser->addBookedFlight(qID);
         editUsers(currentUser->getEmail(), qID);

         //Edits the capacity of the flight int the file
         editFlights(qID);

     }

     ui->menuButtons->show();
     ui->popups->hide();
}

void MainWindow::on_LogoutButton_clicked()
{
    //Logout button changes UI and displays logout message
    QMessageBox::about(this, "SUCCESS", ("You are now logged out!"));
    this->setWindowTitle("Takeoff");
    ui->LogoutButton->hide();
    ui->loginButton_2->show();
    ui->addFlightButton_2->hide();
    ui->registerButton_2->show();
    ui->myFlightsButton->hide();
    ui->bookFlightButton->show();
    ui->myFlightsList->hide();ui->myFlightsLabel->hide();
    ui->myFlightsButton->hide();ui->myFlightsBack->hide();
    ui->outboundFlightList->show();ui->outboundFlightLabel->show();
    ui->flightDetailsBox->setEnabled(true);
    currentUser = NULL;
}

void MainWindow::on_myFlightsButton_clicked()
{
    //Setup UI for my flights button
    ui->myFlightsList->clear();
    ui->flightDetailsBox->setEnabled(false);
    ui->myFlightsBack->show();
    ui->myFlightsButton->hide();
    ui->myFlightsLabel->show();ui->myFlightsList->show();
    ui->returnFlightList->hide();ui->returnFlightLabel->hide();
    ui->outboundFlightList->hide();ui->outboundFlightLabel->hide();
    ui->addFlightButton_2->hide();
    ui->bookFlightButton->hide();
    ui->popups->hide();
    ui->menuButtons->show();

    //Read in users booked flights
    std::string bookedFlights = currentUser->getBookedFlights().toStdString();
    std::vector<std::string> IDVector;
    std::stringstream ss(bookedFlights);
    std::string output;

   //Split the ID Vector by commas to get individual ID of flights
   while(std::getline(ss,output,','))
   {
      if (output != "") {
        IDVector.push_back(output);
      }
   }

   //Read in the flights
   std::vector<Flight*> flights = readFlights();
   std::vector<Flight*> myFlights;

   //Find relevant flights to ID

   //Loop over flight array finding relevent ID to add to myflights vector
   for (int i = 0; i< flights.size(); i++){
       for (int j = 0; j < IDVector.size(); j++){
           if (flights[i]->getID() == std::stoi(IDVector[j])) {
                myFlights.push_back(flights[i]);
           }
       }
    }

   myFlights = sortFligts(myFlights);

   QString flightToAdd;

   //Add flights of user to the flight details page
   for (int i = 0; i < myFlights.size(); i++) {
           flightToAdd = (QString::number(myFlights[i]->getID()) + " | " + myFlights[i]->getDate()) + "  |  " +
                                   myFlights[i]->getDeparture() + " --> " + myFlights[i]->getDestination() + "  |  " +
                                   QString::number(myFlights[i]->getCapacity()) + " seats remaining.";


       ui->myFlightsList->addItem(flightToAdd);
   }
}

void MainWindow::on_myFlightsBack_clicked()
{
    //Sort out UI for button click
    ui->returnCheckBox->setChecked(0);
    ui->myFlightsBack->hide();
    ui->flightDetailsBox->setEnabled(true);
    ui->myFlightsLabel->hide();ui->myFlightsList->hide();ui->myFlightsButton->show();
    ui->outboundFlightList->show();ui->outboundFlightLabel->show();
    ui->popups->hide();
    ui->addFlightButton_2->show();
    ui->bookFlightButton->show();
}

void MainWindow::on_outboundFlightList_clicked(const QModelIndex &index)
{
    //Change UI
    ui->bookFlightButton->setEnabled(true);
    ui->popups->setCurrentIndex(3);
    ui->popups->show();
    ui->menuButtons->show();
    //Call the return showDeatils to disaply details
    bool returnFlight = 0;
    showDetails(returnFlight, "", "");
}

void MainWindow::on_myFlightsList_clicked(const QModelIndex &index)
{
    //Change UI
    ui->popups->show();
    ui->popups->setCurrentIndex(3);

    //Set up various variables needed
    std::string bookedFlights = currentUser->getBookedFlights().toStdString();
    std::vector<std::string> IDVector;
    std::stringstream ss(bookedFlights);
    std::string output;
    std::vector<Flight*> flights = readFlights();

    //Split string by comma delimiter
   while(std::getline(ss,output,','))
   {
      IDVector.push_back(output);
   }

   //Find ID from selected value of list
   std::string flight = ui->myFlightsList->currentItem()->text().toStdString();
   std::size_t found = flight.find("|");
   std::string str = flight.substr(0, found - 1);

   bool flightSet = false;
   //Loop over flights
   for (int i = 0; i < flights.size(); i++)
    {
       //Check if it is a connecting flight
       if (flights[i]->getDistance() > 15000)
       {
           if (flights[i]->getID() == std::stoi(str))
           {
               int returnFlight = 2;
               //Airport Names
               QString departureAirportName = flights[i]->getDeparture();
               QString destinationAirportName = flights[i]->getDestination();
               //Call the return showDeatils to disaply details
               showDetails(returnFlight, departureAirportName, destinationAirportName);
               flightSet = true;
           }
       }
       else
       {
           //If vector matches add these details to screen
           if (flights[i]->getID() == std::stoi(str) && flightSet == false)
           {
            //Change UI
            ui->connectingFlightLabel->setText("Not needed");
            ui->durationLabel->setText(QString::number(flights[std::stoi(str)]->getDuration()) + " hours");
            ui->spacesAvailableLabel->setText(QString::number(flights[std::stoi(str)]->getCapacity()));
            ui->priceLabel->setText("£" + QString::number(flights[std::stoi(str)]->getPrice()));
           }
       }
    }
}

void MainWindow::on_returnFlightList_clicked(const QModelIndex &index)
{
    //Change UI
    ui->bookFlightButton->setEnabled(true);
    ui->menuButtons->show();
    ui->popups->setCurrentIndex(3);
    ui->popups->show();
    //Call the return showDeatils to disaply details
    bool returnFlight = 1;
    showDetails(returnFlight, "", "");
}

void MainWindow::showDetails(int returnFlight, QString departureAirportName, QString destinationAirportName)
{
    //Declaring the flight IDs
    int flightID;
    int connectingFLightID;

    //QStrings for departure/destination countrys
    QString departureCountry;
    QString destinationCountry;

    if (returnFlight == 1 && departureAirportName == "" && destinationAirportName == "")
    {
        departureCountry = ui->toAirportList->currentText();
        destinationCountry = ui->fromAirportList->currentText();

        //Get the ID of a flight when not a connecting flight
        std::string flight = ui->returnFlightList->currentItem()->text().toStdString();
        std::size_t found = flight.find("|");
        flightID = std::stoi(flight.substr(0, found - 1));
    }
    else if (returnFlight == 0 && departureAirportName == "" && destinationAirportName == "")
    {
        destinationCountry = ui->toAirportList->currentText();
        departureCountry = ui->fromAirportList->currentText();

        //Get the ID of a flight when not a connecting flight
        std::string flight = ui->outboundFlightList->currentItem()->text().toStdString();
        std::size_t found = flight.find("|");
        flightID = std::stoi(flight.substr(0, found - 1));
    }

    //Declare values
    QString dest,dep;

    std::vector<Airport*> airports = readAirports();
    std::vector<Flight*> flights = readFlights();

    //Airport IDs
    int departureAirportID;
    int destinationAirportID;


    //Loop over airports
    for (int i = 0; i < airports.size(); i++) {
        if (departureAirportName == "" && destinationAirportName == "")
        {
            if (airports[i]->getCountry() == destinationCountry) {
                dest = airports[i]->getName();
                destinationAirportID = airports[i]->getID();
            }
            if (airports[i]->getCountry() == departureCountry) {
                dep = airports[i]->getName();
                departureAirportID = airports[i]->getID();
            }
        }
        else
        {
            if (airports[i]->getName() == destinationAirportName) {
                dest = destinationAirportName;
                destinationAirportID = airports[i]->getID();
            }
            if (airports[i]->getName() == departureAirportName) {
                dep = departureAirportName;
                departureAirportID = airports[i]->getID();
            }
        }


    }
    //Get connecting airport ID
    int parentAirportID = getConnectingFlight(departureAirportID, destinationAirportID);

    //Get the selected flight ID
    for (int i = 0; i < flights.size(); i++)
    {
        if(flights[i]->getDestination() == airports[parentAirportID]->getName() && flights[i]->getDeparture() == dep)
        {
           connectingFLightID = flights[i]->getID();
        }
    }
    //Check if the flight is selected from my flights
    if (returnFlight == 2 )
    {
        //Get the ID of a flight when not a connecting flight
        std::string flight = ui->myFlightsList->currentItem()->text().toStdString();
        std::size_t found = flight.find("|");
        flightID = std::stoi(flight.substr(0, found - 1));
    }


    //Check if the flight needs a connecting flight and if it does dispaly it
    if (flights[flightID]->getDistance() > 15000)
    {
        //Set data for connecting flights
        QString connectingAirportName = airports[parentAirportID]->getName();
        ui->connectingFlightLabel->setText(connectingAirportName);
        ui->durationLabel->setText(QString::number(flights[flightID]->getDuration()) + " hours");
        ui->spacesAvailableLabel->setText(QString::number(flights[flightID]->getCapacity()));
        ui->priceLabel->setText("£" + QString::number(flights[flightID]->getPrice()));

    }
    else
    {
        //Set date for none connecting flights
        ui->connectingFlightLabel->setText("Not needed");
        ui->durationLabel->setText(QString::number(flights[flightID]->getDuration()) + " hours");
        ui->spacesAvailableLabel->setText(QString::number(flights[flightID]->getCapacity()));
        ui->priceLabel->setText("£" + QString::number(flights[flightID]->getPrice()));

    }

}

std::vector<Flight*> MainWindow::sortFligts(std::vector<Flight*> &correctFlights)
{
    //Check if sorting finished
    bool sortDone = false;
    float nextPrice;

        while (!sortDone)
        {
            sortDone = true;

            for (int i = 0; i < correctFlights.size(); ++i)
            {
                //Get the prices of the flights
                float price = correctFlights[i]->getPrice();
                if (i != correctFlights.size()-1)
                {
                    nextPrice = correctFlights[i+1]->getPrice();
                    //Compare the current price with the next one
                    if ( price > nextPrice)
                    {
                        //If the current price is smaller than the next price swap them
                        Flight* tmp = correctFlights[i];
                        correctFlights[i] = correctFlights[i+1];
                        correctFlights[i+1] = tmp;

                        //Because there was a swap made we need to go through the array again
                        sortDone = false;
                    }
                }
            }
        }
    return correctFlights;
}
