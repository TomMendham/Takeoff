#ifndef AIRPORT_H
#define AIRPORT_H

#include <QString>

class Airport
{

private:
    QString Continent;
    QString Country;
    QString City;
    QString Name;
    QString Code;
    float Long;
    float Lat;

public:
    Airport(QString cont, QString coun, QString city, QString name, QString code, float lon, float lat );
    printInfo();
};

#endif // AIRPORT_H
