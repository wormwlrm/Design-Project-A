#pragma once
#include <list>
#include <string>
#include <vector>
using namespace std;

class Room
{
public:
	Room(); // �⺻ ������
	~Room(); // �Ҹ���
	bool addUserInRequestToBuyList(string _userID); // ����ID�� �̿��� ���� ��û ����Ʈ�� �߰�
	
	virtual void printRoomInfo() = 0; // ������ ����ϴ� ���� ���� �Լ�

	int getRoomType();
	int getRoomID();
	string getSellerID();
	string getRoomName();
	int getXCoord();
	int getYCoord();
	vector<string>* getUsersRequestToBuyList();

	void setRoomType(int _roomType);
	void setRoomID(int _roomID);
	void setSellerID(string _sellerID);
	void setRoomName(string _roomName);
	void setXCoord(int _X);
	void setYCoord(int _Y);


private:
	int roomType; // �� Ÿ��
	int roomID;	// �� ID
	string sellerID; // �Ǹ��� ID
	string roomName; // �� �̸�
	int xCoord, yCoord; // ��ǥ
	vector<string> usersRequestToBuyList; // ���� ��û�� ���� ID ����Ʈ

	
};

