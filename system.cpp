#include "system.h"
#include "user.h"
#include "flight.h"
#include "airport.h"
#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QXmlStreamReader>
#include <iostream>
#include <sstream>
#include <QDir>


System::System()
{

}


User* System::checkLogin(QString user, QString pass) {
    std::vector<User*> Users = readUsers();



    for (int i = 0; i < Users.size(); i++) {
        if (Users[i]->getEmail() == user) {
            if (Users[i]->getPassword() == pass) {
                return Users[i];
            }
        }
    }

    return NULL;

}


std::vector<Flight*> System::searchForFlights(QString dest, QString dep, QString date, int diff) {
    std::vector<Flight*> Flights = readFlights();
    std::vector<Flight*> correctFlights;

    std::string year = date.toStdString().substr(6,4);
    std::string month = date.toStdString().substr(3,2);
    std::string day = date.toStdString().substr(0,2);
    int iDay = std::stoi(day);

    std::string fYear, fMonth, fDay;

    for (int i = 0; i < Flights.size(); i++) {
        if (Flights[i]->getDeparture() == dep) {
            if (Flights[i]->getDestination() == dest) {

                fYear = Flights[i]->getDate().toStdString().substr(6,4);
                fMonth = Flights[i]->getDate().toStdString().substr(3,2);
                fDay = Flights[i]->getDate().toStdString().substr(0,2);

                int ifDay = std::stoi(fDay);

                if (fYear == year) {
                    if (fMonth == month) {
                        if ((ifDay > (iDay-diff)) && (ifDay < iDay+diff)) {
                            correctFlights.push_back(Flights[i]);
                        }
                    }
                }
            }
        }
    }

    return correctFlights;
}



//XML FUNCTIONS

std::vector<Airport*> System::readAirports() {
    QXmlStreamReader Rxml;


    QString cont, coun, city, name, code;
    float lon, lat;
    int id;
    std::vector<Airport*> airportVec;

    QDir dir;
    QFile file(dir.absolutePath()+"/Airports.xml");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           std::cout << "ERROR OPENING FILE" << std::endl;
    }


    Rxml.setDevice(&file);
    Rxml.readNext();

    while (!Rxml.atEnd()) {
        if (Rxml.isStartElement()) {
            if (Rxml.name() == "AIRPORTS") {
                Rxml.readNext();
            } else if (Rxml.name() == "AIRPORT") {
                while (!Rxml.atEnd()) {
                    if (Rxml.isEndElement()) {
                        Rxml.readNext();
                        break;
                    } else if (Rxml.isCharacters()) {
                        Rxml.readNext();
                    } else if (Rxml.isStartElement()) {
                        if (Rxml.name() == "CONTINENT") {

                            cont = Rxml.readElementText();

                        } else if (Rxml.name() == "COUNTRY") {

                            coun = Rxml.readElementText();

                        } else if (Rxml.name() == "CITY") {

                            city = Rxml.readElementText();

                        } else if (Rxml.name() == "NAME") {

                            name = Rxml.readElementText();

                        } else if (Rxml.name() == "CODE") {

                            code = Rxml.readElementText();

                        } else if (Rxml.name() == "LONG") {
                            std::string temp = Rxml.readElementText().toStdString();
                            lon = std::stof(temp);

                        } else if (Rxml.name() == "LAT") {
                            std::string temp = Rxml.readElementText().toStdString();
                            lat = std::stof(temp);

                        } else if (Rxml.name() == "ID") {
                            std::string temp = Rxml.readElementText().toStdString();
                            id = std::stoi(temp);

                        }

                        Rxml.readNext();
                    }
                    else {
                        Rxml.readNext();
                    }
                }
            }

            if (cont != "") {
                Airport* airport = new Airport(cont, coun, city, name, code, lat, lon, id);
                airportVec.push_back(airport);
            }

        }
        else {
            Rxml.readNext();
        }
    }

    return airportVec;

}

