#pragma once
#include "Mail.h"
#include <vector>
#include <string>
using namespace std;

class Mail;

class MailCenter
{
private:
	int id;								//우편집중국 ID
	string cityName; 					//도시 이름
	int neighborCnt; 					//인접한 우편집중국 개수
	int* neighborIds; 					//인접한 우편집중국 아이디

	vector<Mail*> sendMailList;			//보낸 우편물 리스트
	vector<Mail*> recievedMailList; 	//받은 우편물 리스트
	vector<Mail*> localMailList; 		//내부로 발송될 우편물 리스트
	vector<Mail*> externalMailList; 	//외부로 발송될 우편물 리스트
	
public:
	MailCenter();
	MailCenter(int _Id, string _CityName);
	~MailCenter();

	void setId(int _Id);
	void setCityName(string _CityName);
	int getId();
	string getCityName();
	vector<Mail*>* getreceivedMailList() { return &recievedMailList; };
	vector<Mail*>* getlocalMailList() { return &localMailList; };
	vector<Mail*>* getExternalMailList() { return &externalMailList; };

};
