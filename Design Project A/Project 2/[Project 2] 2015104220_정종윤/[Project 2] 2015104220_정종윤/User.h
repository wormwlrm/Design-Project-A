#pragma once
#include "Mail.h"
#include "MailDelivery.h"
#include <iostream>
#include <string>
using namespace std;

class MailDelivery;
class Mail;

class User
{
protected:
	int userType; // ���� Ÿ��( 0�� �Ϲ� ��, 1�� ������)
	string id; //���̵�
	string password; // ��й�ȣ

public:
	User();
	~User();

	void setUserType(int _UserType);
	void setId(string _Id);
	void setPassword(string _Password);
	int getUserType();
	string getId();
	string getPassword();

	virtual vector<Mail*>* getReceivedMail() = 0;
	virtual vector<Mail*>* getSendMail() = 0;
	virtual bool send(MailDelivery& md) = 0; // ������ ������ ���� ���� �Լ�
	virtual bool receive(MailDelivery& md) = 0; // ������ �޴� ���� ���� �Լ�
};

class Client : public User // User�κ��� ��ӹ��� Client Ŭ����
{
private:
	string name; // �̸�
	string address; // �ּ�

	vector<Mail*> sendMailList; // ���� ���� ����Ʈ
	vector<Mail*> reciedvedMailList; // ���� ���� ����Ʈ

public:
	Client();
	Client(int _UserType, string _Id, string _Password, string _Name, string _Address);
	~Client();

	void setName(string _name);
	void setAddress(string _address);	
	void setClient(int _UserType, string _Id, string _Password, string _Name, string _Address);
	string getName();
	string getAddress();
	void printSendedMail();

	virtual vector<Mail*>* getReceivedMail() { return &reciedvedMailList; };
	virtual vector<Mail*>* getSendMail() { return &sendMailList; };
	virtual bool send(MailDelivery& md); // ���� ������
	virtual bool receive(MailDelivery& md);	 // ���� �ޱ�
};

class Manager : public User // User�κ��� ��ӹ��� Manager Ŭ����
{
public:
	Manager();
	Manager(int _UserType, string _Id, string _Password);
	~Manager();

	void setCurrentCityName(string _CurrentCityName);
	string getCurrentCityName();
	void setManager(int _UserType, string _Id, string _Password);

	
	virtual vector<Mail*>* getReceivedMail() { return NULL; };
	virtual vector<Mail*>* getSendMail() { return NULL; };
	virtual bool send(MailDelivery& md); // ���� ������
	virtual bool receive(MailDelivery& md);	//���� �ޱ�

private:
	string currentCityName; // ���� ���� �̸�
};

