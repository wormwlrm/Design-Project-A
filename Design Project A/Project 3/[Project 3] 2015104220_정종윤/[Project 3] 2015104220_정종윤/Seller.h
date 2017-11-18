#pragma once
#include "User.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Seller :
	public User
{
public:
	Seller(); // �⺻ ������
	~Seller(); // �Ҹ���

	void addRoomIDToRegisteredRoomList(int _roomID);	//iD�� �̿��� �� �߰�
	virtual void printUserInfo();	//�Ǹ��� ���� ���
	
	vector<int>* getRegisteredRoomList();

private:
	vector<int> registerdRoomList;	//����� �� ����Ʈ
};

