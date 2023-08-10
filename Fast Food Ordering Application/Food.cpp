#include "Customer.h"
#include "Food.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iostream>
#define COLUMN_WIDTH 25

using namespace std;
template<typename charT, typename traits = std::char_traits<charT> >
class center_helper2 {
	std::basic_string<charT, traits> str_;
public:
	center_helper2(std::basic_string<charT, traits> str) : str_(str) {}
	template<typename a, typename b>
	friend std::basic_ostream<a, b>& operator<<(std::basic_ostream<a, b>& s, const center_helper2<a, b>& c);

};

template<typename charT, typename traits = std::char_traits<charT> >
center_helper2<charT, traits> centered2(std::basic_string<charT, traits> str) {
	return center_helper2<charT, traits>(str);
}

// redeclare for std::string directly so we can support anything that implicitly converts to std::string
center_helper2<std::string::value_type, std::string::traits_type> centered2(const std::string& str) {
	return center_helper2<std::string::value_type, std::string::traits_type>(str);
}

template<typename charT, typename traits>
std::basic_ostream<charT, traits>& operator<<(std::basic_ostream<charT, traits>& s, const center_helper2<charT, traits>& c) {
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

void foodSelection() {

	vector<Food> set_foods;
	set_foods.push_back(Food("Big Breakfast : Ham + Sausage + Fried Egg + Toast", 12.00, 1));
	set_foods.push_back(Food("McChicken Set: Cola + Chicken Burger + French Fries", 15.00, 2));
	set_foods.push_back(Food("McFillet Set: Cola + Fish Burger + French Fries", 21.50, 3));

	vector<Food> ala_carte_foods;
	ala_carte_foods.push_back(Food("Big Breakfast : Ham + Sausage + Fried Egg + Toast", 12.00, 4));
	ala_carte_foods.push_back(Food("McChicken Set: Cola + Chicken Burger + French Fries", 15.00, 5));
	ala_carte_foods.push_back(Food("McFillet Set: Cola + Fish Burger + French Fries", 21.50, 6));

	vector<int> orders;
	bool flag = true;
	bool isCheckout = true;

	while (flag) {
		int orderChoice, setAlaCarteChoice;
		cout << "Previous Page (0) Take Away (1) Dine In (2)\n";
		cin >> orderChoice;
		while (!cin || orderChoice < 0 || orderChoice>2) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice\n";
			cin >> orderChoice;
		}

		if (orderChoice == 0) {
			isCheckout = false;
			break;
		}

		bool orderFlag = true;
		while (orderFlag) {
			switch (orderChoice) {
			case 1:
				cout << "TAKE AWAY:\n";
				break;
			case 2:
				cout << "DINE IN:\n";
				break;
			}
			cout << "Return to previous page (0) Set (1) Ala Carte (2) Show Orders (3) Delete An Order (4) Proceed To Checkout (5) \n";
			cin >> setAlaCarteChoice;
			while (!cin || setAlaCarteChoice < 0 || setAlaCarteChoice>5) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid choice\n";
				cin >> setAlaCarteChoice;
			}
			if (setAlaCarteChoice == 1) {


				cout << "0. Return to previous page\n";
				for (auto it = set_foods.begin(); it != set_foods.end(); ++it) {

					auto i = std::distance(set_foods.begin(), it);
					cout << (*it).getId() << ". " << (*it).getName() << "\n";
				}

				cout << "Please Select Your Choice (number): ";
				int choice, quantity;
				cin >> choice;
				if (choice == 0) continue;
				while (!cin || choice < 0 || choice>set_foods.size()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice\n";
					cin >> choice;
				}
				cout << "Please Enter Your Quantity: ";
				cin >> quantity;
				while (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice\n";
					cin >> quantity;
				}
				for (int i = 0; i < quantity; i++) {
					orders.push_back(choice);
				}
				//	cout << "Enter Y to continue order, other to quit ordering\n";
				//	string isQuit;
				//	cin >> isQuit;
					//if (isQuit == "Y") {
					///	orderFlag = false;
					//}



			}
			else if (setAlaCarteChoice == 2) {
				cout << "0. Return to previous page\n";

				for (auto it = ala_carte_foods.begin(); it != ala_carte_foods.end(); ++it) {

					auto i = std::distance(ala_carte_foods.begin(), it);
					cout << (*it).getId() << ". " << (*it).getName() << "\n";
				}

				cout << "Please Select Your Choice (number): ";
				int choice, quantity;
				cin >> choice;
				if (choice == 0) continue;

				while (!cin || (choice != 0 && (choice <= set_foods.size() || choice > set_foods.size() + ala_carte_foods.size()))) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice\n";
					cin >> choice;
				}
				cout << "Please Enter Your Quantity: ";
				cin >> quantity;
				while (!cin) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice\n";
					cin >> quantity;
				}
				for (int i = 0; i < quantity; i++) {
					orders.push_back(choice);
				}
				orders.push_back(choice);
				//cout << "Enter Y to continue order, other to quit ordering\n";
			//	string isQuit;
			//	cin >> isQuit;
				//if (isQuit == "Y") {
				//	orderFlag = false;
				//}

			}
			else if (setAlaCarteChoice == 4) {
				cout << "0. Return to previous page\n";
				for (auto it = orders.begin(); it != orders.end(); ++it) {

					auto i = std::distance(orders.begin(), it);
					if ((*it) > set_foods.size()) {
						cout << i + 1 << ". " << ala_carte_foods.at((*it) - set_foods.size() - 1).getName() << "\n";

					}
					else {
						cout << i + 1 << ". " << set_foods.at((*it)).getName() << "\n";

					}
				}
				int choiceToDelete;
				cout << "Enter the number of the order to be deleted: ";
				cin >> choiceToDelete;
				if (choiceToDelete == 0) continue;
				while (!cin || choiceToDelete<0 || choiceToDelete>orders.size()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid choice\n";
					cin >> setAlaCarteChoice;
				}

				orders.erase(orders.begin() + choiceToDelete - 1);
			}
			else if (setAlaCarteChoice == 3) {
				for (auto it = orders.begin(); it != orders.end(); ++it) {

					auto i = std::distance(orders.begin(), it);
					if ((*it) > set_foods.size()) {
						cout << i + 1 << ". " << ala_carte_foods.at((*it) - set_foods.size() - 1).getName() << "\n";

					}
					else {
						cout << i + 1 << ". " << set_foods.at((*it)).getName() << "\n";

					}
				}

			}
			else if (setAlaCarteChoice == 5) {

				orderFlag = false;
				flag = false;

			}
			else if (setAlaCarteChoice == 0) {
				string choice;
				cout << "Are you sure to cancel your order and return to previous page? (Y)";
				cin >> choice;
				if (choice == "Y" || choice == "y")orderFlag = false;
			}
		}

	}

	if (isCheckout) {
		cout << "Proceeding to checkout";
		vector<Food>foods;
		foods.reserve(set_foods.size() + ala_carte_foods.size()); // preallocate memory
		foods.insert(foods.end(), set_foods.begin(), set_foods.end());
		foods.insert(foods.end(), ala_carte_foods.begin(), ala_carte_foods.end());
		payment(foods, orders);
	//	return orders;
	}


	
}
void pushBack(string &str1, string str2)
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
void payment(vector<Food>foods, vector<int>orders) {

	double total = 0;
	cout << setw(50) << 'NAME' << setw(10) << "QUANTITY" << setw(10)<<"SUBTOTAL"<< endl;
	for (auto it = foods.begin(); it != foods.end(); ++it) {

		auto i = std::distance(foods.begin(), it);
		int count = std::count(orders.begin(), orders.end(), (*it).getId());
		if (count > 0) {
			total += count * (*it).getPrice();
			cout << setw(50) << (*it).getName() << setw(10) << count << count * (*it).getPrice() << endl;;
		}
	}

	cout << "TOTAL: " << total<<endl;
	cout << "Please enter your card number to proceed: ";

	string cardNo;
	cin >> cardNo;
	while (cardNo.length() != 9) {
		cout << "Invalid format! ";
		cout << "Please enter your card number again to proceed: ";;
		cin >> cardNo;
	}
	
	bool flagToProceed = false;
	double currentValue = 0;
	int currentPoint = 0;
	string deleteLine;

	while (!flagToProceed) {
		ifstream fileInput;
		fileInput.open("member.txt");
		string line;
		unsigned int curLine = 0;
		while (getline(fileInput, line)) { 
			if (line.find(cardNo, 0) != string::npos) {
				deleteLine = line;
			//	cout << "FOUND";
				flagToProceed = true;
				break;
			}
			else {
				

			}



		}
		if (flagToProceed) break;
		cout << "NOT FOUND";
		cout << "Please enter your card number to proceed: ";
		fileInput.close();
		string cardNo;
		cin >> cardNo;
	}


	int selection;
	int pointsNeeded = ceil(total * 100); // Points required for the purchase


	

		bool goOnFlag = false;
		while(!goOnFlag) {
			cout << "Enter your selection" << endl;
			cout << "1) Use sufficient balance to pay" << endl;
			cout << "2) Use redeem point to pay" << endl;
			cin >> selection;
			if (selection != 1 && selection != 2) {
				cout << "Invalid input. Please enter 1 or 2." << endl;
			}
			else {
				if (selection == 1) {
					currentValue = getCurrentTopUpValueFromFile(cardNo);
					if (currentValue < total) {
						cout << "Not enough balance!\n";
					//	continue;

					}
					else {
						goOnFlag = true;
						break;
					}
				}
				else if (selection == 2) {
					 currentPoint = getCurrentPointFromFile(cardNo);
					if (currentPoint < pointsNeeded) {
						cout << "Not enough points!\n";
					//	continue;

					}
					else {
						goOnFlag = true;

						break;
					}
				}
			}
		}
		
	

	// use value to purchase
	if (selection == 1) {
		string line;

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
			//else {
			//	cout << "HEREEEE" << line << endl;

			//	cout << "FOUND\n";
			//}




		}
		fin.close();
		string name, cardNo, contactNo;
		int point;
		double value = currentValue - total;

		//cout << "CURRNET VALUE" << currentValue;
		std::string s = deleteLine;
		std::stringstream ss(s);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> v(begin, end);
		for (int i = 0; i < v.size() - 4; i++) {
			pushBack(name,v.at(i));
		}
		// std::copy(v.begin(), v.end() - 5, name);
		out_file << setw(50) << centered2(name) << setw(COLUMN_WIDTH) << centered2(v.at(v.size() - 4)) << setw(COLUMN_WIDTH) <<centered2(v.at(v.size() - 3)) << setw(COLUMN_WIDTH) << centered2(v.at(v.size() - 2)) << setw(COLUMN_WIDTH) << centered2(to_string(value)) << endl;
		out_file.close();
		ofstream out_file2{ "member.txt",  std::ios::trunc };
		string line2;
		ifstream fin2;
		fin2.open("copy.txt");
		while (getline(fin2, line2)) {

			out_file2 << line2 << "\n";


		}
	}
		// use membership point to purchase
	else if (selection == 2) {
		
		string line;

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
			//else {
			//	cout << "HEREEEE" << line << endl;

			//	cout << "FOUND\n";
			//}




		}
		fin.close();
		string name, cardNo, contactNo;
		int point;
		double newPoint = currentPoint - pointsNeeded;

		//cout << "CURRNET VALUE" << currentValue;
		std::string s = deleteLine;
		std::stringstream ss(s);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> v(begin, end);
		for (int i = 0; i < v.size() - 4; i++) {
			pushBack(name, v.at(i));
		}
		//std::copy(v.begin(), v.end()-5,name);
		out_file << setw(50) << centered2(name) << setw(COLUMN_WIDTH) << centered2(v.at(v.size() - 4)) << setw(COLUMN_WIDTH) << centered2(v.at(v.size() - 3)) << setw(COLUMN_WIDTH) << centered2(to_string(newPoint)) << setw(COLUMN_WIDTH) << centered2(v.at(v.size() - 1)) << endl;
		out_file.close();
		ofstream out_file2{ "member.txt",  std::ios::trunc };
		string line2;
		ifstream fin2;
		fin2.open("copy.txt");
		while (getline(fin2, line2)) {

			out_file2 << line2 << "\n";


		}
		
	}

	cout << "Payment is successful!\n";
	

	}

