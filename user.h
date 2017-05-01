#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(QString,QString,QString,QString,QString);

    void addBookedFlight(std::string str);

    //Accessor functions
    QString getEmail();
    QString getFirstName();
    QString getLastName();
    QString getPassword();
    QString getAdmin();
    QString getBookedFlights();

private:
    QString email;
    QString firstName;
    QString lastName;
    QString password;
    QString admin;
    QString bookedFlights;
};

#endif // USER_H
