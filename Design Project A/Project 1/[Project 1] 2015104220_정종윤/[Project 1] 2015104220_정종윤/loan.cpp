#include "loan.h"


loan::loan()
{
}


loan::~loan()
{
}

void loan::setLoan(int _id, int _amount, int _repayment_priod_month)
{
	userId = _id;
	amount = _amount;
	repayment_priod_month = _repayment_priod_month;
}

/*void loan::print()
{
	
}*/

int loan :: getUserId()
{
	return userId;
}

int loan::getAmount()
{
	return amount;
}

int loan::GetRepayment_Period_Month()
{
	return repayment_priod_month;
}

void loan:: setAmount(int _amount)
{
	amount -= _amount;
}

void loan::setRepayment_Period_Month(int _period)
{
	repayment_priod_month -= _period;
}