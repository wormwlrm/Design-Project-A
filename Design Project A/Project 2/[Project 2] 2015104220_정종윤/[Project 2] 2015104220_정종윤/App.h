#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "MailDelivery.h"
using namespace std;

class App
{
private:
	vector<User*> users;						//��ü �� �迭
	vector<MailCenter*> mailCenters;			//��ü �������߱� �迭
	int** router;								//���� ���� ���߱��� �α� �������߱��� ����Ǿ� �ִ����� Ȯ��
	User* loginedUser;							//���� �α����� ������ ����Ű�� ������ ����
	MailDelivery md;

private:
	bool loadUserFiles();						//������ ���� �ε�
	bool loadRouterFiles();
	bool loadMailCenterIdFiles();
	User* login(int userType, string input_id, string input_password);			//�α��� �Լ�
	bool logout();								//�α׾ƿ� �Լ�
//	void saveFiles();							//������ ���� ����
	void printClientMenu();						//�� �޴� ���
	void printManagerMenu();					//������ �޴� ���

public:
	App();										//���� �ε� �� ���� �ʱ�ȭ
	~App();										//�Ҹ���

	void run();									//���� ȭ�� ���
};

