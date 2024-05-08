#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

class account
{
	int Account_No;
	char Account_Holder_Name[44];
	char type;
	int Deposit_Amount;
public:
	void login();
	void Open_account();
	void Display_account() const;	
	void Update();	
	void dep(int);	
	void Withdraw(int);	
	void report() const;	
	int Return_Account_Number() const;
	int Return_Deposit_Amount() const;	
	char Return_type() const;
};  
void account::Open_account()
{
	cout<<"\nPlease! Enter The account No. :";
	cin>>Account_No;
	cout<<"\nPlease! Enter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(Account_Holder_Name,44);
	cout<<"\nPlease! Enter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nPlease! Enter The Initial amount(>=440 for Saving and >=1000 for current ) : ";
	cin>>Deposit_Amount;
	cout<<"\n\nAccount Created..";
}     
void account::Display_account() const
{
	cout<<"\nAccount No. : "<<Account_No;
	cout<<"\nAccount Holder Name : ";
	cout<<Account_Holder_Name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<Deposit_Amount;
}
void account::dep(int x)
{
	Deposit_Amount+=x;
}
	
void account::Withdraw(int x)
{
	Deposit_Amount-=x;
}
	
void account::report() const
{
	cout<<Account_No<<setw(10)<<" "<<Account_Holder_Name<<setw(10)<<" "<<type<<setw(6)<<Deposit_Amount<<endl;
}

void account::Update()
{
	cout<<"\nAccount No. : "<<Account_No;
	cout<<"\nUpdate Account Holder Name : ";
	cin.ignore();
	cin.getline(Account_Holder_Name,44);
	cout<<"\nUpdate Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nUpdate Balance amount : ";
	cin>>Deposit_Amount;
}
	
int account::Return_Account_Number() const
{
	return Account_No;
}


char account::Return_type() const
{
	return type;
}
int account::Return_Deposit_Amount() const
{
	return Deposit_Amount;
}
void delete_account(int);	
void display_all();	
void write_account();	
void display_sp(int);	
void Deposit_Amount_withWithdraw(int, int); 
void intro();
void login();	
void Update_account(int);	
int main()
{
	char ch;
	int num;
	intro();
	do
	{
		cout<<"\n\n\t\t***************MAIN MENU******************";
		cout<<"\n\t\t1. Create account";
		cout<<"\n\t\t2. Deposit amount";
		cout<<"\n\t\t3. Withdraw amount";
		cout<<"\n\t\t4. Balance enquiry";
		cout<<"\n\t\t5. All account holders list";
		cout<<"\n\t\t6. close an account";
		cout<<"\n\t\t7. Update an account";
		cout<<"\n\t\t8. EXIT";
		cout<<"\n\t\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			Deposit_Amount_withWithdraw(num, 1);
			break;
		case '3':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			Deposit_Amount_withWithdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\t\tPlease! Enter The account No. : "; cin>>num;
			Update_account(num);
			break;
		 case '8':
			cout<<"\n\t\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}
void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.Open_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}
void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\nAccount number does not exist";
}
void Update_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			cout<<"\nPlease! Enter The New Details of account"<<endl;
			ac.Update();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\t\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n Record Not Found ";
}
void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.Return_Account_Number()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\n\t\tRecord Deleted ..";
}
void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\t\tACCOUNT HOLDER LIST\n";
	cout<<"*\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"*\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}
void Deposit_Amount_withWithdraw(int n, int option)
{
	int Amount;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			if(option==1)
			{
				cout<<"\n\t\tTO Deposit_AmountE AMOUNT ";
				cout<<"\nPlease! Enter The amount to be Deposit_Amounted";
				cin>>Amount;
				ac.dep(Amount);
			}
			if(option==2)
			{
				cout<<"\n\t\tTO WITHWithdraw AMOUNT ";
				cout<<"\nPlease! Enter The amount to be withWithdraw";
				cin>>Amount;
				int bal=ac.Return_Deposit_Amount()-Amount;
				if((bal<440 && ac.Return_type()=='S') || (bal<1000 && ac.Return_type()=='C'))
					cout<<"Insufficience balance";
				else
					ac.Withdraw(Amount);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\t\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n Record Not Found ";
}
void intro()
{
	cout<<"\n\n\t\t  BANK MANAGEMENT";
	cout<<"\n\t\t\t  SYSTEM";
	cout<<"\n\nMADE BY : Vkiptum";
	cout<<"\nPress Enter to continue..";
	cin.get();
	}



