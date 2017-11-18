#pragma once
#include "MailDelivery.h"
#include <string>
using namespace std;

class Mail
{
protected:
	string senderId;					//���� ��� ID
	string receiverId;					//�޴� ��� ID
	string senderAddr;					//���� ��� �ּ�
	string receiverAddr;				//�޴� ��� �ּ�
	int mailType;						//���� ����
	int cost;							//��� ���


public:
	Mail();
	~Mail();

	void setSenderId(string _SenderId);
	void setReceiverId(string _ReceiverId);
	void setSenderAddr(string _SenderAddr);
	void setReceiverAddr(string _ReceiverAddr);
	void setMailType(int _MailType);
	void setCost(int _Cost);

	string getSenderId();
	string getReceiverId();
	string getSenderAddr();
	string getReceiverAddr();
	int getMailType();
	int getCost();

	virtual int calculateCost(int distance) = 0; //��� ����� ����ϴ� ���� ���� �Լ�
	virtual void printData() = 0;
};

class Letter : public Mail // Mail�κ��� ��ӹ��� Letter Ŭ����
{
public:
	virtual int calculateCost(int distance); // �Ÿ��� ���� ��� ��� ���
	virtual void printData();
public:
	Letter();
	~Letter();
};

class Package : public Mail // Mail�κ��� ��ӹ��� Package Ŭ����
{
public:
	virtual int calculateCost(int distance); // �Ÿ��� ���Կ� ���� ��� ��� ���
	virtual void printData();
	Package();
	~Package();

	void setWeight(int _Weight);
	int getWeight();
private:
	int weight; // ���� ����
};

