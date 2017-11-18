#pragma once
#include <list>
#include <string>
using namespace std;

class Room
{
public:
	Room(); // �⺻ ������
	~Room(); // �Ҹ���
	bool addUserInRequestToBuyList(string _userID); // ����ID�� �̿��� ���� ��û ����Ʈ�� �߰�
	virtual void printRoomInfo() = 0; // ������ ����ϴ� ���� ���� �Լ�

private:
	int roomType; // �� Ÿ��
	int roomID;	// �� ID
	int sellerID; // �Ǹ��� ID
	string roomName; // �� �̸�
	int xCoord, yCoord; // ��ǥ
	list<string> usersRequestToBuyList; // ���� ��û�� ���� ID ����Ʈ

	
};

