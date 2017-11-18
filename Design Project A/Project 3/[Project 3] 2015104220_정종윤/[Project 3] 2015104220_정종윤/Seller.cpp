#include "Seller.h"

Seller::Seller()
{

}

Seller::~Seller()
{

}

void Seller::addRoomIDToRegisteredRoomList(int _roomID)
{

}

void Seller::printUserInfo()
{
	cout << " I D  : " << getId() << endl;
}

/////////////////////////////////////////////////////////
// get/set ÇÔ¼ö
/////////////////////////////////////////////////////////

vector<int>* Seller::getRegisteredRoomList()
{
	return &registerdRoomList;
}