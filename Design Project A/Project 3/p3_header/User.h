#pragma once
#include <string>
using namespace std;

class User
{
public:
	User(); //기본 생성자
	~User();	//소멸자

	virtual void printUserInfo() = 0;	//정보를 출력하는 순수 가상함수
private:
	int userType;	//유저 타입
	string id;	//아이디
	string password;	//패스워드

	
};

