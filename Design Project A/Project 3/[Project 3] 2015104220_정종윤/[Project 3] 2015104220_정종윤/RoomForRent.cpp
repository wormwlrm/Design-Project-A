#include "RoomForRent.h"

RoomForRent::RoomForRent()
{

}

RoomForRent::~RoomForRent()
{

}

void RoomForRent::printRoomInfo()
{
	cout << "───────────────────" << endl;
	cout << "방이름 : " << getRoomName() << endl;
	cout << "매  물 : 월세" << endl;
	cout << "판매자 : " << getSellerID() << endl;
	cout << "위  치 : " << getXCoord() << " , " << getYCoord() << endl;
	cout << "보증금 : " << getDeposit() << " (만원)" << endl;
	cout << "월  세 : " << getMonthlyPay() << " (만원)" << endl;
	cout << "───────────────────" << endl;
}

/////////////////////////////////////////////////////////
// get/set 함수
/////////////////////////////////////////////////////////

int RoomForRent::getDeposit()
{
	return deposit; 
}

int RoomForRent::getMonthlyPay()
{ 
	return monthlyPay;
}

void RoomForRent::setDeposit(int _deposit)
{
	deposit = _deposit; 
}

void RoomForRent::setMonthlyPay(int _monthlyPay)
{
	monthlyPay = _monthlyPay; 
}