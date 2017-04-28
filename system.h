#ifndef SYSTEM_H
#define SYSTEM_H


#include "airport.h"
#include "flight.h"
#include "user.h"


class System
{

public:
    System();

    User* checkLogin(QString user, QString pass);
    std::vector<Flight*> searchForFlights(QString dest, QString dep, QString date);

    //XML FUNCTIONS
    std::vector<Airport*> readAirports();
    std::vector<Flight*> readFlights();
    std::vector<User*> readUsers() ;

    void writeFlights(Flight* f);
    void writeUsers(User* u);
};

#endif // SYSTEM_H
