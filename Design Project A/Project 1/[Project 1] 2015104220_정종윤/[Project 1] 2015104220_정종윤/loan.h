#pragma once

#include "User.h"
#include <string>
#include <iostream>
using namespace std;

class loan
{
private:
	int userId;
	int amount;
	int repayment_priod_month;

public:
	loan();
	~loan();

	void setLoan(int _id, int _amount, int _repayment_priod_month); // ���� ���� �Է�
//	void print(); // ���� ���� ���

	int getUserId(); // ����� ���̵� ��ȯ
	int getAmount(); // ���� �ܱ� ��ȯ
	int GetRepayment_Period_Month(); // �ܿ� ��ȯ �Ⱓ ��ȯ

	void setAmount(int _amount); // ����� ����
	void setRepayment_Period_Month(int _period); // �ܿ� ��ȯ �Ⱓ ����



};

