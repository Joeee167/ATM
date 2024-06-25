#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>

using namespace std;

const string FileName = "Clients.txt";

struct stClients
{
	string AccountNumber;
	string PIN;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool MarkForDelete = false;
};

stClients CurrentClient;

enum enChoices { QuickWithDraw = 1, NormalWithDraw = 2, Deposit = 3, CheckBalance = 4,LogOut = 5 };

vector<string> SplitString(string str, string Seperator)
{
	string SeperatedWord;
	vector <string> vSeperated;
	short pos = 0;

	while ((pos = str.find(Seperator)) != string::npos)   // Assign position of seperator to " pos " and check if it is value or null 
	{
		SeperatedWord = str.substr(0, pos);  // seperate the string at the seperator position

		if (SeperatedWord != "")
		{
			vSeperated.push_back(SeperatedWord);  // push the seperated word to the vector
		}

		str.erase(0, pos + Seperator.length());  // erase the string from start till the end of seperator
	}

	if (str != "")
	{
		vSeperated.push_back(str); // push last seperated part " No seperator after it "
	}

	return vSeperated;
}

stClients ConvertLineToRecord(vector<string> vClient)
{

	// Seperate the string into client data using the vector

	stClients Client;

	Client.AccountNumber = vClient[0];
	Client.PIN = vClient[1];
	Client.Name = vClient[2];
	Client.PhoneNumber = vClient[3];
	Client.AccountBalance = stod(vClient[4]);

	return Client;
}

vector <stClients> LoadDataFromFile(string FileName)
{
	fstream fClients;
	vector<stClients> vClients;

	fClients.open(FileName, ios::in);   // Open the file in read mode

	string Line;
	stClients Client;

	if (fClients.is_open())
	{

		while (getline(fClients, Line))  // checks if there is data found in file
		{
			Client = ConvertLineToRecord(SplitString(Line, "#//#"));   // Convert the string in file into " stClient " struct
			vClients.push_back(Client);  // Save every client data in vector of clients
		}

		fClients.close();
	}

	return vClients;
}

bool SearchForClientInFile(string AccountNumber,string PIN,stClients &CurrentClient)
{
	vector<stClients> vClients = LoadDataFromFile(FileName);		// Load all clients from file in vector of clients

	for (stClients& client : vClients)
	{
		if (client.AccountNumber == AccountNumber && client.PIN == PIN)		// If a client is found with the required acc number and pin code , the data is saved in a global variable " CurrentClient "
		{
			CurrentClient = client;
			return 1;

		}
	}

	return 0;

}

string ConvertRecordToLine(stClients Client, string Seperator)
{
	// Convert Client Info Into String To be added to the file

	string Line = "";

	Line += Client.AccountNumber + Seperator;
	Line += Client.PIN + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.PhoneNumber + Seperator;
	Line += to_string(Client.AccountBalance);	// Convert balance into string and add it to client data " string "

	return Line;


}

void SaveDataFromVectorAfterUpdate(string FileName, vector<stClients>& vClients)
{
	fstream fClients;

	string Line;

	fClients.open(FileName, ios::out);  // Delete previous data

	if (fClients.is_open())
	{
		for (stClients& Client : vClients)
		{
			if (Client.MarkForDelete == false)		// If the client is not marked to be deleted , info is added to the file
			{
				Line = ConvertRecordToLine(Client, "#//#");
				fClients << Line << endl;

			}
		}

		fClients.close();
	}
}

void GoBackToMainMenu();

void CheckBalanceScreen()
{
	cout << "========================================\n";
	cout << "\tCheck Balance Screen\n";
	cout << "========================================\n";

	cout << "\nYour Balance is " << CurrentClient.AccountBalance <<"$." << endl;		// Show the cureent client balance

	GoBackToMainMenu();		// On clicking any key, go back to the main menu
}

void QuickWithdrawScreen();

void PerformWithdraw(int amount)
{
	vector<stClients> vClients = LoadDataFromFile(FileName);

	if (amount > CurrentClient.AccountBalance)	// If amount to withdraw is more than current balance , return to screen without performing withdraw
	{
		cout << "\nInvalid. Amount is more than current balance.\n";
		cout << "\n\nPress any key to enter another amount...\n";
		system("pause>0");
		system("cls");
		QuickWithdrawScreen();
	}

	cout << "\nAre you sure you want to perform this transaction?Y/N";
	char answer;
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		CurrentClient.AccountBalance -= amount;		// Update balance in variable

		for (stClients& C : vClients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C.AccountBalance -= amount;		// update balance in file
			}
		}

		cout << "\nDone Successfully. New balance is " << CurrentClient.AccountBalance << endl;

		SaveDataFromVectorAfterUpdate(FileName, vClients);		// Save data in file after update
		GoBackToMainMenu();
	}
}

