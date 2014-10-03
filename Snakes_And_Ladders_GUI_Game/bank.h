#ifndef BANK_H
#define BANK_H

class Bank
{
	private:
		int _amount;
	public:
		Bank();
		void settotal(int amount);
		int deposit(int amount);
		int withdraw(int amount);
};

#endif
