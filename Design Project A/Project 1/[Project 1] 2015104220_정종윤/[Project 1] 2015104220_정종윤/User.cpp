#include "User.h"


User::User()
{
	cacheSize = 0;
}


User::~User()
{
}


transaction** User::getTrasCache()
{
	return transCache;
}

void User::setCache(transaction* trans)  // 최근 캐시의 개수에 따라 기존 캐시를 이동시킴
{
	if (cacheSize == 5) // 캐시 사이즈가 5일 때
	{
		for (int i = 4; i > 0; i--) // 기존 캐시 중 마지막 기록을 삭제
		{
			transCache[i] = transCache[i-1]; 
		}
	}
	else if (cacheSize != 5) // 캐시 사이즈가 5가 아닐 때
	{
		for (int j = cacheSize; j > 0; j--) // 기존 캐시를 이동시킴
		{
			transCache[j] = transCache[j-1];
		}
		cacheSize++;
	}

	transCache[0] = trans; // 0번 째 캐시에 새 기록을 추가
	
}

int User::getCacheSize()
{
	return cacheSize;
}

void User::setUser(int _id, string _password, string _name, int _accountNumber, int _balance, int _creditRating)
{
	id = _id;
	password = _password;
	name = _name;
	accountNumber = _accountNumber;
	balance = _balance;
	creditRating = _creditRating;
}

void User::printUserInfo()
{
	cout << "사용자 이름\t :" << getName() << endl;
	cout << "계좌번호\t :" << getAccoutNumber() << endl;
	cout << "잔액\t\t :" << getBalance() << endl;
	cout << "신용등급\t :" << getCreditRating() << endl;
}

int User::getId()
{
	return id;
}

string User::getPW()
{
	return password;
}

string User::getName()
{
	return name;
}

int User::getAccoutNumber()
{
	return accountNumber;
}

int User::getBalance()
{
	return balance;
}

int User::getCreditRating()
{
	return creditRating;
}

void User::setBalance(int _balance)
{
	balance += _balance;
}

void User::setCreditRating(int _creditRating) // 최대 10에서 최소 1까지만 처리
{
	creditRating += _creditRating;
	if (creditRating < 1)
	{
		creditRating = 1;
	}
	if (creditRating > 10)
	{
		creditRating = 10;
	}
}