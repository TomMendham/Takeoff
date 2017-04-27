#include "mainwindow.h"
#include <QApplication>
#include "airport.h"
#include "xmlhandler.h"
#include "flight.h"
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<Airport*> Airports = readAirports();

    QString string = "04/07/1997";
    Flight* f = new Flight(2,string,Airports[1],Airports[2]);



    writeFlights(f);

    std::vector<Flight*> Flights = readFlights();


    std::cout << Flights[0]->getID() << std::endl;
    std::cout << Flights[1]->getID() << std::endl;



    return a.exec();
}
