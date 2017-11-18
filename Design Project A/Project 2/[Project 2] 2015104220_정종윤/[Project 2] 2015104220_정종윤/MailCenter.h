#pragma once
#include "Mail.h"
#include <vector>
#include <string>
using namespace std;

class Mail;

class MailCenter
{
private:
	int id;								//�������߱� ID
	string cityName; 					//���� �̸�
	int neighborCnt; 					//������ �������߱� ����
	int* neighborIds; 					//������ �������߱� ���̵�

	vector<Mail*> sendMailList;			//���� ���� ����Ʈ
	vector<Mail*> recievedMailList; 	//���� ���� ����Ʈ
	vector<Mail*> localMailList; 		//���η� �߼۵� ���� ����Ʈ
	vector<Mail*> externalMailList; 	//�ܺη� �߼۵� ���� ����Ʈ
	
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
