#pragma once
#include <iostream>
using namespace std;
class transaction
{
private:
	int fromId;
	int toId;
	int amount;

public:
	transaction();
	~transaction();

	int getFromId(); // ���� ��� ���̵� ����
	int getToId(); // ���� ��� ���̵� ����
	int getAmount(); // �ݾ� ����

	void setTransation(int _fromId, int _toId, int _amount); // �ŷ� ���� �Է�
	void print(); // �ŷ� ���� ���
};

