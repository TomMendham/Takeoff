#include "user.h"
#include <iostream>

User::User()
{

}

User::User(QString _email, QString _first, QString _last, QString _password, QString _admin ) {
    email = _email;
    firstName = _first;
    lastName = _last;
    password = _password;
    admin = _admin;
    bookedFlights = ",";
}

void User::addBookedFlight(std::string str) {
    bookedFlights += QString::fromStdString(str) + ","; 
    std::cout << bookedFlights.toStdString() << std::endl;
}


//Accessor functions
QString User::getEmail() {
    return email;
}

QString User::getFirstName() {
    return firstName;
}

QString User::getLastName() {
    return lastName;
}

QString User::getPassword() {
    return password;
}

QString User::getAdmin() {
    return admin;
}

QString User::getBookedFlights() {
    return bookedFlights;
}

