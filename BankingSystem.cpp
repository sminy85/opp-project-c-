#include "stdafx.h"
#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 20;

void ShowMenu(void);
void MakeAccount(void);
void DepositMoney(void);
void WithdrawMoney(void);
void ShowAllAccInfo(void);

enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

class Account
{
private:
	int accID;
	int balance;
	char *cusName;

public:
	Account(const int id,  const int money, const char *name)
		:accID(id), balance(money)
	{
		cusName = new char[strlen(name) + 1];
		strcpy(cusName, name);
	}

    
	Account(const Account& copy)
		:accID(copy.accID), balance(copy.balance)
	{
		cusName = new char[strlen(copy.cusName) + 1];
		strcpy(cusName, copy.cusName);
	}



	int getAccID() const
	{
		return accID;
	}

	void Deposit(int money)
	{
		balance += money;
	}

	int Withdraw(int money)
	{
		if (balance < money)
			return 0;
		else
		{
			balance -= money;
			return money;
		}

	}

	void showAccInfo() const
	{
		cout << "계좌번호: " << accID << endl;
		cout << "이    름: " << cusName << endl;
		cout << "잔    액: " << balance << endl;
		cout << endl;

	}

	~Account()
	{
		delete []cusName;
	}
};


Account * accArr[100];
int accNum = 0;


int main()
{
	int choice;

	while (1) {
		ShowMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			MakeAccount();
			break;
		case DEPOSIT:
			DepositMoney();
			break;
		case WITHDRAW:
			WithdrawMoney();
			break;
		case INQUIRE:
			ShowAllAccInfo();
			break;
		case EXIT:
		{
			for (int i = 0; i < accNum; i++)
				delete accArr[i];
			return 0;
		}

		default:
			cout << "Illegal selction.." << endl;
		}


	}
	
	return 0;
}


void ShowMenu(void)
{
	cout << "----MENU----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void MakeAccount(void)
{
	int id;
	int balance;
	char name[NAME_LEN];

	cout << "[계좌개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << endl;

	accArr[accNum] = new Account(id, balance, name);
	accNum++;

}
void DepositMoney(void)
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
void WithdrawMoney(void)
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
void ShowAllAccInfo(void)
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->showAccInfo();

	}
}

