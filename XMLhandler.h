#ifndef XMLHANDLER_H
#define XMLHANDLER_H

#include "airport.h"
#include "flight.h"


std::vector<Airport*> readAirports();

std::vector<Flight*> readFlights();

void writeFlights(Flight* f);


#endif // XMLHANDLER_H
