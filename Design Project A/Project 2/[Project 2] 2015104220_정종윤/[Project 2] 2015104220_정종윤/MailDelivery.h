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
	vector<User*>* pointerOfUsers;//���� ����Ű�� ������
	vector<MailCenter*>* pointerOfMailCenters;//�������߱��� ����Ű�� ������
	int** pointerOfRouter;//��θ� ����Ű�� ������

public:
	MailDelivery();
	~MailDelivery();

	bool clientSendMail(User* curUser, Mail* mail);//���� ���� ������
	bool managerSendMail(string cityName);//�������� ���� ������
	bool managerReceiveMail(string cityName);//�������� ���� �ޱ�

	vector<User*>* getpointerOfUsers() {return pointerOfUsers; };
	int getTotalDistance(int sourceId, int destinationId);//��������� ���������� �� �̵� Ƚ���� ����Ͽ� ��ȯ
	int getNextMailCenterId(int currentPos, int destinationId);//���� �������߱����� ������ ���������� ���� ����� ���� �������߱� ID�� �޾ƿ�
	int getMailCenterIdByCityName(string cityName);//���� �̸��� �̿��� ID�� �޾ƿ�
	int getMailCenterIdByAddress(string address);
	string getCityNameByMailCenterId(int id);

	void setDBPointers(vector<User*>* pUser, vector<MailCenter*>* pMailCenter, int** pRouter)//App Ŭ������ ����� �����͵��� �ּҰ��� �����ؿ�
	{
		pointerOfUsers = pUser;
		pointerOfMailCenters = pMailCenter;
		pointerOfRouter = pRouter;
	}
};