std::vector<Flight*> System::readFlights() {

    QXmlStreamReader Rxml;

    int ID, capacity, duration;
    QString destination, departure, date;
    float distance, pric;

    std::vector<Flight*> flightVec;

    QDir dir;
    QFile file(dir.absolutePath()+"/Flights.xml");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           std::cout << "ERROR OPENING FILE" << std::endl;
    }


    Rxml.setDevice(&file);
    Rxml.readNext();

    while (!Rxml.atEnd()) {
        if (Rxml.isStartElement()) {
            if (Rxml.name() == "FLIGHTS") {
                Rxml.readNext();
            } else if (Rxml.name() == "FLIGHT") {
                while (!Rxml.atEnd()) {
                    if (Rxml.isEndElement()) {
                        Rxml.readNext();
                        break;
                    } else if (Rxml.isCharacters()) {
                        Rxml.readNext();
                    } else if (Rxml.isStartElement()) {
                        if (Rxml.name() == "ID") {

                            std::string temp = Rxml.readElementText().toStdString();
                            ID = std::stoi(temp);

                        } else if (Rxml.name() == "CAPACITY") {

                            std::string temp = Rxml.readElementText().toStdString();
                            capacity = std::stoi(temp);

                        } else if (Rxml.name() == "DURATION") {

                            std::string temp = Rxml.readElementText().toStdString();
                            duration = std::stoi(temp);

                        } else if (Rxml.name() == "DESTINATION") {

                            destination = Rxml.readElementText();

                        } else if (Rxml.name() == "DEPARTURE") {

                            departure = Rxml.readElementText();

                        } else if (Rxml.name() == "DATE") {

                            date = Rxml.readElementText();

                        } else if (Rxml.name() == "DISTANCE") {

                            std::string temp = Rxml.readElementText().toStdString();
                            distance = std::stof(temp);
                        } else if (Rxml.name() == "PRICE") {

                            std::string temp = Rxml.readElementText().toStdString();
                            pric = std::stof(temp);
                        }


                        Rxml.readNext();
                    }
                    else {
                        Rxml.readNext();
                    }
                }
            }

            if (destination != "") {
                Flight* flight = new Flight(ID, capacity, destination, departure, duration, date, distance, pric);
                flightVec.push_back(flight);
            }

        }
        else {
            Rxml.readNext();
        }
    }

    return flightVec;
}

std::vector<User*> System::readUsers() {

    QXmlStreamReader Rxml;


    QString email, firstname, lastname, password, admin, bookedFlights;

    std::vector<User*> userVec;

    QDir dir;
    QFile file(dir.absolutePath()+"/Users.xml");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           std::cout << "ERROR OPENING FILE" << std::endl;
    }


    Rxml.setDevice(&file);
    Rxml.readNext();

    while (!Rxml.atEnd()) {
        if (Rxml.isStartElement()) {
            if (Rxml.name() == "USERS") {
                Rxml.readNext();
            } else if (Rxml.name() == "USER") {
                while (!Rxml.atEnd()) {
                    if (Rxml.isEndElement()) {
                        Rxml.readNext();
                        break;
                    } else if (Rxml.isCharacters()) {
                        Rxml.readNext();
                    } else if (Rxml.isStartElement()) {
                        if (Rxml.name() == "EMAIL") {

                            email = Rxml.readElementText();

                        } else if (Rxml.name() == "FIRSTNAME") {

                            firstname = Rxml.readElementText();

                        } else if (Rxml.name() == "LASTNAME") {

                            lastname = Rxml.readElementText();

                        } else if (Rxml.name() == "PASSWORD") {

                            password = Rxml.readElementText();

                        } else if (Rxml.name() == "ADMIN") {

                            admin = Rxml.readElementText();

                        } else if (Rxml.name() == "BOOKEDFLIGHTS") {

                            bookedFlights = Rxml.readElementText();

                        }

                        Rxml.readNext();
                    }
                    else {
                        Rxml.readNext();
                    }
                }
            }

            if (email != "") {
                User* user = new User(email, firstname, lastname, password, admin, bookedFlights);
                userVec.push_back(user);
            }

        }
        else {
            Rxml.readNext();
        }
    }

    return userVec;
}


