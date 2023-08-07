#include "Customer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#define COLUMN_WIDTH 25

using namespace std;

template<typename charT, typename traits = std::char_traits<charT> >
class center_helper {
	std::basic_string<charT, traits> str_;
public:
	center_helper(std::basic_string<charT, traits> str) : str_(str) {}
	template<typename a, typename b>
	friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper<a, b>& c);

};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper<charT, traits> centered(std::basic_string<charT, traits> str) {
	return center_helper<charT, traits>(str);
}

// redeclare for std::string directly so we can support anything that implicitly converts to std::string
center_helper<std::string::value_type, std::string::traits_type> centered(const std::string& str) {
	return center_helper<std::string::value_type, std::string::traits_type>(str);
}

template<typename charT, typename traits>
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper<charT, traits>& c) {
	std::streamsize w = s.width();
	if (w > c.str_.length()) {
		std::streamsize left = (w + c.str_.length()) / 2;
		s.width(left);
		s << c.str_;
		s.width(w - left);
		s << "";
	}
	else {
	}
	return s;
}

Customer registerCustomer() {
	ifstream InputMemberFile("member.txt");

	string name, contactNo;
	double topUpValue;
	cout << "Please enter your info: \n";
	cout << "Name: ";
	cin.ignore(1, '\n');

	getline(cin, name);
	cout << "Contact Number: ";
	cin >> contactNo;
	cout << "Top Up Value (Must be greater than RM20): RM";
	cin >> topUpValue;

	bool greaterThan20Flag = false;
	if (cin && topUpValue >= 20) {
		greaterThan20Flag = true;
	}
	while (!cin || !greaterThan20Flag) {
		if (!cin) {

			cout << "Please enter a number!\n";
		}
		else {
			cout << "Must be at least RM20! \n";

		}
		cout << "Top Up Value (Must be at least RM20): RM";

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		greaterThan20Flag = false;

		cin >> topUpValue;
		if (cin && topUpValue >= 20) {
			greaterThan20Flag = true;
		}
	}

	return Customer(name, contactNo, topUpValue);

}
void writeMemberToFile(Customer customer) {
	// Create and open a text file
	ofstream MemberFile("member.txt", std::ios_base::app | std::ios_base::out);
	ifstream InputMemberFile("member.txt");
	int noOfLines;
	std::string line;

	bool isEmpty = InputMemberFile.peek() == EOF;

	if (isEmpty) MemberFile << setw(50) << centered("Customer Name") << setw(COLUMN_WIDTH) << centered("Card Number") << setw(COLUMN_WIDTH) << centered("Contact Number") << setw(COLUMN_WIDTH) << centered("Membership Point") << setw(COLUMN_WIDTH) << centered("Value") << endl;
	// Write to the file
	MemberFile << setw(50) << centered(customer.getName()) << setw(COLUMN_WIDTH) << centered(customer.getCardNo()) << setw(COLUMN_WIDTH) << centered(customer.getContactNo()) << setw(COLUMN_WIDTH) << centered(to_string(customer.getPoint())) << setw(COLUMN_WIDTH) << centered(to_string(customer.getTopUpValue())) << endl;

	// Close the file
	MemberFile.close();
	InputMemberFile.close();
}

