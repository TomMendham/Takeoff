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




//XML FUNCTIONS

std::vector<Airport*> System::readAirports() {
    QXmlStreamReader Rxml;


    QString cont, coun, city, name, code;
    float lon, lat;
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

                        }

                        Rxml.readNext();
                    }
                    else {
                        Rxml.readNext();
                    }
                }
            }

            if (cont != "") {
                Airport* airport = new Airport(cont, coun, city, name, code, lon, lat);
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
    float distance;

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

                        }

                        Rxml.readNext();
                    }
                    else {
                        Rxml.readNext();
                    }
                }
            }

            if (destination != "") {
                Flight* flight = new Flight(ID, capacity, destination, departure, duration, date, distance);
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


    QString email, firstname, lastname, password, admin;

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


                        }

                        Rxml.readNext();
                    }
                    else {
                        Rxml.readNext();
                    }
                }
            }

            if (email != "") {
                User* user = new User(email, firstname, lastname, password, admin);
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


                //close user tag
                xmlWriter.writeEndElement();


            }


            //end users tag
            xmlWriter.writeEndElement();
            //end document
            xmlWriter.writeEndDocument();
       }


}