void System::writeFlights(Flight* f) {


    std::vector<Flight*> Flights = readFlights();
    Flights.push_back(f);

    QDir dir;
    QFile file(dir.absolutePath()+"/Flights.xml");



    QXmlStreamWriter xmlWriter;


        if (!file.open(QIODevice::WriteOnly))
        {
            std::cout << "ERROR OPENING FILE" << std::endl;
        }
        else
        {

            xmlWriter.setDevice(&file);
            // Writes a document start and opens the flights element
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("FLIGHTS");


            for (int i = 0; i < Flights.size(); i++) {


                QString id = QString::number(Flights[i]->getID());
                QString capac = QString::number(Flights[i]->getCapacity());
                QString dur = QString::number(Flights[i]->getDuration());
                QString dest = Flights[i]->getDestination();
                QString dep = Flights[i]->getDeparture();
                QString date = Flights[i]->getDate();
                QString dist = QString::number(Flights[i]->getDistance());
                QString pric = QString::number(Flights[i]->getPrice());

                //open flight tag
                xmlWriter.writeStartElement("FLIGHT");

                //add one attribute and its value
                xmlWriter.writeStartElement("ID");
                xmlWriter.writeCharacters(id);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("CAPACITY");
                xmlWriter.writeCharacters(capac);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("DURATION");
                xmlWriter.writeCharacters(dur);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("DESTINATION");
                xmlWriter.writeCharacters(dest);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("DEPARTURE");
                xmlWriter.writeCharacters(dep);
                xmlWriter.writeEndElement();


                xmlWriter.writeStartElement("DATE");
                xmlWriter.writeCharacters(date);
                xmlWriter.writeEndElement();


                xmlWriter.writeStartElement("DISTANCE");
                xmlWriter.writeCharacters(dist);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("PRICE");
                xmlWriter.writeCharacters(pric);
                xmlWriter.writeEndElement();


                //close tag flight
                xmlWriter.writeEndElement();


            }


            //end tag flights
            xmlWriter.writeEndElement();
            //end document
            xmlWriter.writeEndDocument();
       }


}

void System::writeUsers(User* u) {


    std::vector<User*> Users = readUsers();



    Users.push_back(u);

    QDir dir;
    QFile file(dir.absolutePath()+"/Users.xml");


    QXmlStreamWriter xmlWriter;


        if (!file.open(QIODevice::WriteOnly))
        {
            std::cout << "ERROR OPENING FILE" << std::endl;
        }
        else
        {

            xmlWriter.setDevice(&file);
            // Writes a document start and opens the flights element
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("USERS");


            for (int i = 0; i < Users.size(); i++) {


                QString email = Users[i]->getEmail();
                QString firstname = Users[i]->getFirstName();
                QString lastname = Users[i]->getLastName();
                QString password = Users[i]->getPassword();
                QString admin = Users[i]->getAdmin();
                QString bookedFlights = Users[i]->getBookedFlights();


                //open flight tag
                xmlWriter.writeStartElement("USER");

                //add one attribute and its value
                xmlWriter.writeStartElement("EMAIL");
                xmlWriter.writeCharacters(email);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("FIRSTNAME");
                xmlWriter.writeCharacters(firstname);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("LASTNAME");
                xmlWriter.writeCharacters(lastname);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("PASSWORD");
                xmlWriter.writeCharacters(password);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("ADMIN");
                xmlWriter.writeCharacters(admin);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("BOOKEDFLIGHTS");
                xmlWriter.writeCharacters(bookedFlights);
                xmlWriter.writeEndElement();


                //close user tag
                xmlWriter.writeEndElement();


            }


            //end users tag
            xmlWriter.writeEndElement();
            //end document
            xmlWriter.writeEndDocument();
       }


}

void System::editUsers(QString email, QString str) {

    std::vector<User*> Users = readUsers();




    for (int j = 0; j < Users.size(); j++) {
        if (Users[j]->getEmail() == email) {
            Users[j]->addBookedFlight(str);
        }
    }



    QDir dir;
    QFile file(dir.absolutePath()+"/Users.xml");


    QXmlStreamWriter xmlWriter;


        if (!file.open(QIODevice::WriteOnly))
        {
            std::cout << "ERROR OPENING FILE" << std::endl;
        }
        else
        {

            xmlWriter.setDevice(&file);
            // Writes a document start and opens the flights element
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("USERS");


            for (int i = 0; i < Users.size(); i++) {


                QString email = Users[i]->getEmail();
                QString firstname = Users[i]->getFirstName();
                QString lastname = Users[i]->getLastName();
                QString password = Users[i]->getPassword();
                QString admin = Users[i]->getAdmin();
                QString bookedFlights = Users[i]->getBookedFlights();


                //open flight tag
                xmlWriter.writeStartElement("USER");

                //add one attribute and its value
                xmlWriter.writeStartElement("EMAIL");
                xmlWriter.writeCharacters(email);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("FIRSTNAME");
                xmlWriter.writeCharacters(firstname);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("LASTNAME");
                xmlWriter.writeCharacters(lastname);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("PASSWORD");
                xmlWriter.writeCharacters(password);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("ADMIN");
                xmlWriter.writeCharacters(admin);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("BOOKEDFLIGHTS");
                xmlWriter.writeCharacters(bookedFlights);
                xmlWriter.writeEndElement();


                //close user tag
                xmlWriter.writeEndElement();


            }


            //end users tag
            xmlWriter.writeEndElement();
            //end document
            xmlWriter.writeEndDocument();
       }

}

