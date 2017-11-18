#pragma once
#include <string>
#include <vector>
using namespace std;

class User
{
public:
	User(); //기본 생성자
	~User();	//소멸자

	virtual void printUserInfo() = 0;	//정보를 출력하는 순수 가상함수

	int getUserType();
	string getId();
	string getPassword();

	void setUserType(int _userType);
	void setId(string _id);
	void setPassword(string _password);


private:
	int userType;	//유저 타입
	string id;	//아이디
	string password;	//패스워드

	
};

