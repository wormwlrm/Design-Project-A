#pragma once
#include "User.h"
#include <list>

class Seller :
	public User
{
public:
	Seller(); // �⺻ ������
	~Seller(); // �Ҹ���

	void addRoomIDToRegisteredRoomList(int _roomID);	//iD�� �̿��� �� �߰�
	virtual void printUserInfo();	//�Ǹ��� ���� ���

private:
	list<int> registerdRoomList;	//����� �� ����Ʈ
};

