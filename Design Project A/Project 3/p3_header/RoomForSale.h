#pragma once
#include "Room.h"
class RoomForSale : 
	public Room
{
public:
	RoomForSale(); // �⺻ ������
	~RoomForSale(); // �Ҹ���

	virtual void printRoomInfo(); // �� ���� ���
private:
	int cost; // �ŸŰ�

	
};

