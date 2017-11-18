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

	int getId(); // 아이디 리턴
	string getPW(); // 비밀번호 리턴
	string getName(); // 이름 리턴
	int getAccoutNumber(); // 계좌번호 리턴
	int getBalance(); // 잔금 리턴
	int getCreditRating(); // 신용등급 리턴
	int getCacheSize(); // 현재 캐시 사이즈 리턴

	void setBalance(int _balance); // 잔금 설정
	void setCreditRating(int _creditRating); // 신용등급 설정
	void setCache(transaction* trans); // 현재 유저의 캐시에 trans 배열의 기록을 저장
	void resetCache(){ cacheSize = 0; }; // 캐시 사이즈를 초기화
	transaction** getTrasCache(); // Application의 Transaction DB에서 ID가 일치하는 거래내역을 가져옴
	void setUser(int _id, string _password, string _name, int _accountNumber, int _balance, int _creditRating); // 사용자 정보 입력
	void printUserInfo(); // 사용자 정보 출력


};

// 예외 처리문들