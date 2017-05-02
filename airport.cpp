#include "airport.h"
#include <iostream>

Airport::Airport(QString cont, QString coun, QString city, QString name, QString code, float lat, float lon, int id )
{
    Continent = cont;
    Country = coun;
    City = city;
    Name = name;
    Code = code;
    Lat = lat;
    Lon = lon;
    ID = id;
}


QString Airport::getName() {
    return Name;
}

QString Airport::getCountry() {
    return Country;
}

std::pair<float, float> Airport::getCoord() {
    std::pair<float,float> pair = std::make_pair(Lat, Lon);
    return pair;
}

int Airport::getID() {
    return ID;
}
