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

public:
    Airport(QString cont, QString coun, QString city, QString name, QString code, float lon, float lat );
    void printInfo();
    QString getName();
    std::pair<float, float> getCoord();
};

#endif // AIRPORT_H
