#include "RoomForRent.h"

RoomForRent::RoomForRent()
{

}

RoomForRent::~RoomForRent()
{

}

void RoomForRent::printRoomInfo()
{
	cout << "��������������������������������������" << endl;
	cout << "���̸� : " << getRoomName() << endl;
	cout << "��  �� : ����" << endl;
	cout << "�Ǹ��� : " << getSellerID() << endl;
	cout << "��  ġ : " << getXCoord() << " , " << getYCoord() << endl;
	cout << "������ : " << getDeposit() << " (����)" << endl;
	cout << "��  �� : " << getMonthlyPay() << " (����)" << endl;
	cout << "��������������������������������������" << endl;
}

/////////////////////////////////////////////////////////
// get/set �Լ�
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