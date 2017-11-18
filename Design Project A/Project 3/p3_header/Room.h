#pragma once
#include <list>
#include <string>
using namespace std;

class Room
{
public:
	Room(); // 기본 생성자
	~Room(); // 소멸자
	bool addUserInRequestToBuyList(string _userID); // 유저ID를 이용해 구매 요청 리스트에 추가
	virtual void printRoomInfo() = 0; // 정보를 출력하는 순수 가상 함수

private:
	int roomType; // 방 타입
	int roomID;	// 방 ID
	int sellerID; // 판매자 ID
	string roomName; // 방 이름
	int xCoord, yCoord; // 좌표
	list<string> usersRequestToBuyList; // 구매 요청한 유저 ID 리스트

	
};

