#pragma once
#include <string>
using namespace std;

class User
{
public:
	User(); //�⺻ ������
	~User();	//�Ҹ���

	virtual void printUserInfo() = 0;	//������ ����ϴ� ���� �����Լ�
private:
	int userType;	//���� Ÿ��
	string id;	//���̵�
	string password;	//�н�����

	
};

