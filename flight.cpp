#include "flight.h"
#include "airport.h"
#include <cmath>

Flight::Flight(int id, QString dest, QString dep, QString dat, Airport a1, Airport a2)
{
    ID = id;
    capacity = 0;
    destination = dest;
    departure = dep;
    date = dat;
    distance = calculateDistance(a1, a2);
}

float Flight::calculateDistance(Airport a1, Airport a2)
float Flight::calculateDistance(float lat1, float lat2, float long1, float long2)
{
    std::pair <float, float> a1coord, a2coord ;

    a1coord = a1.getCoord;
    a2coord = a2.getCoord;
    //a1coord.first = radLat1
    //a1coord.second = radLon1
    //a2coord.first = radLat2
    //a2coord.second = radLon2

    //R is earths mean radius in km
    float R = 6371;
    //Converting to radians "*M_PI / 180.0"
    float radLat1 = (lat1*M_PI / 180.0);
    float radLon1 = (long1*M_PI / 180.0);
    float radLat2 = (lat2*M_PI / 180.0);
    float radLon2 = (long2*M_PI / 180.0);
    //Calculating Distance
    double u = sin((radLat2 - radLat1)/2);
    double v = sin((radLon2 - radLon1)/2);

    float d = 2 * R * asin(sqrt(u * u + cos(radLat1) * cos(radLat2) * v * v));
    return d;
}

Flight::updateCapacity()
{

}

Flight::calculateDuration()
{

}

Flight::calculateConnectingFlight()
{

}
