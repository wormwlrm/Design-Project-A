#pragma once
#include "Mail.h"
#include "MailDelivery.h"
#include <iostream>
#include <string>
using namespace std;

class MailDelivery;
class Mail;

class User
{
protected:
	int userType; // 유저 타입( 0은 일반 고객, 1은 관리자)
	string id; //아이디
	string password; // 비밀번호

public:
	User();
	~User();

	void setUserType(int _UserType);
	void setId(string _Id);
	void setPassword(string _Password);
	int getUserType();
	string getId();
	string getPassword();

	virtual vector<Mail*>* getReceivedMail() = 0;
	virtual vector<Mail*>* getSendMail() = 0;
	virtual bool send(MailDelivery& md) = 0; // 우편물을 보내는 순수 가상 함수
	virtual bool receive(MailDelivery& md) = 0; // 우편물을 받는 순수 가상 함수
};

class Client : public User // User로부터 상속받은 Client 클래스
{
private:
	string name; // 이름
	string address; // 주소

	vector<Mail*> sendMailList; // 보낸 메일 리스트
	vector<Mail*> reciedvedMailList; // 받은 메일 리스트

public:
	Client();
	Client(int _UserType, string _Id, string _Password, string _Name, string _Address);
	~Client();

	void setName(string _name);
	void setAddress(string _address);	
	void setClient(int _UserType, string _Id, string _Password, string _Name, string _Address);
	string getName();
	string getAddress();
	void printSendedMail();

	virtual vector<Mail*>* getReceivedMail() { return &reciedvedMailList; };
	virtual vector<Mail*>* getSendMail() { return &sendMailList; };
	virtual bool send(MailDelivery& md); // 우편물 보내기
	virtual bool receive(MailDelivery& md);	 // 우편물 받기
};

class Manager : public User // User로부터 상속받은 Manager 클래스
{
public:
	Manager();
	Manager(int _UserType, string _Id, string _Password);
	~Manager();

	void setCurrentCityName(string _CurrentCityName);
	string getCurrentCityName();
	void setManager(int _UserType, string _Id, string _Password);

	
	virtual vector<Mail*>* getReceivedMail() { return NULL; };
	virtual vector<Mail*>* getSendMail() { return NULL; };
	virtual bool send(MailDelivery& md); // 우편물 보내기
	virtual bool receive(MailDelivery& md);	//우편물 받기

private:
	string currentCityName; // 현재 도시 이름
};

