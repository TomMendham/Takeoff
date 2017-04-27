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

public:
    Flight(int id, QString dat, Airport *a1, Airport *a2);
    Flight(int id, int capac, QString dest, QString dep, int dur, QString dat, float dist);

    float calculateDistance(Airport* a1, Airport* a2);

    //Accessor functions
    int getID();
    int getCapacity();
    QString getDestination();
    QString getDeparture();
    int getDuration();
    QString getDate();
    float getDistance();

    //    updateCapacity();
    //    int calculateDuration();
    //    int calculateConnectingFlight();
};

#endif // FLIGHT_H
