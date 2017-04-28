#include "user.h"

User::User()
{

}

User::User(QString _email, QString _first, QString _last, QString _password, QString _admin ){
    email = _email;
    firstName = _first;
    lastName = _last;
    password = _password;
    admin = _admin;
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