void System::editFlights(QString id) {

    std::vector<Flight*> Flights = readFlights();


    for (int j = 0; j < Flights.size(); j++) {
        if (Flights[j]->getID() == std::stoi(id.toStdString())) {
            Flights[j]->updateCapacity();
        }
    }


    QDir dir;
    QFile file(dir.absolutePath()+"/Flights.xml");



    QXmlStreamWriter xmlWriter;


        if (!file.open(QIODevice::WriteOnly))
        {
            std::cout << "ERROR OPENING FILE" << std::endl;
        }
        else
        {

            xmlWriter.setDevice(&file);
            // Writes a document start and opens the flights element
            xmlWriter.writeStartDocument();
            xmlWriter.writeStartElement("FLIGHTS");


            for (int i = 0; i < Flights.size(); i++) {


                QString id = QString::number(Flights[i]->getID());
                QString capac = QString::number(Flights[i]->getCapacity());
                QString dur = QString::number(Flights[i]->getDuration());
                QString dest = Flights[i]->getDestination();
                QString dep = Flights[i]->getDeparture();
                QString date = Flights[i]->getDate();
                QString dist = QString::number(Flights[i]->getDistance());
                QString pric = QString::number(Flights[i]->getPrice());

                //open flight tag
                xmlWriter.writeStartElement("FLIGHT");

                //add one attribute and its value
                xmlWriter.writeStartElement("ID");
                xmlWriter.writeCharacters(id);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("CAPACITY");
                xmlWriter.writeCharacters(capac);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("DURATION");
                xmlWriter.writeCharacters(dur);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("DESTINATION");
                xmlWriter.writeCharacters(dest);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("DEPARTURE");
                xmlWriter.writeCharacters(dep);
                xmlWriter.writeEndElement();


                xmlWriter.writeStartElement("DATE");
                xmlWriter.writeCharacters(date);
                xmlWriter.writeEndElement();


                xmlWriter.writeStartElement("DISTANCE");
                xmlWriter.writeCharacters(dist);
                xmlWriter.writeEndElement();

                xmlWriter.writeStartElement("PRICE");
                xmlWriter.writeCharacters(pric);
                xmlWriter.writeEndElement();


                //close tag flight
                xmlWriter.writeEndElement();


            }
            //end tag flights
            xmlWriter.writeEndElement();
            //end document
            xmlWriter.writeEndDocument();
       }

}



//CONNECTING FLIGHT FUNCTIONS
//Function to fill the flight grid
void System::fillFlightGrid(std::vector<std::vector<float>> &matrix)
{
    std::vector<Flight*> Flights = readFlights();

    for (int i = 0; i < Flights.size(); i++)
    {
        if (Flights[i]->getDestination() == "Dubai International"&& Flights[i]->getDeparture() == "London Heathrow" )
        {
            matrix[1][0] = Flights[i]->getDistance();
            matrix[0][1] = Flights[i]->getDistance();
        }
        if (Flights[i]->getDestination() == "Sydney"&& Flights[i]->getDeparture() == "London Heathrow")
        {
            matrix[2][0] = (Flights[i]->getDistance() + 10000);
            matrix[0][2] = (Flights[i]->getDistance() + 10000);
        }
        if (Flights[i]->getDestination() == "Cape Town"&& Flights[i]->getDeparture() == "London Heathrow")
        {
            matrix[3][0] = Flights[i]->getDistance();
            matrix[0][3] = Flights[i]->getDistance();
        }

        if (Flights[i]->getDestination() == "Sydney" && Flights[i]->getDeparture() == "Dubai International")
        {
            matrix[1][2] = Flights[i]->getDistance();
            matrix[2][1] = Flights[i]->getDistance();
        }
        if (Flights[i]->getDestination() == "Cape Town" && Flights[i]->getDeparture() == "Dubai International")
        {
            matrix[1][3] = Flights[i]->getDistance();
            matrix[3][1] = Flights[i]->getDistance();
        }
        if (Flights[i]->getDestination() == "London Heathrow" && Flights[i]->getDeparture() == "Dubai International")
        {
            matrix[1][0] = Flights[i]->getDistance();
            matrix[0][1] = Flights[i]->getDistance();
        }

        if (Flights[i]->getDestination() == "London Heathrow" && Flights[i]->getDeparture() == "Sydney")
        {
            matrix[2][0] = (Flights[i]->getDistance()+ 10000);
            matrix[0][2] = (Flights[i]->getDistance()+ 10000);
        }
        if (Flights[i]->getDestination() == "Dubai International" && Flights[i]->getDeparture() == "Sydney")
        {
            matrix[2][1] = Flights[i]->getDistance();
            matrix[1][2] = Flights[i]->getDistance();
        }
        if (Flights[i]->getDestination() == "Cape Town" && Flights[i]->getDeparture() == "Sydney")
        {
            matrix[3][2] = Flights[i]->getDistance();
            matrix[2][3] = Flights[i]->getDistance();
        }

        if (Flights[i]->getDestination() == "London Heathrow" && Flights[i]->getDeparture() == "Cape Town")
        {
            matrix[3][0] = Flights[i]->getDistance();
            matrix[0][3] = Flights[i]->getDistance();
        }
        if (Flights[i]->getDestination() == "Dubai International" && Flights[i]->getDeparture() == "Cape Town")
        {
            matrix[3][1] = Flights[i]->getDistance();
            matrix[1][3] = Flights[i]->getDistance();
        }
        if (Flights[i]->getDestination() == "Sydney" && Flights[i]->getDeparture() == "Cape Town")
        {
            matrix[3][2] = Flights[i]->getDistance();
            matrix[2][3] = Flights[i]->getDistance();
        }
    }
}

