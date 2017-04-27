#include "user.h"

User::User()
{

}

User::User(QString _email, QString _first, QString _last, QString _password, bool _admin ){
    email = _email;
    firstName = _first;
    lastName = _last;
    password = _password;
    admin = _admin;
}
