#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MailDelivery.h"
using namespace std;

class App
{
private:
	vector<User*> users;						//전체 고객 배열
	vector<MailCenter*> mailCenters;			//전체 우편집중국 배열
	int** router;								//현재 우편 집중국이 인근 우편집중국과 연결되어 있는지를 확인
	User* loginedUser;							//현재 로그인한 유저를 가리키는 포인터 변수
	MailDelivery md;

private:
	bool loadUserFiles();						//데이터 파일 로드
	bool loadRouterFiles();
	bool loadMailCenterIdFiles();
	User* login(int userType, string input_id, string input_password);			//로그인 함수
	bool logout();								//로그아웃 함수
//	void saveFiles();							//데이터 파일 저장
	void printClientMenu();						//고객 메뉴 출력
	void printManagerMenu();					//관리자 메뉴 출력

public:
	App();										//파일 로드 및 변수 초기화
	~App();										//소멸자

	void run();									//시작 화면 출력
};