void cardTopUp()
{
	int id;
	bool validInput;


	cout << "Please enter your membership card number: ";
	cin >> id;

	int topupamount;
	char confirmation;
	char conttopup;
	double balance = 0.0;


	do {
	menu:
		cout << "\nPlease select top up amount:" << endl;
		cout << " -------------------------------- " << endl;
		cout << setw(10) << "> RM5 " << endl;
		cout << setw(10) << "> RM10" << endl;
		cout << setw(10) << "> RM30" << endl;
		cout << setw(10) << "> RM50" << endl;
		cout << " -------------------------------- " << endl;
		cout << "enter your amount :RM";
		cin >> topupamount;

		if (cin || topupamount == 5 || topupamount == 10 || topupamount == 30 || topupamount == 50) {
			cout << "\n\nNotice: RM0.50 will be deducted for service charges." << endl;
			cout << "Do you confirm top up RM" << topupamount << " into your membership card? \nYES(Y) or NO(N)  >> ";
			cin >> confirmation;
			validInput = true;

		}
		else
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nInvalid Amount! Please select amount from the list!\n\n\n";
			validInput = false;
		}
	} while (!validInput);





	if (confirmation != 'Y') {
		cout << "Do you want to continue to top up? (Y/N)";
		cin >> conttopup;

		if (conttopup != 'Y') {
			cout << "----------------------------------------------------------\n";
			cout << setw(40) << "TOP UP MODULE END\n";
			cout << "----------------------------------------------------------\n";
		}
		else {
			goto menu;
		}
	}
	else {
		balance += (double)topupamount - 0.5;
		cout << "\nYou have successfully top up RM" << topupamount << " into your membership card!" << endl;
		cout << "---------------------------------------" << endl;
		cout << "|Balance :RM" << setw(26) << left << fixed << setprecision(2) << showpoint << balance << "|" << endl;
		cout << "---------------------------------------" << endl;
	}


}
void membershipPoint(double purchaseAmount, int& memberPoint, double& balanceAmt) {
	int selection;
	string input;

	cout << "Enter your selection" << endl;
	cout << "1) Use sufficient balance to pay" << endl;
	cout << "2) Use redeem point to pay" << endl;

	while (true) {
		cin >> input;

		try {
			selection = stoi(input);

			if (selection != 1 && selection != 2) {
				cout << "Invalid input. Please enter 1 or 2." << endl;
			}
			else {
				break;
			}
		}
		catch (const std::invalid_argument&) {
			cout << "Invalid input. Please enter a valid number (1 or 2)." << endl;
		}
	}

	if (selection == 1) {
		if (balanceAmt < purchaseAmount) {
			cout << "Insufficient Balance" << endl;
			cout << "Enter your selection" << endl;
			cout << "1) Top-up to pay" << endl;
			cout << "2) Cancel order" << endl;

			while (true) {
				cin >> selection;

				if (selection == 1) {
					cout << "Open topupModule" << endl;
					// Implement your top-up functionality here
					break;
				}
				else if (selection == 2) {
					cout << "Payment canceled" << endl;
					purchaseAmount = 0;
					break;
				}
				else {
					cout << "Please enter the correct input (1 or 2):" << endl;
				}
			}
		}
		else {
			balanceAmt -= purchaseAmount;
		}
	}
	else if (selection == 2) {
		int pointsNeeded = ceil(purchaseAmount * 100); // Points required for the purchase
		if (memberPoint < pointsNeeded) {
			cout << "***Insufficient Points\n\n" << endl;
			cout << "Enter your selection" << endl;
			cout << "1) Top-up to pay" << endl;
			cout << "2) Cancel order" << endl;

			while (true) {
				cin >> selection;

				if (selection == 1) {
					cout << "Open topupModule" << endl;
					// Implement your top-up functionality here
					break;
				}
				else if (selection == 2) {
					cout << "Payment canceled" << endl;
					purchaseAmount = 0;
					break;
				}
				else {
					cout << "Please enter the correct input (1 or 2):" << endl;
				}
			}

		}
		else {
			memberPoint -= pointsNeeded;
		}
	}
}

double getCurrentTopUpValueFromFile(string cardNo) {
	ifstream fileInput;
	fileInput.open("member.txt");
	string line;
	string found = "";
	unsigned int curLine = 0;
	while (getline(fileInput, line)) { // I changed this, see below
		curLine++;
		if (line.find("ABC000001", 0) != string::npos) {
			//cout << "found: " << cardNo << "line: " << curLine << endl;

			char separator = ' ';
			int i = 0;

			// Temporary string used to split the string.
			string s;
			while (line[i] != '\0') {
				if (line[i] != separator) {
					// Append the char to the temp string.
					s += line[i];
				}

				else {
					//	cout << s << endl;
					s.clear();
				}
				i++;

			}

			// Output the last stored word.
			cout << s << endl;
			found = s;
		}
	}

	cout << "HERE" << found;
	return 0.0;
};
