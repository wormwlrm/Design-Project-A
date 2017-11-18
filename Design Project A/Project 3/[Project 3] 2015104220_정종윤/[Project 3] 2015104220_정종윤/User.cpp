#include "User.h"

User::User()
{
	userType = 0;
	id = "";
	password = "";
}

User::~User()
{

}

/////////////////////////////////////////////////////////
// get/set ÇÔ¼ö
/////////////////////////////////////////////////////////

int User::getUserType()
{
	return userType;
}

string User::getId()
{
	return id;
}

string User::getPassword()
{
	return password;
}

void User::setUserType(int _userType)
{
	userType = _userType;
}

void User::setId(string _id)
{
	id = _id;
}

void User::setPassword(string _password)
{
	password = _password;
}