#include "stdafx.h"
#include <iostream>
#include <cstring>


using namespace std;

const int NAME_LEN = 20;

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };


enum{LEV_A=7, LEV_B=4,LEV_C=2};


enum {NORMAL=1, HIGH=2};

class Account
{
private:
	int accID;
	int balance;
	char *cusName;

public:
	Account(const int id, const int money, const char *name);
	Account(const Account& copy);
	int getAccID() const;
	virtual void Deposit(int money);
	int Withdraw(int money);
	void showAccInfo() const;
	~Account();
};

Account::Account(const int id, const int money, const char *name)
	:accID(id), balance(money)
{
	cusName = new char[strlen(name) + 1];
	strcpy(cusName, name);
}

Account::Account(const Account& copy)
	:accID(copy.accID), balance(copy.balance)
{
	cusName = new char[strlen(copy.cusName) + 1];
	strcpy(cusName, copy.cusName);
}

int Account::getAccID() const
{
	return accID;
}

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)
{
	if (balance < money)
		return 0;
	else
	{
		balance -= money;
		return money;
	}

}

void Account::showAccInfo() const
{
	cout << "계좌번호: " << accID << endl;
	cout << "이    름: " << cusName << endl;
	cout << "잔    액: " << balance << endl;
	cout << endl;

}

Account::~Account()
{
	delete[]cusName;
}


class NormalAccount : public Account
{
private:
	int interRate;
public:
	NormalAccount(const int ID, const int money, const char * name, const int rate)
		:Account(ID, money, name), interRate(rate)
	{

	}

	virtual void Deposit(int money)
	{
		Account::Deposit(money);
		Account::Deposit(money*(interRate / 100.0));
	}
};


class HighCreditAccount : public NormalAccount
{
private:
	int lev;
public:
	HighCreditAccount(const int ID, const int money, const char * name, const int rate, const int level)
		:NormalAccount(ID, money, name, rate), lev(level)
	{

	}

	virtual void Deposit(int money)
	{
		NormalAccount::Deposit(money);
		Account::Deposit((money)*(lev / 100.0));
	}
};



class AccountHandler
{
private:
	Account * accArr[100];
	int accNum;

public:
	AccountHandler();
	void ShowMenu(void) const;
	void MakeAccount(void);
	void DepositMoney(void);
	void WithdrawMoney(void);
	void ShowAllAccInfo(void);
	~AccountHandler();
protected:
	void MakeNormalAccount(void);
	void MakeCreditAccount(void);
};

AccountHandler::AccountHandler() : accNum(0)
{

}
void AccountHandler::ShowMenu(void) const
{
	cout << "----MENU----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::MakeAccount(void)
{

	int type;

	cout << "[계좌종류선택]" << endl;
	cout << "1.보통예금계좌 ";
	cout << "2.신용신뢰계좌" << endl;
	cout << "선택: ";  cin >> type;

	if (type == NORMAL)
		MakeNormalAccount();
	else
		MakeCreditAccount();

}

void AccountHandler::MakeNormalAccount(void)
{
	int id;
	int balance;
	int rate;
	char name[NAME_LEN];

	cout << "[보통계좌개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << "이자율: "; cin >> rate;
	cout << endl;

	accArr[accNum] = new NormalAccount(id, balance, name, rate);
	accNum++;

}

void AccountHandler::MakeCreditAccount(void)
{
	int id;
	int balance;
	int rate;
	int lev;
	char name[NAME_LEN];

	cout << "[신용계좌개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << "이자율: "; cin >> rate;
	cout << "신용등급(1toA, 2toB, 3toC): "; cin >> lev;
	cout << endl;

	switch (lev)
	{
	case 1:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, rate, LEV_A);
		break;
	case 2:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, rate, LEV_B);
break;
	case 3:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, rate, LEV_C);
	break;
	}

}
void AccountHandler::DepositMoney(void)
{
	int money;
	int id;

	cout << "[입     금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "입금액: "; cin >> money;


	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->getAccID() == id)
		{
			accArr[i]->Deposit(money);
			cout << "입금완료" << endl;
			return;
		}

	}
	cout << "잘못된 id입력" << endl;

}
void AccountHandler::WithdrawMoney(void)
{
	int money;
	int id;

	cout << "[출     금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "출금액: "; cin >> money;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->getAccID() == id)
		{
			if (accArr[i]->Withdraw(money) == 0)
				cout << "잔액부족" << endl;

			cout << "출금완료" << endl;
			return;
		}

	}

	cout << "잘못된 id입력" << endl;
}
void AccountHandler::ShowAllAccInfo(void)
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->showAccInfo();

	}
}

AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
}






int main()
{
	AccountHandler manager;
	int choice;

	while (1) {
		manager.ShowMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			manager.MakeAccount();
			break;
		case DEPOSIT:
			manager.DepositMoney();
			break;
		case WITHDRAW:
			manager.WithdrawMoney();
			break;
		case INQUIRE:
			manager.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selction.." << endl;
		}


	}

	return 0;
}