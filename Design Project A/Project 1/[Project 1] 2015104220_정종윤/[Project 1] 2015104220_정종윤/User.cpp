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

void User::setCache(transaction* trans)  // �ֱ� ĳ���� ������ ���� ���� ĳ�ø� �̵���Ŵ
{
	if (cacheSize == 5) // ĳ�� ����� 5�� ��
	{
		for (int i = 4; i > 0; i--) // ���� ĳ�� �� ������ ����� ����
		{
			transCache[i] = transCache[i-1]; 
		}
	}
	else if (cacheSize != 5) // ĳ�� ����� 5�� �ƴ� ��
	{
		for (int j = cacheSize; j > 0; j--) // ���� ĳ�ø� �̵���Ŵ
		{
			transCache[j] = transCache[j-1];
		}
		cacheSize++;
	}

	transCache[0] = trans; // 0�� ° ĳ�ÿ� �� ����� �߰�
	
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
	cout << "����� �̸�\t :" << getName() << endl;
	cout << "���¹�ȣ\t :" << getAccoutNumber() << endl;
	cout << "�ܾ�\t\t :" << getBalance() << endl;
	cout << "�ſ���\t :" << getCreditRating() << endl;
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

void User::setCreditRating(int _creditRating) // �ִ� 10���� �ּ� 1������ ó��
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