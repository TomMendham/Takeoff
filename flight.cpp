#include "flight.h"
#include "airport.h"
#include <cmath>
#include <iostream>

Flight::Flight(int id, QString dat, Airport* a1, Airport* a2)
{
    ID = id;
    capacity = 0;
    destination = a2->getName();
    departure = a1->getName();
    date = dat;
    distance = calculateDistance(a1, a2);
}

float Flight::calculateDistance(Airport* a1, Airport* a2)
{
    std::pair <float, float> a1coord, a2coord ;

    a1coord = a1->getCoord();
    a2coord = a2->getCoord();
    //a1coord.first = lat1
    //a1coord.second = lon1
    //a2coord.first = lat2
    //a2coord.second = lon2

    //R is earths mean radius in km
    float R = 6371;
    //Converting to radians "*M_PI / 180.0"
    float radLat1 = (a1coord.first*M_PI / 180.0);
    float radLon1 = (a1coord.second*M_PI / 180.0);
    float radLat2 = (a2coord.first*M_PI / 180.0);
    float radLon2 = (a2coord.second*M_PI / 180.0);
    //Calculating Distance
    double u = sin((radLat2 - radLat1)/2);
    double v = sin((radLon2 - radLon1)/2);

    float d = 2 * R * asin(sqrt(u * u + cos(radLat1) * cos(radLat2) * v * v));
    std::cout << "D: " << d << std::endl;
    return d;
}

//Flight::updateCapacity()
//{

//}

int Flight::calculateDuration()
{

}

int Flight::calculateConnectingFlight()
{

}
