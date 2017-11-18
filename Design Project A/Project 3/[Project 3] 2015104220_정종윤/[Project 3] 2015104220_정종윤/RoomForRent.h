#pragma once
#include <iostream>
#include "Room.h"
class RoomForRent :
	public Room
{
public:
	RoomForRent(); // �⺻ ������
	~RoomForRent(); // �Ҹ���
	virtual void printRoomInfo(); // �� ���� ���

	int getDeposit();
	int getMonthlyPay();

	void setDeposit(int _deposit);
	void setMonthlyPay(int _monthlyPay);
private:
	int deposit; // ������
	int monthlyPay; // ����

	
};

