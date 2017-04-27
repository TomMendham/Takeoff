#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(QString,QString,QString,QString,bool);
private:
    QString email;
    QString firstName;
    QString lastName;
    QString password;
    bool admin;
};

#endif // USER_H
