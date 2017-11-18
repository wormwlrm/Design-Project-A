#pragma once
#include "Seller.h"
#include "Buyer.h"
#include "RoomForRent.h"
#include "RoomForSale.h"
#include <vector>
using namespace std;

class App
{
public:
	App();	//�⺻ ������
	~App();	//�Ҹ���

	void run();	//���α׷� ����
private:
	vector<User*> users;	//���� ����
	vector<Room*> rooms;	//�� ����

	User* loginedUser;	//�α��� ����

	vector<Room*> reusltOfFilter1, resultOfFilter2;   //����1, 2�� ���� ���͸��� ������ �ӽ� �˻� ���
	int searchAreaRadius;    //����� �߽����� �˻��� ����(�Ÿ�)
	bool isFilter1Skipped, istFilter2Skipped, isFilter3Skipped;  //���͸��� ������ ������ �����ϴ� ������
	int minDeposit, maxDeposit;     //���͸��� ���� �������� ������ �����ϴ� ������
	int minMonthlyPay, maxMonthlyPay;	//���͸��� ���� ������ ������ �����ϴ� ������
	int minCost, maxCost;	//���͸��� ���� �ŸŰ��� ������ �����ϴ� ������
	                 
	vector<Room*> getFilter1Result();	// ����1 ��ȯ �Լ�
	vector<Room*> getFilter2Result();	// ����2 ��ȯ �Լ�
	vector<Room*> getFilter3Result();	// ����3 ��ȯ �Լ�

	void loadUserFile();	//���� ������ �ε�
	void loadRoomFile();	//�� ������ �ε�
	void saveFiles();	//���� ����

	void run();	//���α׷� ����
	void printMenu();	//�޴� ���

	bool login(string userID, string password);	//�α���
	bool logout();	//�α׾ƿ�
	
	void printRecentlySearcedRoomsOfLoginedUser();	//�ֱ� �˻� ���� ���
	Room* getRoomByID(int _roomID);	//ID�� �̿��� Room ��ȯ
	bool printFilterConditions();    //���� ���͵��� ������ ���
	void searchRooms();	//�� �˻�
	void registerNewRoom(); // �� ���
	void deleteRoom();	//�� ����
};

