#pragma once
#include <iostream>
#include "Room.h"
class RoomForRent :
	public Room
{
public:
	RoomForRent(); // 기본 생성자
	~RoomForRent(); // 소멸자
	virtual void printRoomInfo(); // 방 정보 출력

	int getDeposit();
	int getMonthlyPay();

	void setDeposit(int _deposit);
	void setMonthlyPay(int _monthlyPay);
private:
	int deposit; // 보증금
	int monthlyPay; // 월세

	
};

