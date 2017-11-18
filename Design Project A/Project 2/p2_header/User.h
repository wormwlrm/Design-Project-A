#pragma once
#include <string>
#include "mailDeilivery.h"
#include "Mail.h"
using namespace std;

class mailDeilivery;

class User
{
private:
	int userType; // 유저 타입( 0은 일반 고객, 1은 관리자)
	string id; //아이디
	string password; // 비밀번호
public:
	User();
	~User();

	virtual bool send(mailDeilivery& md) = 0; // 우편물을 보내는 순수 가상 함수
	virtual bool receive(mailDeilivery& md) = 0; // 우편물을 받는 순수 가상 함수
};

class Client : public User // User로부터 상속받은 Client 클래스
{
private:
	string name; // 이름
	string address; // 주소

	Mail* sentMailList[10]; // 보낸 메일 리스트
	Mail* reciedvedMailList[10]; // 받은 메일 리스트

public:
	Client();
	~Client();

	virtual bool send(mailDeilivery& md); // 우편물 보내기
	virtual bool receive(mailDeilivery& md);	 // 우편물 받기
};

class Manager : public User // User로부터 상속받은 Manager 클래스
{
public:
	Manager();
	~Manager();

	virtual bool send(mailDeilivery& md); // 우편물 보내기
	virtual bool receive(mailDeilivery& md);	//우편물 받기
	
private:
	string currentCityName; // 현재 도시 이름
};

