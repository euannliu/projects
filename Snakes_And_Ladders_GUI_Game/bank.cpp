#include <iostream>

using namespace std;

#include "bank.h"

Bank::Bank()
{
	_amount=4000;
}

void Bank::settotal(int amount)
{
	_amount=amount;
}

int Bank::deposit(int amount)
{
	_amount+=amount;
	return _amount;
}

int Bank::withdraw(int amount)
{
	_amount-=amount;
	return _amount;
}
