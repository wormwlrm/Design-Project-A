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

	int getFromId(); // 보낸 사람 아이디 리턴
	int getToId(); // 받은 사람 아이디 리턴
	int getAmount(); // 금액 리턴

	void setTransation(int _fromId, int _toId, int _amount); // 거래 정보 입력
	void print(); // 거래 정보 출력
};

