#pragma once
#include <fstream>
#include <string>
using namespace std;

#include "User.h"
#include "Mail.h"
#include "MailCenter.h"
#include "mailDeilivery.h"

class App
{
private:
	User* users[36];				//��ü �� �迭
	MailCenter mailCenters[12];		//��ü �������߱� �迭
	int** router;					//���� ���� ���߱��� �α� �������߱��� ����Ǿ� �ִ����� Ȯ��

	User* loginedUser;				//���� �α����� ������ ����Ű�� ������ ����

private:
	bool load_files();				//������ ���� �ε�
	bool login();					//�α��� �Լ�
	bool logout();					//�α׾ƿ� �Լ�
	void saveFiles();				//������ ���� ����
	void printClientMenu();			//�� �޴� ���
	void printManagerMenu();		//������ �޴� ���
public:
	App();							//���� �ε� �� ���� �ʱ�ȭ
	~App();							//�Ҹ���

	void run();						//���� ȭ�� ���
};

