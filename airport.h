#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>
#include <utility>

class Airport
{

private:
    QString Continent;
    QString Country;
    QString City;
    QString Name;
    QString Code;
    float Lon;
    float Lat;
    int ID;

public:
    Airport(QString cont, QString coun, QString city, QString name, QString code, float lon, float lat, int id );
    void printInfo();
    QString getName();
    QString getCountry();
    int getID();
    std::pair<float, float> getCoord();
};

#endif // AIRPORT_H
