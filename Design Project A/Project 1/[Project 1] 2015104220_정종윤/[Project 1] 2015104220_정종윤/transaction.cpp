#include "transaction.h"


transaction::transaction()
{
}


transaction::~transaction()
{
}

void transaction::setTransation(int _fromId, int _toId, int _amount)
{
	fromId = _fromId;
	toId = _toId;
	amount = _amount;
}

void transaction::print()
{
	cout << "    " << fromId << "\t   ->\t   " << toId << "\t\t" << amount << endl;
}

int transaction::getFromId()
{
	return fromId;
}

int transaction::getToId()
{
	return toId;
}

int transaction::getAmount()
{
	return amount;
}