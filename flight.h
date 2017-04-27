#ifndef FLIGHT_H
#define FLIGHT_H
#include <QString>
#include <math.h>
#include "airport.h"

class Flight
{

private:
    int ID;
    int capacity;
    QString destination;
    QString departure;
    int duration;
    QString date;
    float distance;
    bool isConnectingFlight;
public:
    Flight(int id, QString dat, Airport *a1, Airport *a2);
    //updateCapacity();
    int calculateDuration();
    int calculateConnectingFlight();
    float calculateDistance(Airport* a1, Airport* a2);
};

#endif // FLIGHT_H
