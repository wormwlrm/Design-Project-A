#include "Buyer.h"

Buyer::Buyer()
{

}

Buyer::~Buyer()
{

}

bool Buyer::addRoomIDToRecentlySearched(int _roomID)
{
	return 0;
}

bool Buyer::addRoomIDToRequestToBuy(int _roomID)
{
	return 0;
}

void Buyer::printUserInfo()
{
	cout << " I D  : " << getId() << endl;
	cout << " ÁÂÇ¥ : " << getXCoord() << " , " << getYCoord() << endl;
}


/////////////////////////////////////////////////////////
// get/set ÇÔ¼ö
/////////////////////////////////////////////////////////

int Buyer::getXCoord()
{
	return xCoord;
}

int Buyer::getYCoord()
{ 
	return yCoord;
}

vector<int>* Buyer::getRecentlySearched()
{
	return &recentlySearched;
}

vector<int>* Buyer::getRoomsRequestToBuy()
{
	return &roomsRequestToBuy;
}

void Buyer::setXCoord(int _X)
{
	xCoord = _X; 
}

void Buyer::setYCoord(int _Y)
{ 
	yCoord = _Y; 
}