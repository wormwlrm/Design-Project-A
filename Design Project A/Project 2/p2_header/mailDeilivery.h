#pragma once
#include "User.h"
#include "MailCenter.h"

#include <iostream>
#include <sstream>
using namespace std;

#define N 12
#define IN 99 
//IN = INTMAX

class User;

class mailDeilivery
{
private:
	User** pointerOfUsers;//���� ����Ű�� ������
	MailCenter* pointerOfMailCenters;//�������߱��� ����Ű�� ������
	int** pointerOfRouter;//��θ� ����Ű�� ������

	int getTotalDistance(int sourceId, int destinationId);//��������� ���������� �� �̵� Ƚ���� ����Ͽ� ��ȯ
	int getNextMailCenterId(int currentPos, int destinationId);//���� �������߱����� ������ ���������� ���� ����� ���� �������߱� ID�� �޾ƿ�
	int getMailCenterIdByCityName(string cityName);//���� �̸��� �̿��� ID�� �޾ƿ�

public:
	mailDeilivery();
	~mailDeilivery();
	
	bool clientSendMail(User* curUser);//���� ���� ������
	bool managerSendMail(string cityName);//�������� ���� ������
	bool managerReceiveMail(string cityName);//�������� ���� �ޱ�

	void setDBPointers(User** pUser, MailCenter* pMailCenter, int** pRouter)//App Ŭ������ ����� �����͵��� �ּҰ��� �����ؿ�
	{ 
		pointerOfUsers = pUser; 
		pointerOfMailCenters = pMailCenter;
		pointerOfRouter = pRouter;
	}
};

