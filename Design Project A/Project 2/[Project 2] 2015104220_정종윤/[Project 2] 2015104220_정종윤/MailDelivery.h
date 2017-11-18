#pragma once
#include "MailCenter.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "User.h"
using namespace std;

#define N 12
#define IN 99 
//IN = INTMAX

class User;
class MailCenter;
class MailDelivery
{
private:
	vector<User*>* pointerOfUsers;//고객을 가리키는 포인터
	vector<MailCenter*>* pointerOfMailCenters;//우편집중국을 가리키는 포인터
	int** pointerOfRouter;//경로를 가리키는 포인터

public:
	MailDelivery();
	~MailDelivery();

	bool clientSendMail(User* curUser, Mail* mail);//고객의 우편물 보내기
	bool managerSendMail(string cityName);//관리자의 우편물 보내기
	bool managerReceiveMail(string cityName);//관리자의 우편물 받기

	vector<User*>* getpointerOfUsers() {return pointerOfUsers; };
	int getTotalDistance(int sourceId, int destinationId);//출발지에서 목적지까지 총 이동 횟수를 계산하여 반환
	int getNextMailCenterId(int currentPos, int destinationId);//현재 우편집중국에서 목적지 우편집까지 가는 경로의 다음 우편집중국 ID를 받아옴
	int getMailCenterIdByCityName(string cityName);//도시 이름을 이용해 ID를 받아옴
	int getMailCenterIdByAddress(string address);
	string getCityNameByMailCenterId(int id);

	void setDBPointers(vector<User*>* pUser, vector<MailCenter*>* pMailCenter, int** pRouter)//App 클래스에 저장된 데이터들의 주소값을 복사해옴
	{
		pointerOfUsers = pUser;
		pointerOfMailCenters = pMailCenter;
		pointerOfRouter = pRouter;
	}
};

