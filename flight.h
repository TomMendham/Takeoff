#ifndef FLIGHT_H
#define FLIGHT_H
#include <QString>
#include <math.h>

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
    Flight();
    updateCapacity();
    int calculateDuration();
    int calculateConnectingFlight();
    float calculateDistance(float lat1, float lat2, float long1, float long2);
};

#endif // FLIGHT_H
