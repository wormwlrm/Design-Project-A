#pragma once
#include "User.h"
#include <list>

class Seller :
	public User
{
public:
	Seller(); // 기본 생성자
	~Seller(); // 소멸자

	void addRoomIDToRegisteredRoomList(int _roomID);	//iD를 이용해 방 추가
	virtual void printUserInfo();	//판매자 정보 출력

private:
	list<int> registerdRoomList;	//등록한 방 리스트
};

