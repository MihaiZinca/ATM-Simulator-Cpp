#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount
{
private:
	string accountNumber;
	string accountName;
	double balance;
	int pin;
public:
	BankAccount(string accNumber, string accName, double initBalance,int pinCode)
	{
		accountNumber = accNumber;
		accountName = accName;
		balance = initBalance;
		pin = pinCode;
	}
	BankAccount()
	{
		accountNumber = "";
		accountName = "";
		balance = 0.0;
		pin = 0;
	}

	//depunere bani in cont
	void deposit(double amount)
	{
		if (amount > 0)
		{
			balance += amount;
			cout << "Deposited: " << amount << "$" << " ||| New Balance is: " << balance << "$" << endl;
		}
		else
		{
			cout << "Deposit amount must be positive!" << endl;
		}
	}

	//retrage bani din cont
	void withdraw(double amount)
	{
		if (amount > 0 && amount <= balance)
		{
			balance -= amount;
			cout << "Withdrawn: " << amount << "$" << " ||| New Balance is : " << balance << "$" << endl;
		}
		else
		{
			cout << "Insufficient funds or invalid amount!" << endl;
		}

	}
	void checkBalance() const {
		cout << "Account Balance: " << balance << "$" << endl;
	}

	int getPin() const {
		return pin;
	}

	void changePin() {
		int newPin;
		do {
			cout << "Enter new 4-digit PIN: ";
			cin >> newPin;
			if (newPin < 1000 || newPin > 9999)
				cout << "PIN must be exactly 4 digits!\n";
		} while (newPin < 1000 || newPin > 9999);

		pin = newPin;
		cout << "PIN changed successfully!\n";
	}
	void saveToFile() const {
		ofstream file(accountNumber + ".txt");
		if (file.is_open()) {
			file << accountNumber << endl;
			file << accountName << endl;
			file << balance << endl;
			file << pin << endl;
			file.close();
			cout << "Account details saved to " << accountNumber << ".txt" << endl;
		}
		else
		{
			cout << "Unable to save account" << endl;
		}
	}

	static BankAccount loadFromFile(string accNumber)
	{
		ifstream file(accNumber + ".txt");
		string accName;
		double bal;
		int accpin;

		if (file.is_open())
		{
			getline(file, accNumber);
			getline(file, accName);
			file >> bal;
			file >> accpin;
			file.close();

			return BankAccount(accNumber, accName, bal,accpin);
		}
		else
		{
			cout << "No existing account fund with that number.You need to create a new account." << endl;
			return BankAccount();
		}
	}
	//daca nr contului e gol, cont nevalid
	bool isValid() const {
		return !accountNumber.empty();
	}
};

int main()
	{
		string accNumber;

		cout << "Enter Account Number: ";
		cin >> accNumber;

		//creare obiect(cont bancar)
		BankAccount account = BankAccount::loadFromFile(accNumber);

		if (!account.isValid()) {
			string accName;
			double initialBalance;
			int pinCode;

			cout << "\nCreating a new account...\n";
			cout << "Enter Account Name: ";
			cin.ignore();
			getline(cin, accName);
			cout << "Enter Initial Balance in $: ";
			cin >> initialBalance;
			
			do {
				cout << "Set your 4-digit PIN: ";
				cin >> pinCode;
				if (pinCode < 1000 || pinCode > 9999)
					cout << "PIN must be exactly 4 digits!\n";
			} while (pinCode < 1000 || pinCode > 9999);

			account = BankAccount(accNumber, accName, initialBalance,pinCode);
			account.saveToFile();
			cout << "Account created successfully!\n";
		}

		int attempts = 3;
		int enterpin;
		bool autentification = false;
		while (attempts > 0)
		{
			cout << "Enter your PIN: ";
			cin >> enterpin;

			if (enterpin == account.getPin())
			{
				autentification = true;
				break;
			}
			else
			{
				attempts--;
				cout << "Incorrect PIN! Attempts left: " << attempts << endl;
			}
		}

		if (!autentification)
		{
			cout << "Too many wrong attempts. Exiting...\n";
			return 0;
		}
		
		int choice;
		do {
			cout << "\nBank Menu: \n";
			cout << "1.Deposit Amount \n";
			cout << "2.Withdraw Amount \n";
			cout << "3.Check Balance \n";
			cout << "4.Change PIN \n";
			cout << "5.Save Accounnt \n";
			cout << "6.Exit \n";

			cout << "Choose an option: ";
			cin >> choice;

			switch (choice) {
			case 1: {
				double amount;
				cout << "Enter the amount to deposit in $: ";
				cin >> amount;

				account.deposit(amount);
				break;
				}
			case 2: {
				double amount;
				cout << "Enter amount to withdraw in $: ";
				cin >> amount;

				account.withdraw(amount);
				break;
			}
			case 3: {
				account.checkBalance();
				break;
			}
			case 4: {
				account.changePin();
				break;
			}
			case 5: {
				account.saveToFile();
				break;
			}
			case 6: {
				cout << "Exiting..." << endl;
				account.saveToFile();
				break;
			}
			default:
				cout << "Invalid option! Try again. " << endl;
			}
		} while (choice != 6);
		return 0;
	}
