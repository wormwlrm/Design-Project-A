#pragma once
#include "Room.h"
class RoomForRent :
	public Room
{
public:
	RoomForRent(); // �⺻ ������
	~RoomForRent(); // �Ҹ���
	virtual void printRoomInfo(); // �� ���� ���
private:
	int deposit; // ������
	int monthlyPay; // ����

	
};

