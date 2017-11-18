#include "MailCenter.h"


MailCenter::MailCenter()
{
}


MailCenter::~MailCenter()
{
}

MailCenter::MailCenter(int _Id, string _CityName)
{
	id = _Id;
	cityName = _CityName;
}

void MailCenter::setId(int _Id){ id = _Id; }
void MailCenter::setCityName(string _CityName){ cityName = _CityName; }
int MailCenter::getId(){ return id; }
string MailCenter::getCityName(){ return cityName; }