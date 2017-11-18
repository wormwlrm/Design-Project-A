#pragma once
#include <string>
using namespace std;
class Mail
{
private:
	string senderId;	//���� ��� ID
	string recieverId;	//�޴� ��� ID
	string senderAddr;	//���� ��� �ּ�
	string recieverAddr;//�޴� ��� �ּ�
	int mailType;	//���� ����
	int cost;	//��� ���

	virtual int calculateCost(int distance) = 0; //��� ����� ����ϴ� ���� ���� �Լ�

public:
	Mail(); //������
	~Mail(); //�Ҹ���
	
	void setSenderId();
	void setReceiverId();
	void setSenderAddr();
	void setReceiverAddr();
	void setMailType();
	void setCost();

	string getSenderId();
	string getReceiverId();
	string getSenderAddr();
	string getRecieverAddr();
	int getMailType;	
	int getCost();

};

class Letter :	public Mail // Mail�κ��� ��ӹ��� Letter Ŭ����
{
public:
	virtual int calculateCost(int distance); // �Ÿ��� ���� ��� ��� ���
public:
	Letter();
	~Letter();
};

class Package :	public Mail // Mail�κ��� ��ӹ��� Package Ŭ����
{
public:	
	virtual int calculateCost(int distance); // �Ÿ��� ���Կ� ���� ��� ��� ���
	Package();
	~Package();
private:
	int weight; // ���� ����
};