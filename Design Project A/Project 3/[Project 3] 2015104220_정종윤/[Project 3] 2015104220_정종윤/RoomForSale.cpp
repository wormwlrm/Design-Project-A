#include "RoomForSale.h"

RoomForSale::RoomForSale()
{

}

RoomForSale::~RoomForSale()
{

}

void RoomForSale::printRoomInfo()
{
	cout << "��������������������������������������" << endl;
	cout << "���̸� : " << getRoomName() << endl;
	cout << "��  �� : �Ÿ�" << endl;
	cout << "�Ǹ��� : " << getSellerID() << endl;
	cout << "��  ġ : " << getXCoord() << " , " << getYCoord() << endl;
	cout << "�ŸŰ� : " << getCost() << " (����)" << endl;
	cout << "��������������������������������������" << endl;
}

/////////////////////////////////////////////////////////
// get/set �Լ�
/////////////////////////////////////////////////////////

int RoomForSale::getCost()
{ 
	return cost;
}
void RoomForSale::setCost(int _cost)
{ 
	cost = _cost;
}