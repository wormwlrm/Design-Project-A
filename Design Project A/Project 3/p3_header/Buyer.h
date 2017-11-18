#pragma once
#include "User.h"
#include <list>
class Buyer :
	public User
{
public:
	Buyer();	//기본 생성자
	~Buyer();	//소멸자
	bool addRoomIDToRecentlySearched(int _roomID);	//최근 검색 내역에 추가
	bool addRoomIDToRequestToBuy(int _roomID);	//구매 요청 내역에 추가

	virtual void printUserInfo();	//구매자 정보 출력

private:
	int xCoord, yCoord;	//구매자의 좌표
	list<int> recentlySearched;	//최근 검색 내역 리스트
	list<int> roomsRequestToBuy; //구매 요청 내역 리스트

	
};

