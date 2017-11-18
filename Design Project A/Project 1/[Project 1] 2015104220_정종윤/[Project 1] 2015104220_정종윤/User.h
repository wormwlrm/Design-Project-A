#pragma once

#include <string>
#include <iostream>
#include "transaction.h"
using namespace std;

class User
{
private:
	int id;
	string password;
	string name;
	int accountNumber;
	int balance;
	int creditRating;

	int cacheSize;
	transaction* transCache[5];

public:
	User();
	~User();

	int getId(); // ���̵� ����
	string getPW(); // ��й�ȣ ����
	string getName(); // �̸� ����
	int getAccoutNumber(); // ���¹�ȣ ����
	int getBalance(); // �ܱ� ����
	int getCreditRating(); // �ſ��� ����
	int getCacheSize(); // ���� ĳ�� ������ ����

	void setBalance(int _balance); // �ܱ� ����
	void setCreditRating(int _creditRating); // �ſ��� ����
	void setCache(transaction* trans); // ���� ������ ĳ�ÿ� trans �迭�� ����� ����
	void resetCache(){ cacheSize = 0; }; // ĳ�� ����� �ʱ�ȭ
	transaction** getTrasCache(); // Application�� Transaction DB���� ID�� ��ġ�ϴ� �ŷ������� ������
	void setUser(int _id, string _password, string _name, int _accountNumber, int _balance, int _creditRating); // ����� ���� �Է�
	void printUserInfo(); // ����� ���� ���


};

// ���� ó������