#include "Mail.h"

Mail::Mail()
{
}

Mail::~Mail()
{
}

Letter::Letter()
{
}

Letter::~Letter()
{
}

Package::Package()
{
}

Package::~Package()
{
}

int Letter::calculateCost(int distance)
{
	if (distance == 0) // �⺻ ���
		return 1000;
	else // �Ÿ� �� 1000�� �� �߰�
		return distance * 1000;
}

int Package::calculateCost(int distance)
{
	if (distance == 0) // �⺻ ���
		return (1000 + 5 * getWeight());
	else // �Ÿ��� ���Կ� ����� ����
		return (1000 * distance + 5 * getWeight());
}

void Letter::printData()
{
	cout << "����" << endl;
	cout << "���� ��� : " << senderId << endl;
	cout << "���� �ּ� : " << senderAddr << endl;
	cout << "�޴� ��� : " << receiverId << endl;
	cout << "�޴� �ּ� : " << receiverAddr << endl << endl;
}

void Package::printData()
{
	cout << "����" << endl;
	cout << "���� ��� : " << senderId << endl;
	cout << "���� �ּ� : " << senderAddr << endl;
	cout << "�޴� ��� : " << receiverId << endl;
	cout << "�޴� �ּ� : " << receiverAddr << endl;
	cout << "���� : " << weight << endl << endl;
}

void Mail::setSenderId(string _SenderId){ senderId = _SenderId; }
void Mail::setReceiverId(string _ReceiverId){ receiverId = _ReceiverId; }
void Mail::setSenderAddr(string _SenderAddr){ senderAddr = _SenderAddr; }
void Mail::setReceiverAddr(string _ReceiverAddr){ receiverAddr = _ReceiverAddr; }
void Mail::setMailType(int _MailType){ mailType = _MailType; }
void Mail::setCost(int _Cost){ cost = _Cost; }
string Mail::getSenderId(){ return senderId; }
string Mail::getReceiverId(){ return receiverId; }
string Mail::getSenderAddr(){ return senderAddr; }
string Mail::getReceiverAddr(){ return receiverAddr; }
int Mail::getMailType(){ return mailType; }
int Mail::getCost(){ return cost; }
void Package::setWeight(int _Weight){ weight = _Weight; }
int Package::getWeight(){ return weight; }