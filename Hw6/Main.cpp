#include <iostream>  
using namespace std;
const int NAME_LEN = 40;
const int MAX_ACC_NUM = 100;

class Account{ 
private: 
	int m_accID;
	int m_balance;
	char* m_cusName;
public:  		
	Account(int ID, int balance, char* cname) :m_accID{ID}, m_balance{ balance } {		     
		 m_cusName = new char[strlen(cname)+1];
		 strcpy(m_cusName, cname);
	} 
	~Account() {  		
		cout << "Using Destructor "<<endl;
		delete[] m_cusName;
	}  
	int GetAccID() {	
		return m_accID;
	}  
	void Deposit(int money){  
		m_balance += money;

	}
	int Withdraw(int money){ 
		if (money > m_balance) {
			return true;
		
		}else{
			m_balance -= money;
		    return false; 
		}
		
	}  
	void ShowAccInfo (void){ 
		
		cout << "Account ID: " << m_accID << endl;
		cout << "Name: " << m_cusName << endl;
		cout << "Balance: " << m_balance << endl << endl;
		
	}  
};

Account* accArr[MAX_ACC_NUM]; //Account array  
int accNum=0; // # of accounts  


enum class bank { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

void ShowMenu(void);  
void MakeAccount(void);  
void DepositMoney(void); 
void WithdrawMoney(void);  
void ShowAllAccInfo(void);  
int GetAccIdx(int);

int main(void) {	
	int choice;
	while(1){
		ShowMenu();
		cout<<"Select menu:";
		cin>>choice;
		cout<<endl;
		switch(bank(choice)){
			case bank::MAKE:
				MakeAccount();
				break;
			case bank::DEPOSIT:
				DepositMoney();
				break;
			case bank::WITHDRAW:
				WithdrawMoney();
				break;
			case bank::INQUIRE:
				ShowAllAccInfo();
				break;
			case bank::EXIT:			
				for(int i=0;i<accNum;i++)
					delete accArr[i];
				return 0;
			default:
				cout<<"Illegal selection.."<<endl;
		}
	} 
		
}

void ShowMenu(void) {
	cout << "-----Menu------" << endl;
	cout << "1.Make Accout" << endl;
	cout << "2.Deposit" << endl;
	cout << "3.Withdrawal" << endl;
	cout << "4.Display all" << endl;
	cout << "5.Exit program" << endl;
}

void MakeAccount(void) {
	int id;
	char name[NAME_LEN];
	int balance;
	
	if (accNum >= MAX_ACC_NUM) {
		cout << "Sorry! cannot make an account anymore." << endl;
		return;
	}
	if (accNum == -1) {
		accNum = 0;
	}
	cout << "[Make Account]" << endl;
	cout << "Account ID: ";
	cin >> id;
	cout << "Customer Name: ";
	cin >> name;
	cout << "Deposit amount: ";
	cin >> balance;

	cout << endl;
	if (GetAccIdx(id) != -1) {
		cout << "Error: Existing account ID" << endl;
		return;
	}

	accArr[accNum]= new Account(id,balance,name);
	
	accNum++;
	
}


void DepositMoney(void) {
	int money;
	int id;
	cout << "[Deposit]" << endl;
	cout << "AccountID: ";
	cin >> id;
	cout << "Deposit amount: ";
	cin >> money;
	for (int i = 0; i < accNum; i++) {
		if (accArr[i]->GetAccID() == id) {
			accArr[i]->Deposit(money);
			cout << "Deposit completed" << endl << endl;
			return;
		}
	}
	cout << "This ID is not valid." << endl << endl;
}
void WithdrawMoney(void) {
	int money;
	int id;
	cout << "[Withdrawal]" << endl;
	cout << "Account ID: ";
	cin >> id;
	cout << "Withdrawal amount: ";
	cin >> money;
	for (int i = 0; i < accNum; i++) {
		if (accArr[i]->GetAccID() == id) {
			if (accArr[i]->Withdraw(money)) {
				cout << "Not enough balance" << endl << endl;
				return;
			}

			cout << "Withdrawal completed" << endl << endl;
			return;
		}
	}
	cout << "This ID is not valid." << endl << endl;
}
void ShowAllAccInfo(void) {
	for (int i = 0; i < accNum; i++) {
		cout << "Account " << i+1<<endl;
		accArr[i]->ShowAccInfo();

	}
}
int GetAccIdx(int id) {
	for (int i = 0; i < accNum; i++) {
		if (accArr[i]->GetAccID() == id) {
			return i;
		}
	}
	return -1;
}
