#pragma once
#include "Mail.h"
class MailCenter
{
private:
	int id;	//�������߱� ID
	string cityName;//���� �̸�
	int neighborCnt;//������ �������߱� ����
	int* neighborIds;//

	Mail* recievedMailList[10];//���� ���� ����Ʈ
	Mail* localMailList[10];//���η� �߼۵� ���� ����Ʈ
	Mail*** externalMailList;//�ܺη� �߼۵� ���� ����Ʈ
public:
	MailCenter();
	~MailCenter();
};

