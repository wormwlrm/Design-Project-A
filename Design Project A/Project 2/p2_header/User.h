#pragma once
#include <string>
#include "mailDeilivery.h"
#include "Mail.h"
using namespace std;

class mailDeilivery;

class User
{
private:
	int userType; // ���� Ÿ��( 0�� �Ϲ� ��, 1�� ������)
	string id; //���̵�
	string password; // ��й�ȣ
public:
	User();
	~User();

	virtual bool send(mailDeilivery& md) = 0; // ������ ������ ���� ���� �Լ�
	virtual bool receive(mailDeilivery& md) = 0; // ������ �޴� ���� ���� �Լ�
};

class Client : public User // User�κ��� ��ӹ��� Client Ŭ����
{
private:
	string name; // �̸�
	string address; // �ּ�

	Mail* sentMailList[10]; // ���� ���� ����Ʈ
	Mail* reciedvedMailList[10]; // ���� ���� ����Ʈ

public:
	Client();
	~Client();

	virtual bool send(mailDeilivery& md); // ���� ������
	virtual bool receive(mailDeilivery& md);	 // ���� �ޱ�
};

class Manager : public User // User�κ��� ��ӹ��� Manager Ŭ����
{
public:
	Manager();
	~Manager();

	virtual bool send(mailDeilivery& md); // ���� ������
	virtual bool receive(mailDeilivery& md);	//���� �ޱ�
	
private:
	string currentCityName; // ���� ���� �̸�
};

