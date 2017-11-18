#pragma once
#include <fstream>
#include <string>
using namespace std;

#include "User.h"
#include "Mail.h"
#include "MailCenter.h"
#include "mailDeilivery.h"

class App
{
private:
	User* users[36];				//전체 고객 배열
	MailCenter mailCenters[12];		//전체 우편집중국 배열
	int** router;					//현재 우편 집중국이 인근 우편집중국과 연결되어 있는지를 확인

	User* loginedUser;				//현재 로그인한 유저를 가리키는 포인터 변수

private:
	bool load_files();				//데이터 파일 로드
	bool login();					//로그인 함수
	bool logout();					//로그아웃 함수
	void saveFiles();				//데이터 파일 저장
	void printClientMenu();			//고객 메뉴 출력
	void printManagerMenu();		//관리자 메뉴 출력
public:
	App();							//파일 로드 및 변수 초기화
	~App();							//소멸자

	void run();						//시작 화면 출력
};

