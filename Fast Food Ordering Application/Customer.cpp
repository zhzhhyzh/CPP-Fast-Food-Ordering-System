#include "Customer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cctype>
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

inline std::string trim(const std::string& s)
{
	auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c) {return std::isspace(c); });
	auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c) {return std::isspace(c); }).base();
	return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}
Customer registerCustomer() {
	ifstream InputMemberFile("member.txt");

	string name, contactNo;
	double topUpValue;
	cout << "Please enter your info: \n";
	cin.ignore(1, '\n');


	bool validateName = false;
	while (!validateName) {
		cout << "Name (Only letter accepted): ";
	getline(cin, name);
	if (name.length() > 50) {
		cout << "Please register with a shorter name\n";
		continue;
	}
	for (int i = 0; i < name.length(); i++)
	{
		if (!isalpha(name[i])&&name[i]!=' ')
		{
			cout << "*Name must contain letters only\n";
		//	cin.clear();
		//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		else if (isalpha(name[i]) and i == name.length() - 1) {
			validateName = true;
		}

	}
	}

	bool validateContactNo = false;
	while (!validateContactNo) {

		cout << "Contact Number (0123456789): ";
		cin >> contactNo;
		if (contactNo.length() < 10|| contactNo.length()>11) {
			cout << "Invalid phone number\n";
			continue;
		}
		for (int i = 0; i < contactNo.length(); i++)
		{
			if (!isdigit(contactNo[i]))
			{
				cout << "Invalid phone number\n";
				//	cin.clear();
				//	cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
			else if (isdigit(contactNo[i]) and i == contactNo.length() - 1) {
				validateContactNo = true;
			}

		}
	}
	
	string input;

	while (true) {
		cout << "Top Up Value (Must be at least RM20): RM";
		cin >> input;

		// Check if the entire input consists of digits
		bool isNumeric = true;
		for (char c : input) {
			if (!isdigit(c)) {
				isNumeric = false;
				break;
			}
		}

		if (isNumeric && (topUpValue = stod(input)) >= 20 && topUpValue <= 9999) {
			break; // Valid input, exit the loop.
		}

		cout << "Invalid input. Please enter a numeric value between RM20 and RM9999." << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return Customer(name, contactNo, topUpValue);

}
void pushBack2(string& str1, string str2)
{
	// Appends character by character str2
	// at the end of str1
	for (int i = 0; str2[i] != '\0'; i++)
	{
		str1.push_back(str2[i]);
	}
	//cout << "After push_back : ";
	//cout << str1;
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


double getCurrentTopUpValueFromFile(string cardNo) {
	ifstream fileInput;
	fileInput.open("member.txt");
	string line;
	string found = "";
	unsigned int curLine = 0;
	while (getline(fileInput, line)) { // I changed this, see below
		curLine++;
		if (line.find(cardNo, 0) != string::npos) {
			//cout << "found: " << cardNo << "line: " << curLine << endl;

			char separator = ' ';
			int i = 0;

			// Temporary string used to split the string.
			string s;
			line;
			line = trim(line);
			while (i < line.length() - 1) {
				if (line[i] != separator) {
					// Append the char to the temp string.
					s += line[i];	
				}

				else {
					//	cout << s << endl;
					s.clear();
				}
				i++;
				//cout << "HERE" << s;

			}

			// Output the last stored word.
			//cout << s << endl;

			found = s;

			return stod(found);
		}
	}

	return 0.0;
};
int getCurrentPointFromFile(string cardNo){
	ifstream fileInput;
	fileInput.open("member.txt");
	string line;
	string found = "";
	unsigned int curLine = 0;
	while (getline(fileInput, line)) { // I changed this, see below
		curLine++;
		if (line.find(cardNo, 0) != string::npos) {
			//cout << "found: " << cardNo << "line: " << curLine << endl;

			char separator = ' ';
			int i = 0;

			// Temporary string used to split the string.
			string s;
			line = line.substr(0, line.length() - COLUMN_WIDTH);
			line = trim(line);
	//		cout << "HERE" << line;
			while (i < line.length()) {
				if (line[i] != separator) {
					// Append the char to the temp string.
					s += line[i];
				}

				else {
					//	cout << s << endl;
					s.clear();
				}
				i++;
				//cout << "HERE" << s;

			}

			// Output the last stored word.
			// cout << s << endl;

			found = s;

			return stoi(found);
		}
	}

	return 0;
}

void updatePoint(string cardNo, int newPoint) {
	int currentPoint = getCurrentPointFromFile(cardNo);

	string line;
	string deleteLine;
	ifstream fin;
	fin.open("member.txt");
	// cout << deleteLine;
	ofstream out_file{ "copy.txt",  std::ios::trunc };


	while (getline(fin, line)) {
		//cout << "HEREEEE" << line << endl;
		//cout << line << endl;
		//cout << cardNo;
		if (line.find((cardNo), 50) == string::npos) {
			//line.replace(0, line.length(), "");

			out_file << line << "\n";

		}
		else {
			deleteLine = line;
		}




	}
	fin.close();
	string name, contactNo;

	//cout << "CURRNET VALUE" << currentValue;
	std::string s = deleteLine;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;

	std::vector<std::string> v(begin, end);
	for (int i = 0; i < v.size() - 4; i++) {
		pushBack2(name, v.at(i) + " ");
	}
	//std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	out_file << setw(50) << centered(name) << setw(COLUMN_WIDTH) << centered(v.at(v.size() - 4)) << setw(COLUMN_WIDTH) << centered(v.at(v.size() - 3)) << setw(COLUMN_WIDTH) << centered(to_string(newPoint)) << setw(COLUMN_WIDTH) << centered(v.at(v.size() - 1)) << endl;
	out_file.close();
	ofstream out_file2{ "member.txt",  std::ios::trunc };
	string line2;
	ifstream fin2;
	fin2.open("copy.txt");
	while (getline(fin2, line2)) {

		out_file2 << line2 << "\n";


	}
}

void updateValue(string cardNo, double newValue) {


	string line;
	string deleteLine;
	ifstream fin;
	fin.open("member.txt");
	// cout << deleteLine;
	ofstream out_file{ "copy.txt",  std::ios::trunc };

	while (getline(fin, line)) {
		//cout << "HEREEEE" << line << endl;
		//cout << line << endl;
		//cout << cardNo;
		if (line.find((cardNo), 50) == string::npos) {
			//line.replace(0, line.length(), "");

			out_file << line << "\n";

		}
		else {
			deleteLine = line;
		}
		//else {
		//	cout << "HEREEEE" << line << endl;

		//	cout << "FOUND\n";
		//}




	}
	fin.close();
	string name, contactNo;
	int point;

	//cout << "CURRNET VALUE" << currentValue;
	std::string s = deleteLine;
	std::stringstream ss(s);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> v(begin, end);
	for (int i = 0; i < v.size() - 4; i++) {
		pushBack2(name, v.at(i) + " ");
	}
	//std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	out_file << setw(50) << centered(name) << setw(COLUMN_WIDTH) << centered(v.at(v.size() - 4)) << setw(COLUMN_WIDTH) << centered(v.at(v.size() - 3)) << setw(COLUMN_WIDTH) << centered(v.at(v.size() - 2)) << setw(COLUMN_WIDTH) << centered(to_string(newValue)) << endl;
	out_file.close();
	ofstream out_file2{ "member.txt",  std::ios::trunc };
	string line2;
	ifstream fin2;
	fin2.open("copy.txt");
	while (getline(fin2, line2)) {

		out_file2 << line2 << "\n";

	}


}

void cardTopUp(string passedInCardNo)
{
	double balance = 0.0; //should be call out
	string id;
	bool validInput = false;
	bool validID = false;


	string cardNo;
	if (passedInCardNo.length()>0) {
		cardNo = passedInCardNo;
	}
	else {
		cout << "Please enter your card number to proceed: ";;
		cin >> cardNo;
	}
	
	while (cardNo.length() != 9) {
		cout << "Invalid format! ";
		cout << "Please enter your card number again: ";;
		cin >> cardNo;
	}

	bool flagToProceed = false;
	string deleteLine;

	while (!flagToProceed) {
		ifstream fileInput;
		fileInput.open("member.txt");
		string line;
		unsigned int curLine = 0;
		while (getline(fileInput, line)) {
			//cout << line.find("ABC000002") << endl;
			//cout << cardNo << endl;
			if (line.find(cardNo, 0) != string::npos) {
				deleteLine = line;
				//	cout << "FOUND";
				if(passedInCardNo.length() <= 0)cout << "\nMember found\n";
				flagToProceed = true;
				//cout << "FOUNDDD";
				break;
			}
			else {


			}



		}
		if (flagToProceed) break;
		cout << "NOT FOUND!\n";
		cout << "Please enter your card number again: ";
		fileInput.close();
		// string cardNo;
		cin >> cardNo;
		while (cardNo.length() != 9) {
			cout << "Invalid format! ";
			cout << "Please enter your card number again: ";;
			cin >> cardNo;
		}
	}
	balance = getCurrentTopUpValueFromFile(cardNo);
	int topupamount = 0;
	string confirmation;
	string conttopup;
	bool validConfirmation = false;

	do {
	menu:
		cout << "\n=======================================" << endl;
		cout << "|          MTaco Topup System         |" << endl;
		cout << "=======================================" << endl;
		cout << "| Balance : RM" << setw(23) << fixed << setprecision(2) << showpoint << balance << " |" << endl;
		cout << "=======================================" << endl;
		cout << "|          Top Up Your Account        |" << endl;
		cout << "=======================================" << endl;
		cout << "| 1. RM5                              |" << endl;
		cout << "| 2. RM10                             |" << endl;
		cout << "| 3. RM30                             |" << endl;
		cout << "| 4. RM50                             |" << endl;
		cout << "=======================================" << endl;

		int choice = 0;
		string input;

		cout << "Enter your choice (1-4): ";

		while (true) {
			getline(cin, input);

			// Create a stringstream to convert the input to an integer
			stringstream ss(input);
			if (ss >> choice && ss.eof()) {
				// Input is a valid integer between 1 and 4
				break;
			}
			else {
				// Input is invalid, prompt for valid input
				cout << "Invalid input! Please enter a valid choice (1-4): ";
			}
		}

		switch (choice) {
		case 1:
			topupamount = 5;
			cout << "\n\nNotice: RM0.50 will be deducted for service charges." << endl;
			cout << "Confirm to top up RM" << topupamount << " into your membership card? \n\nYES(Y) or NO(N)  >> ";
			cin >> confirmation;
			while (!validConfirmation) {
				if (confirmation == "Y" || confirmation == "y") {
					system("CLS");
					validInput = true;
					validConfirmation = true;
					goto displayBalance;
					break;
				}
				else if (confirmation == "N" || confirmation == "n") {
					system("CLS");
					validConfirmation = true;
					goto conttopup;
					break;
				}
				else {
					cout << "Invalid input!\n";
					cout << "Confirm to top up RM" << topupamount << " into your membership card? \nYES(Y) or NO(N)  >> ";
					cin >> confirmation;
				}
			}
			break;
		case 2:
			topupamount = 10;
			cout << "\n\nNotice: RM0.50 will be deducted for service charges." << endl;
			cout << "Confirm to top up RM" << topupamount << " into your membership card? \n\nYES(Y) or NO(N)  >> ";
			cin >> confirmation;
			while (!validConfirmation) {
				if (confirmation == "Y" || confirmation == "y") {
					system("CLS");
					validInput = true;
					validConfirmation = true;
					goto displayBalance;
					break;
				}
				else if (confirmation == "N" || confirmation == "n") {
					system("CLS");
					validConfirmation = true;
					goto conttopup;
					break;
				}
				else {
					cout << "Invalid input!\n";
					cout << "Confirm to top up RM" << topupamount << " into your membership card? \nYES(Y) or NO(N)  >> ";
					cin >> confirmation;
				}
			}
		case 3:
			topupamount = 30;
			cout << "\n\nNotice: RM0.50 will be deducted for service charges." << endl;
			cout << "Confirm to top up RM" << topupamount << " into your membership card? \n\nYES(Y) or NO(N)  >> ";
			cin >> confirmation;
			while (!validConfirmation) {
				if (confirmation == "Y" || confirmation == "y") {
					system("CLS");
					validInput = true;
					validConfirmation = true;
					goto displayBalance;
					break;
				}
				else if (confirmation == "N" || confirmation == "n") {
					system("CLS");
					validConfirmation = true;
					goto conttopup;
					break;
				}
				else {
					cout << "Invalid input!\n";
					cout << "Confirm to top up RM" << topupamount << " into your membership card? \nYES(Y) or NO(N)  >> ";
					cin >> confirmation;
				}
			}
		case 4:
			topupamount = 50;
			cout << "\n\nNotice: RM0.50 will be deducted for service charges." << endl;
			cout << "Confirm to top up RM" << topupamount << " into your membership card? \n\nYES(Y) or NO(N)  >> ";
			cin >> confirmation;
			while (!validConfirmation) {
				if (confirmation == "Y" || confirmation == "y") {
					system("CLS");
					validInput = true;
					validConfirmation = true;
					goto displayBalance;
					break;
				}
				else if (confirmation == "N" || confirmation == "n") {
					system("CLS");
					validConfirmation = true;
					goto conttopup;
					break;
				}
				else {
					cout << "Invalid input!\n";
					cout << "Confirm to top up RM" << topupamount << " into your membership card? \nYES(Y) or NO(N)  >> ";
					cin >> confirmation;
				}
			}
		default:
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << "\nInvalid Amount! Please select amount from the list!\n\n\n";
			validInput = false;
			break;
		}
	} while (!validInput);





	//	if (confirmation !="Y" && confirmation != "y") {
conttopup:
	cout << "Do you want to continue to top up? (Y/N) >> ";
	cin >> conttopup;

	if (conttopup == "N" || conttopup == "n") {
		cout << "----------------------------------------------------------\n";
		cout << setw(35)<<right << "TOP UP MODULE END"<<endl;
		cout << "----------------------------------------------------------\n";
		system("CLS");
		return;
	}
	else if (conttopup == "Y" || conttopup == "y") {
		system("CLS");

		goto menu;
	}
	else  {
		cout << "Invalid Input!\n";
		goto conttopup;
	}
	//
		//}
	//	else {

displayBalance:
	balance += (double)topupamount - 0.5;
	updateValue(cardNo, balance);
	cout << "\nYou have successfully top up RM" << topupamount << " into your membership card (" << cardNo << ") !" << endl;
	cout << "---------------------------------------" << endl;
	cout << "|Balance : RM" << setw(26) << left << fixed << setprecision(2) << showpoint << balance << "|" << endl;
	cout << "---------------------------------------" << endl;
	goto conttopup;
	//}
	//return balance;


}
