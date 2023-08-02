#include <iostream>
#include <cstdlib>
#include <string> // header file for string
#include <iostream>
#include <fstream>
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
		s << c.str_;
	}
	return s;
}
class Customer {
public:
	Customer(string name, string contactNo, double topUpValue) {
		this->name = name;
		this->contactNo = contactNo;
		this->topUpValue = topUpValue;
		string randomNumber = to_string(rand() % 6);
		int paddedLength = 6;
		randomNumber.insert(randomNumber.begin(), paddedLength - randomNumber.size(), '0');
		this->cardNo = "ABC" + randomNumber;
		}
	string getName() {
		return this->name;
	}
	string getCardNo() {
		return this->cardNo;
	}
	string getContactNo() {
		return this->contactNo;
	}
	int getPoint() {
		return this->point;
	}
	double getTopUpValue() {
		return this->topUpValue;
	}
private:
	string name;
	string cardNo;
	string contactNo;
	double topUpValue;
	int point = 0;
};
Customer registerCustomer() {
	ifstream InputMemberFile("member.txt");

	string name, contactNo;
	double topUpValue;
	cout << "Please enter your info: \n";
	cout << "Name: " ;
	getline(cin, name);
	cout << "Contact Number: " ;
	cin >> contactNo;
	cout << "Top Up Value (Must be greater than RM20): RM" ;
	cin >> topUpValue;	

	bool greaterThan20Flag = false;
	if (cin&&topUpValue>=20) {
		greaterThan20Flag = true;
	}
	while (!cin|| !greaterThan20Flag) {
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
	ofstream MemberFile("member.txt",std::ios_base::app | std::ios_base::out);
	ifstream InputMemberFile("member.txt");

	bool isEmpty = InputMemberFile.peek() == EOF;
	if (isEmpty) MemberFile << setw(50) << centered("Customer Name") << setw(COLUMN_WIDTH) << centered("Card Number") << setw(COLUMN_WIDTH) << centered("Contact Number") << setw(COLUMN_WIDTH) << centered("Membership Point") << setw(COLUMN_WIDTH) << centered("Value") << endl;
	// Write to the file
	MemberFile << setw(50) << centered(customer.getName()) << setw(COLUMN_WIDTH) << centered(customer.getCardNo()) << setw(COLUMN_WIDTH) << centered(customer.getContactNo())<< setw(COLUMN_WIDTH) << centered(to_string(customer.getPoint())) << setw(COLUMN_WIDTH) << centered(to_string(customer.getTopUpValue()))<<endl;

	// Close the file
	MemberFile.close();
	InputMemberFile.close();
}

int main() {

	Customer customer
		= registerCustomer();
	cout << "Hi " << customer.getName()<<", congratulations on becoming one of our members!";
	
	writeMemberToFile(customer);
	return 0;
}
