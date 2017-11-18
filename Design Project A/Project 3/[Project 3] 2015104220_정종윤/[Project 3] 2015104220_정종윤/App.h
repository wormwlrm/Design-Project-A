#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iomanip>
#include "Seller.h"
#include "Buyer.h"
#include "RoomForRent.h"
#include "RoomForSale.h"

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

	vector<Room*> resultOfFilter1, resultOfFilter2, resultOfFilter3;   //����1, 2, 3�� ���� ���͸��� ������ �ӽ� �˻� ���
	int searchAreaRadius;    //����� �߽����� �˻��� ����(�Ÿ�)
	bool isFilter1Skipped, isFilter2Skipped, isFilter3Skipped;  //���͸��� ������ ������ �����ϴ� ������
	int minDeposit, maxDeposit;     //���͸��� ���� �������� ������ �����ϴ� ������
	int minMonthlyPay, maxMonthlyPay;	//���͸��� ���� ������ ������ �����ϴ� ������
	int minCost, maxCost;	//���͸��� ���� �ŸŰ��� ������ �����ϴ� ������
	string searchKey; //���͸��� ���� �˻��� ����
	                 
	vector<Room*> getFilter1Result();	// ����1 ��ȯ �Լ�
	vector<Room*> getFilter2Result();	// ����2 ��ȯ �Լ�
	vector<Room*> getFilter3Result();	// ����3 ��ȯ �Լ�

	void loadUserFile();	//���� ������ ���� �ε�
	void loadRoomFile();	//�� ������ ���� �ε�
	void saveFiles();	//���� ����

//	void run();	//���α׷� ����
	void printMenu();	//�޴� ���
	void printBuyerMenu();
	void printSellerMenu();

	bool login(int userType, string userID, string password);	//�α���
	bool logout();	//�α׾ƿ�
	
	void printRecentlySearcedRoomsOfLoginedUser();	//�ֱ� �˻� ���� ���
	Room* getRoomByID(int _roomID);	//ID�� �̿��� Room ��ȯ
	bool printFilterConditions();    //���� ���͵��� ������ ���
	void printRequestToBuyList();	//���� ��û ���� ���
	void setFilters(); // ���� ����
	void searchRooms();	//�� �˻�
	void registerNewRoom(); // �� ���
	void deleteRoom();	//�� ����

	int RecusiveBinSearch(int nArr[], int nBegin, int nEnd, int nTarget);
};

