#pragma once
#include <string>
#include <vector>
using namespace std;

class User
{
public:
	User(); //�⺻ ������
	~User();	//�Ҹ���

	virtual void printUserInfo() = 0;	//������ ����ϴ� ���� �����Լ�

	int getUserType();
	string getId();
	string getPassword();

	void setUserType(int _userType);
	void setId(string _id);
	void setPassword(string _password);


private:
	int userType;	//���� Ÿ��
	string id;	//���̵�
	string password;	//�н�����

	
};

