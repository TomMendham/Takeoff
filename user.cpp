#include "user.h"
#include <iostream>

User::User()
{
    email = "";
    firstName = "";
    lastName = "";
    password = "";
    admin = "";
    bookedFlights = "";
}

User::User(QString _email, QString _first, QString _last, QString _password, QString _admin, QString _bookedFlights ) {
    email = _email;
    firstName = _first;
    lastName = _last;
    password = _password;
    admin = _admin;
    bookedFlights = _bookedFlights;
}

void User::addBookedFlight(QString str) {
    bookedFlights += str + ",";
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

