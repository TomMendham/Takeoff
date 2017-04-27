#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(QString,QString,QString,QString,bool);


    //Accessor functions
    QString getEmail();
    QString getFirstName();
    QString getLastName();
    QString getPassword();
    bool getAdmin();

private:
    QString email;
    QString firstName;
    QString lastName;
    QString password;
    bool admin;
};

#endif // USER_H
