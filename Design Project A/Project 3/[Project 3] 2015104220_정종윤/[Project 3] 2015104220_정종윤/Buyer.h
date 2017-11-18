#pragma once
#include "User.h"
#include <iostream>
#include <list>
using namespace std;

class Buyer :
	public User
{
public:
	Buyer();	//�⺻ ������
	~Buyer();	//�Ҹ���
	bool addRoomIDToRecentlySearched(int _roomID);	//�ֱ� �˻� ������ �߰�
	bool addRoomIDToRequestToBuy(int _roomID);	//���� ��û ������ �߰�

	virtual void printUserInfo();	//������ ���� ���

	int getXCoord();
	int getYCoord();
	vector<int>* getRecentlySearched();
	vector<int>* getRoomsRequestToBuy();

	void setXCoord(int _X);
	void setYCoord(int _Y);
	

private:
	int xCoord, yCoord;	//�������� ��ǥ
	vector<int> recentlySearched;	//�ֱ� �˻� ���� ����Ʈ
	vector<int> roomsRequestToBuy; //���� ��û ���� ����Ʈ

	
};

