#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include "airport.h"
#include "flight.h"
#include "user.h"


std::vector<Airport*> readAirports();
std::vector<Flight*> readFlights();
std::vector<User*> readUsers() ;

void writeFlights(Flight* f);
void writeUsers(User* u);

#endif // XMLHANDLER_H
