#include <QCoreApplication>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QXmlStreamReader>
#include <iostream>
#include "airport.h"
#include "XMLhandler.h"
#include <QDir>

std::vector<Airport*> readAirports() {
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
