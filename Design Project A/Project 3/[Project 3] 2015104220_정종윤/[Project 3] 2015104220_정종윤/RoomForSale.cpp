#include "RoomForSale.h"

RoomForSale::RoomForSale()
{

}

RoomForSale::~RoomForSale()
{

}

void RoomForSale::printRoomInfo()
{
	cout << "───────────────────" << endl;
	cout << "방이름 : " << getRoomName() << endl;
	cout << "매  물 : 매매" << endl;
	cout << "판매자 : " << getSellerID() << endl;
	cout << "위  치 : " << getXCoord() << " , " << getYCoord() << endl;
	cout << "매매가 : " << getCost() << " (만원)" << endl;
	cout << "───────────────────" << endl;
}

/////////////////////////////////////////////////////////
// get/set 함수
/////////////////////////////////////////////////////////

int RoomForSale::getCost()
{ 
	return cost;
}
void RoomForSale::setCost(int _cost)
{ 
	cost = _cost;
}