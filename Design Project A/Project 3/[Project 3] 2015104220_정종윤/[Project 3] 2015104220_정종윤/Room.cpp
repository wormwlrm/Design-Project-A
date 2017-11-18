#include "Room.h"

Room::Room()
{

}

Room::~Room()
{

}

bool Room::addUserInRequestToBuyList(string _userID)
{
	return 0;
}


/////////////////////////////////////////////////////////
// get/set ÇÔ¼ö
/////////////////////////////////////////////////////////


int Room::getRoomType()
{
	return roomType; 
}

int Room::getRoomID()
{
	return roomID; 
}

string Room::getSellerID()
{
	return sellerID; 
}

string Room::getRoomName()
{ 
	return roomName;
}

int Room::getXCoord()
{ 
	return xCoord;
}

int Room::getYCoord()
{
	return yCoord;
}

vector<string>* Room::getUsersRequestToBuyList()
{ 
	return &usersRequestToBuyList;
}

void Room::setRoomType(int _roomType)
{
	roomType = _roomType;
}

void Room::setRoomID(int _roomID)
{
	roomID = _roomID; 
}

void Room::setSellerID(string _sellerID)
{ 
	sellerID = _sellerID;
}

void Room::setRoomName(string _roomName)
{ 
	roomName = _roomName; 
}

void Room::setXCoord(int _X)
{ 
	xCoord = _X; 
}

void Room::setYCoord(int _Y)
{ 
	yCoord = _Y;
}