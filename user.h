#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(QString,QString,QString,QString,QString);


    //Accessor functions
    QString getEmail();
    QString getFirstName();
    QString getLastName();
    QString getPassword();
    QString getAdmin();

private:
    QString email;
    QString firstName;
    QString lastName;
    QString password;
    QString admin;
};

#endif // USER_H
