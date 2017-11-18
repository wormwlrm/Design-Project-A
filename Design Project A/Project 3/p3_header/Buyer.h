#pragma once
#include "User.h"
#include <list>
class Buyer :
	public User
{
public:
	Buyer();	//�⺻ ������
	~Buyer();	//�Ҹ���
	bool addRoomIDToRecentlySearched(int _roomID);	//�ֱ� �˻� ������ �߰�
	bool addRoomIDToRequestToBuy(int _roomID);	//���� ��û ������ �߰�

	virtual void printUserInfo();	//������ ���� ���

private:
	int xCoord, yCoord;	//�������� ��ǥ
	list<int> recentlySearched;	//�ֱ� �˻� ���� ����Ʈ
	list<int> roomsRequestToBuy; //���� ��û ���� ����Ʈ

	
};

