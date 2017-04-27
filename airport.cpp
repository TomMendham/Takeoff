#include "airport.h"
#include <iostream>

Airport::Airport(QString cont, QString coun, QString city, QString name, QString code, float lon, float lat )
{
    Continent = cont;
    Country = coun;
    City = city;
    Name = name;
    Code = code;
    Long = lon;
    Lat = lat;
}

void Airport::printInfo() {
    std::cout << "COUNTRY: " << Country.toStdString() << std::endl;
}

QString Airport::getName() {
    return Name;
}