void PerformDeposit(int amount)
{
	vector<stClients> vClients = LoadDataFromFile(FileName);

	cout << "\nAre you sure you want to perform this transaction?Y/N";
	char answer;
	cin >> answer;

	if (toupper(answer) == 'Y')
	{
		CurrentClient.AccountBalance += amount;

		for (stClients& C : vClients)
		{
			if (C.AccountNumber == CurrentClient.AccountNumber)
			{
				C.AccountBalance += amount;		// Update balance in file
			}
		}

		cout << "\nDone Successfully. New balance is " << CurrentClient.AccountBalance << endl;

		SaveDataFromVectorAfterUpdate(FileName, vClients);		// Save client in file after updating balance
		GoBackToMainMenu();
	}
}


void ChooseWithdrawAmount()
{
	int choice = 0;

	while (choice < 0 || choice>9)
	{
		cout << "\nChoose what to withdraw from [1] to [8] or [9] to exit?";
		cin >> choice;
	}

	

	switch (choice)
	{
	case 1:
		PerformWithdraw(20);
		break;

	case 2:
		PerformWithdraw(50);
		break;

	case 3:
		PerformWithdraw(100);
		break;

	case 4:
		PerformWithdraw(200);
		break;

	case 5:
		PerformWithdraw(400);
		break;

	case 6:
		PerformWithdraw(600);
		break;

	case 7:
		PerformWithdraw(800);
		break;

	case 8:
		PerformWithdraw(1000);
		break;

	case 9:
		GoBackToMainMenu();
	}
}

void QuickWithdrawScreen()
{
	cout << "========================================\n";
	cout << "\tQuick Withdraw Screen\n";
	cout << "========================================\n";

	cout << "\t[1] 20 \t\t [2] 50\n";
	cout << "\t[3] 100 \t [4] 200\n";
	cout << "\t[5] 400 \t [6] 600\n";
	cout << "\t[7] 800 \t [8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "========================================\n";




	cout << "\nYour Balance is " << CurrentClient.AccountBalance << "$." << endl;

	ChooseWithdrawAmount();

}

void NormalWithdrawScreen()
{
	cout << "========================================\n";
	cout << "\tNormal Withdraw Screen\n";
	cout << "========================================\n";

	int amount = 0;

	do
	{
		// The amount entered should be multiple of 5

		cout << "\nEnter an amount multiple of 5 : ";
		cin >> amount;

		if (amount > CurrentClient.AccountBalance)
		{
			cout << "\nInvalid. Amount is more than current balance.\n";
			cout << "\n\nPress any key to enter another amount...\n";
			system("pause>0");
			system("cls");
			NormalWithdrawScreen();
		}

	} while (amount % 5 != 0);


	

	PerformWithdraw(amount);


}

void DepositScreen()
{
	cout << "========================================\n";
	cout << "\tDeposit Screen\n";
	cout << "========================================\n";

	int amount = 0;

	do
	{
		cout << "\nEnter positive amount : ";
		cin >> amount;

		if (amount < 0)		// Check if amount is positive or not
		{
			cout << "\nInvalid. Can't deposit negative amount.\n";
			cout << "\n\nPress any key to enter another amount...\n";
			system("pause>0");
			system("cls");
			DepositScreen();
		}

	} while (amount < 0);




	PerformDeposit(amount);


}

void ChooseOption();

void StartATM()
{


	cout << "========================================\n";
	cout << "\t\tATM Main Menu\n";
	cout << "========================================\n";

	cout << "\t[" << 1 << "] Quick Withdraw\n";
	cout << "\t[" << 2 << "] Normal Withdraw \n";
	cout << "\t[" << 3 << "] Deposit \n";
	cout << "\t[" << 4 << "] Check Balance \n";
	cout << "\t[" << 5 << "] LogOut\n";


	cout << "========================================\n";

	 ChooseOption();

}

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to main menu...\n";
	system("pause>0");

	system("cls");
	StartATM();
}

void LoginScreen()
{
	// Read Account Number and Pin code till they are entered correctly by the client

	string AccountNumber;
	string PIN;

	bool count = 0;

	do
	{
		system("cls");

		cout << "========================================\n";
		cout << "\t\tLogin Screen\n";
		cout << "========================================\n";

		if (count == 1)
			cout << "\nInvalid AccountNumber/PIN\n";


		cout << "\nEnter account number : ";
		cin >> AccountNumber;

		cout << "\nEnter PIN : ";
		cin >> PIN;

		count = 1;

	} while (!SearchForClientInFile(AccountNumber,PIN,CurrentClient));



	system("cls");
	StartATM();

}

void ChooseOption()
{
	cout << "\nChoose what do you want to do ? [1 to 5]";
	short choice;
	cin >> choice;

	choice = (enChoices)choice;

	switch (choice)
	{
	case enChoices::QuickWithDraw:

		system("cls");
		QuickWithdrawScreen();

		break;

	case enChoices::NormalWithDraw:

		system("cls");
		NormalWithdrawScreen();

		break;

	case enChoices::Deposit:

		system("cls");
		DepositScreen();

		break;

	case enChoices::CheckBalance:

		system("cls");
		CheckBalanceScreen();
		break;


	case enChoices::LogOut:
		system("cls");
		LoginScreen();
		break;

	}

}

int main()
{
	LoginScreen();
	system("pause");

	return 0;
}