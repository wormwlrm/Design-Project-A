#pragma once
#include "Seller.h"
#include "Buyer.h"
#include "RoomForRent.h"
#include "RoomForSale.h"
#include <vector>
using namespace std;

class App
{
public:
	App();	//기본 생성자
	~App();	//소멸자

	void run();	//프로그램 시행
private:
	vector<User*> users;	//유저 벡터
	vector<Room*> rooms;	//방 벡터

	User* loginedUser;	//로그인 유저

	vector<Room*> reusltOfFilter1, resultOfFilter2;   //조건1, 2에 대한 필터링을 수행한 임시 검색 결과
	int searchAreaRadius;    //사용자 중심으로 검색할 범위(거리)
	bool isFilter1Skipped, istFilter2Skipped, isFilter3Skipped;  //필터링을 수행할 것인지 저장하는 변수들
	int minDeposit, maxDeposit;     //필터링에 사용될 보증금의 범위를 저장하는 변수들
	int minMonthlyPay, maxMonthlyPay;	//필터링에 사용될 월세의 범위를 저장하는 변수들
	int minCost, maxCost;	//필터링에 사용될 매매가의 범위를 저장하는 변수들
	                 
	vector<Room*> getFilter1Result();	// 필터1 반환 함수
	vector<Room*> getFilter2Result();	// 필터2 반환 함수
	vector<Room*> getFilter3Result();	// 필터3 반환 함수

	void loadUserFile();	//유저 데이터 로드
	void loadRoomFile();	//방 데이터 로드
	void saveFiles();	//파일 저장

	void run();	//프로그램 시행
	void printMenu();	//메뉴 출력

	bool login(string userID, string password);	//로그인
	bool logout();	//로그아웃
	
	void printRecentlySearcedRoomsOfLoginedUser();	//최근 검색 내역 출력
	Room* getRoomByID(int _roomID);	//ID를 이용해 Room 반환
	bool printFilterConditions();    //현재 필터들의 설정을 출력
	void searchRooms();	//방 검색
	void registerNewRoom(); // 방 등록
	void deleteRoom();	//방 삭제
};

