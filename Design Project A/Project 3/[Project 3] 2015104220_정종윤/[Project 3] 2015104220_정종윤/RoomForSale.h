#pragma once
#include <iostream>
#include "Room.h"
class RoomForSale : 
	public Room
{
public:
	RoomForSale(); // �⺻ ������
	~RoomForSale(); // �Ҹ���

	virtual void printRoomInfo(); // �� ���� ���

	int getCost();
	void setCost(int _cost);
private:
	int cost; // �ŸŰ�

	
};

