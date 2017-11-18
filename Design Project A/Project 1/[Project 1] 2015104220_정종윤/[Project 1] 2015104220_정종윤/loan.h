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

	void setLoan(int _id, int _amount, int _repayment_priod_month); // 대출 정보 입력
//	void print(); // 대출 정보 출력

	int getUserId(); // 사용자 아이디 반환
	int getAmount(); // 대출 잔금 반환
	int GetRepayment_Period_Month(); // 잔여 상환 기간 반환

	void setAmount(int _amount); // 대출금 변경
	void setRepayment_Period_Month(int _period); // 잔여 상환 기간 변경



};

