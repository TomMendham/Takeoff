#include "airport.h"
#include <iostream>

Airport::Airport(QString cont, QString coun, QString city, QString name, QString code, float lat, float lon )
{
    Continent = cont;
    Country = coun;
    City = city;
    Name = name;
    Code = code;
    Lat = lat;
    Lon = lon;

}

void Airport::printInfo() {
    std::cout << "COUNTRY: " << Country.toStdString() << std::endl;
}

QString Airport::getName() {
    return Name;
}

std::pair<float, float> Airport::getCoord() {
    std::pair<float,float> pair = std::make_pair(Lat, Lon);
    return pair;
}
