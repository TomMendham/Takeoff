#include "mainwindow.h"
#include <QApplication>
#include "airport.h"
#include "xmlhandler.h"
#include "flight.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    std::vector<Airport*> Airports = readAirports();

    QString string = "02/05/1997";
    Flight f = Flight(1,string,Airports[0],Airports[1]);
    return a.exec();
}
