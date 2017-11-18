#pragma once
#include <iostream>
#include "Room.h"
class RoomForSale : 
	public Room
{
public:
	RoomForSale(); // 기본 생성자
	~RoomForSale(); // 소멸자

	virtual void printRoomInfo(); // 방 정보 출력

	int getCost();
	void setCost(int _cost);
private:
	int cost; // 매매가

	
};

