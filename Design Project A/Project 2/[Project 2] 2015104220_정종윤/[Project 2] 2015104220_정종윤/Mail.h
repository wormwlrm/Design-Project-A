#pragma once
#include "MailDelivery.h"
#include <string>
using namespace std;

class Mail
{
protected:
	string senderId;					//보낸 사람 ID
	string receiverId;					//받는 사람 ID
	string senderAddr;					//보낸 사람 주소
	string receiverAddr;				//받는 사람 주소
	int mailType;						//우편물 종류
	int cost;							//배송 비용


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

	virtual int calculateCost(int distance) = 0; //배송 비용을 계산하는 순수 가상 함수
	virtual void printData() = 0;
};

class Letter : public Mail // Mail로부터 상속받은 Letter 클래스
{
public:
	virtual int calculateCost(int distance); // 거리에 따른 배송 비용 계산
	virtual void printData();
public:
	Letter();
	~Letter();
};

class Package : public Mail // Mail로부터 상속받은 Package 클래스
{
public:
	virtual int calculateCost(int distance); // 거리와 무게에 따른 배송 비용 계산
	virtual void printData();
	Package();
	~Package();

	void setWeight(int _Weight);
	int getWeight();
private:
	int weight; // 소포 무게
};