int System::getConnectingFlight(int departureAirportID, int destinationAirportID)
{
    std::vector<std::vector<float>> matrix(V, std::vector<float>(V));
    //Fill in the flight grid with the corresponding flight distances
    fillFlightGrid(matrix);

    int parent[V];
    //Run the algorithm function to fill in the parent array
    dijkstra(matrix, departureAirportID, parent);
    int parentAirportID = getParentFlight(parent,destinationAirportID);

    return parentAirportID;
}
//Get the ID of the connecting airport from the parent array and return it
int System::getParentFlight(int parent [V],int destinationAirportID)
{
    int connectingFlight = NULL;
    for (int i = 0; i < V; i++)
    {
        if (i == destinationAirportID)
        {
            connectingFlight = parent [i];
        }
    }
    return connectingFlight;
}

// A function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest path tree
// Reference:: http://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
int System::minDistance(float dist[], bool sptSet[])
{
    // Initialize min value
    float min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Funtion that implements Dijkstra's single source shortest path algorithm
// Reference:: http://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
void System::dijkstra(std::vector<std::vector<float>> &matrix, int source, int parent [V])
{
    float distance[V];  //distance[i] will hold the shortest distance from source to i

    // sptSet[i] will be true if vertex i is included / in shortest
    // path tree or shortest distance from source to i is finalized
    bool sptSet[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[0] = -1;
        distance[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    distance[source] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to source in first iteration.
        int u = minDistance(distance, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)

            // Update distance[v] only if it is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // source to v through u is smaller than current value of distance[v]
            if (!sptSet[v] && matrix[u][v] &&
                distance[u] + matrix[u][v] < distance[v])
            {
                parent[v]  = u;
                distance[v] = distance[u] + matrix[u][v];
            }
    }

}


std::vector<Flight*> System::findBothFlights(QString flightID, QString date) {

    std::vector<Flight*> flights = readFlights();
    std::vector<Airport*> airports = readAirports();

    std::vector<Flight*> bothFlights;

    QString depName, destName, connName;
    int depID, destID, connID;

    for (int i = 0; i < flights.size(); i++) {
        if (flights[i]->getID() == std::stoi(flightID.toStdString())) {
            if (flights[i]->getDistance() > 15000) {
                depName = flights[i]->getDeparture();
                destName = flights[i]->getDestination();
            }
        }
    }

    if (depName != NULL) {

        for (int j = 0; j < airports.size(); j++) {
            if (airports[j]->getName() == depName) {
                depID = airports[j]->getID();
            }
            if (airports[j]->getName() == destName) {
                destID = airports[j]->getID();
            }
        }

        connID = getConnectingFlight(depID, destID);

        for (int k = 0; k < airports.size(); k++) {
            if (airports[k]->getID() == connID) {
                connName = airports[k]->getName();
            }
        }

        std::vector<Flight*> firstFlights = searchForFlights(connName, depName, date, 1);
        std::vector<Flight*> secondFlights = searchForFlights(destName, connName, date, 1);

        for (int l = 0; l < firstFlights.size(); l++) {
            bothFlights.push_back(firstFlights[l]);
        }
        for (int l = 0; l < secondFlights.size(); l++) {
            bothFlights.push_back(secondFlights[l]);
        }

    }

    return bothFlights;
}
