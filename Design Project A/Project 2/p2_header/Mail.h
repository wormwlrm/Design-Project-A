#pragma once
#include <string>
using namespace std;
class Mail
{
private:
	string senderId;	//보낸 사람 ID
	string recieverId;	//받는 사람 ID
	string senderAddr;	//보낸 사람 주소
	string recieverAddr;//받는 사람 주소
	int mailType;	//우편물 종류
	int cost;	//배송 비용

	virtual int calculateCost(int distance) = 0; //배송 비용을 계산하는 순수 가상 함수

public:
	Mail(); //생성자
	~Mail(); //소멸자
	
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

class Letter :	public Mail // Mail로부터 상속받은 Letter 클래스
{
public:
	virtual int calculateCost(int distance); // 거리에 따른 배송 비용 계산
public:
	Letter();
	~Letter();
};

class Package :	public Mail // Mail로부터 상속받은 Package 클래스
{
public:	
	virtual int calculateCost(int distance); // 거리와 무게에 따른 배송 비용 계산
	Package();
	~Package();
private:
	int weight; // 소포 무게
};