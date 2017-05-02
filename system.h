#ifndef SYSTEM_H
#define SYSTEM_H


#include "airport.h"
#include "flight.h"
#include "user.h"
#include <vector>

// Number of vertices in the matrix in our case number of airports
#define V 4

class System
{

public:
    System();

    User* checkLogin(QString user, QString pass);
    std::vector<Flight*> searchForFlights(QString dest, QString dep, QString date, int diff);

    //XML FUNCTIONS
    std::vector<Airport*> readAirports();
    std::vector<Flight*> readFlights();
    std::vector<User*> readUsers() ;

    void writeFlights(Flight* f);
    void writeUsers(User* u);
    void editUsers(QString email, QString str);
    void editFlights(QString id);

    //Connecting flight functions
    int getConnectingFlight(int departureAirportID, int destinationAirportID);
    void fillFlightGrid(std::vector<std::vector<float>> &matrix);
    int getParentFlight(int parent [V],int destinationAirportID);
    int minDistance(float dist[], bool sptSet[]);
    void dijkstra(std::vector<std::vector<float>> &matrix, int src, int parent [V]);

    std::vector<Flight*> findBothFlights(QString flightID, QString date);

};

#endif // SYSTEM_H
