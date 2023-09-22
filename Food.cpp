#include "Customer.h"
#include "Food.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <stdlib.h>

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

double displayOrders(vector<Food>foods, vector<int>orders, int type) {
	double total = 0;
	cout << setw(10) << centered2("ID") << setw(50) << centered2("NAME") << setw(35) << centered2("QUANTITY") << setw(35) << centered2("SUBTOTAL") << endl;

	for (auto it = foods.begin(); it != foods.end(); ++it) {

		auto i = std::distance(foods.begin(), it);
		int count = std::count(orders.begin(), orders.end(), (*it).getId());
		if (count > 0) {
			total += count * (*it).getPrice();
			ostringstream str1;
			str1 << round(count * (*it).getPrice() * 100) / 100;
			// Sending a number as a stream into output
			// string
			cout << setw(10) << centered2(to_string(int((*it).getId()))) << setw(50) << centered2((*it).getName()) << setw(35) << centered2(to_string(count)) << setw(35) << centered2(str1.str()) << endl;;
		}
	}


	// 1 is take away, 2 is dine in
	if (type == 1) {
		total += 2;
		cout << "\nPACKAGING FEE: RM2" << endl;
	}
	else if (type == 2) {
		ostringstream str1;

		// Sending a number as a stream into output
		// string
		str1 << round(total * 0.1 * 100) / 100;
		cout << "\nSERVICE CHARGE (10%): " << str1.str() << endl;
		total *= 1.1;
	}
	ostringstream str1;

	// Sending a number as a stream into output
	// string
	str1 << round(total * 100) / 100;

	cout << "TOTAL: RM" << str1.str() << endl;

	return total;
}
void pushBack(string& str1, string str2)
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

void payment(vector<Food>foods, vector<int>orders, int orderChoice) {

	// cout << setw(50) << centered2("NAME") << setw(10) << centered2("QUANTITY") << setw(10) << centered2("SUBTOTAL") << endl;
	double total = displayOrders(foods, orders, orderChoice);

	//cout << "TOTAL: " << total<<endl;
	cout << "Please enter your card number(ABCXXXXXX) to proceed: ";

	string cardNo;
	cin >> cardNo;
	while (cardNo.length() != 9) {
		cout << "Invalid format! ";
		cout << "Please enter your card number(ABCXXXXXX) again: ";;
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
				cout << "\nMember found\n";
				flagToProceed = true;
				break;
			}



		}
		if (flagToProceed) break;
		cout << "NOT FOUND!\n";
		cout << "Please enter your card number(ABCXXXXXX) again: ";
		fileInput.close();
		//string cardNo;
		cin >> cardNo;
	}

	int selection;
	
	
	int pointsNeeded = ceil(total * 100); // Points required for the purchase

	bool goOnFlag = false;

	while (!goOnFlag) {
		cout << "\nEnter your selection" << endl;
		cout << "1) Use sufficient balance to pay" << endl;
		cout << "2) Use redeem points to pay" << endl;
		cin >> selection;

		if (!cin || (selection != 1 && selection != 2)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter 1 or 2." << endl;
		}
		else {
			if (selection == 1) {
				currentPoint = getCurrentTopUpValueFromFile(cardNo);
				if (currentValue < total) {
					cout << "Current Balance is: " << currentValue << endl;
					cout << "Billing Total: " << total << endl;
					cout << "Not enough balance!\n";
					string wantTopUp;

					cout << "Do you want to top up now? (Y/N): ";
					cin >> wantTopUp;
					while (wantTopUp != "Y" && wantTopUp != "y" && wantTopUp != "N" && wantTopUp != "n") {
						cout << "Invalid input! Please enter Y or N: ";
						cin >> wantTopUp;
					}

					if (wantTopUp == "Y" || wantTopUp == "y") {
						system("CLS");
						cout << "\nProceeding to top up page\n";
						cin.clear();
						cardTopUp(cardNo);
					}
				}
				else {
					goOnFlag = true;
				}
			}
			else if (selection == 2) {
				currentPoint = getCurrentPointFromFile(cardNo);
					if (currentPoint < pointsNeeded) {
						cout << "Not enough points!\n";
					}
					else {
						goOnFlag = true;
					}
			}
		
		}
	}

	// use value to purchase
	if (selection == 1) {

		double value = currentValue - total;

		updateValue(cardNo, value);
	}
	// use membership point to purchase
	else if (selection == 2) {
		double newPoint = currentPoint - pointsNeeded;
		updatePoint(cardNo, newPoint);
	}
	system("CLS");
	double valueBalance = getCurrentTopUpValueFromFile(cardNo);
	int pointBalance = getCurrentPointFromFile(cardNo);
	cout << "Receipt:" << endl<<endl;

	displayOrders(foods, orders, orderChoice);
	cout << "---------------------------------------" << endl;
	cout << "|Balance : RM" << setw(26) << left << fixed << setprecision(2) << showpoint << valueBalance << "|" << endl;
	cout << "---------------------------------------" << endl;
	cout << "|Point   : " << setw(26) << left << pointBalance << "|" << endl;
	cout << "---------------------------------------" << endl;
	cout << "\nPayment is successful! Enjoy your meal!\n";
	system("pause");
	system("cls");

}




void foodSelection() {

	vector<Food> set_foods;
	set_foods.push_back(Food("Burrito + Beef Backribs + Filete de Salmon", 30.00, 1));
	set_foods.push_back(Food("Taco + Braised Australian Lamb Shank ", 25.00, 2));
	set_foods.push_back(Food("Soft-shell Taco + Grain-fed Rib Eye-Australia", 20.00, 3));

	vector<Food> ala_carte_foods;
	ala_carte_foods.push_back(Food("Chili Con Carne", 12.00, 4));
	ala_carte_foods.push_back(Food("Burrito", 13.00, 5));
	ala_carte_foods.push_back(Food("Las Carretas Fruit Punch ", 10.00, 6));

	// all foods grouped together
	vector<Food>foods;
	foods.reserve(set_foods.size() + ala_carte_foods.size()); // preallocate memory
	foods.insert(foods.end(), set_foods.begin(), set_foods.end());
	foods.insert(foods.end(), ala_carte_foods.begin(), ala_carte_foods.end());
	vector<int> orders;
	bool flag = true;
	bool isCheckout = true;
	
	int orderChoice, setAlaCarteChoice;
	while (flag) {
		while (true) {
			cout << "===============================" << endl;
			cout << "        ORDER FOOD" << endl;
			cout << "===============================" << endl;
			cout << "Previous Page (0)\nTake Away (1)\nDine In (2)\n";
			cout << "\nPlease enter your choice: ";

			if (!(cin >> orderChoice) || orderChoice < 0 || orderChoice > 2 || cin.peek() != '\n') {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\nInvalid choice. Please enter a valid option (0, 1, or 2)." << endl;
			}
			else {
				break;  // Valid input, exit the loop
			}
		}

		if (orderChoice == 0) {
			isCheckout = false;
			system("CLS");
			break;
		}

	order: bool orderFlag = true;
		while (orderFlag) {
			system("CLS");
			switch (orderChoice) {
			case 1:
				cout << "ORDER FOOD (TAKE AWAY)\n\n";
				break;
			case 2:
				cout << "ORDER FOOD (DINE IN):\n\n";
				break;
			}
			while (true) {
				cout << "=======================================" << endl;
				cout << "          Operation Menu" << endl;
				cout << "=======================================" << endl;
				cout << "Return to previous page (0)\nSet (1)\nAla Carte (2)\nShow Orders (3)\nDelete An Order (4)\nProceed To Checkout (5)\n";
				operationMenu:
				cout << "\nPlease enter your choice: ";

				if (!(cin >> setAlaCarteChoice) || setAlaCarteChoice < 0 || setAlaCarteChoice > 5 || cin.peek() != '\n') {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "\nInvalid choice. Please enter a valid option (0-5)." << endl;
				}
				else {
					break;  // Valid input, exit the loop
				}
			}

			if (setAlaCarteChoice == 1) {


				system("CLS");



				cout << "0. Return to previous page\n\n";
				cout << setw(10) << centered2("ID") << setw(50) << centered2("NAME") << setw(35) << centered2("PRICE (RM)") << endl;

				for (auto it = set_foods.begin(); it != set_foods.end(); ++it) {

					auto i = std::distance(set_foods.begin(), it);
					// declaring output string stream
					ostringstream str1;

					// Sending a number as a stream into output
					// string
					str1 << round((*it).getPrice() * 100) / 100;
					cout << setw(10) << centered2(to_string(int((*it).getId()))) << setw(50) << centered2((*it).getName()) << setw(35) << centered2(str1.str()) << endl;

				}

				int choice, quantity;
				bool validInput;
				
				do {
					cout << "Please Select Your Choice (number): ";
					string input;
					cin >> input;
					validInput = true;

					for (char c : input) {
						if (!isdigit(c)) {
							validInput = false;
							break;
						}
					}

					if (validInput) {
						choice = stoi(input);
						if (choice < 0 || choice > set_foods.size()) {
							validInput = false;
						}
					}
					
					if (!validInput) {
						cout << "Invalid choice. Please enter a valid number." << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				} while (!validInput);
				if (choice == 0) continue;


				do {
					cout << "Please Enter Your Quantity: ";
					string input;
					cin >> input;
					validInput = true;

					for (char c : input) {
						if (!isdigit(c)) {
							validInput = false;
							break;
						}
					}

					if (validInput) {
						quantity = stoi(input);
						if (quantity <= 0) {
							validInput = false;
						}
					}

					if (!validInput) {
						cout << "Invalid quantity. Please enter a valid positive number." << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				} while (!validInput);

				
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
				system("CLS");

				cout << "0. Return to previous page\n\n";
				cout << setw(10) << centered2("ID") << setw(50) << centered2("NAME") << setw(35) << centered2("PRICE (RM)") << endl;

				for (auto it = ala_carte_foods.begin(); it != ala_carte_foods.end(); ++it) {

					auto i = std::distance(ala_carte_foods.begin(), it);
					ostringstream str1;

					// Sending a number as a stream into output
					// string
					str1 << round((*it).getPrice() * 100) / 100;
					cout << setw(10) << centered2(to_string(int((*it).getId()))) << setw(50) << centered2((*it).getName()) << setw(35) << centered2(str1.str()) << endl;

				}

				int choice, quantity;
				bool validInput;

				do {
					cout << "Please Select Your Choice (number): ";
					string input;
					cin >> input;
					validInput = true;

					for (char c : input) {
						if (!isdigit(c)) {
							validInput = false;
							break;
						}
					}
					if(validInput){
						choice = stoi(input);
						if ((choice > 6 || choice < 4) && (choice <= set_foods.size() || choice > set_foods.size() + ala_carte_foods.size())) {
							validInput = false;
						}
						if (choice == 0) {
							validInput = true;
						}
					}
					if (!validInput) {
						cout << "Invalid choice. Please enter a valid number." << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				} while (!validInput);
				if (choice == 0) continue;
				do {
					cout << "Please Enter Your Quantity: ";
					string input;
					cin >> input;
					validInput = true;

					for (char c : input) {
						if (!isdigit(c)) {
							validInput = false;
							break;
						}
					}

					if (validInput) {
						quantity = stoi(input);
						if (quantity <= 0) {
							validInput = false;
						}
					}

					if (!validInput) {
						cout << "Invalid quantity. Please enter a valid positive number." << endl;
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
				} while (!validInput);

			
			
				for (int i = 0; i < quantity; i++) {
					orders.push_back(choice);
				}
				//orders.push_back(choice);
				//cout << "Enter Y to continue order, other to quit ordering\n";
			//	string isQuit;
			//	cin >> isQuit;
				//if (isQuit == "Y") {
				//	orderFlag = false;
				//}

			}
			else if (setAlaCarteChoice == 4) {
				system("CLS");

				while (true) {
					cout << "0. Return to previous page\n\n";
					displayOrders(foods, orders, orderChoice);
					int choiceToDelete, quantityToDelete;
					bool validInput;

					do {
						cout << "\nEnter the ID of the food to be deleted: ";
						string input;
						cin >> input;
						validInput = true;

						for (char c : input) {
							if (!isdigit(c)) {
								validInput = false;
								break;
							}
						}
						if (validInput) {
							choiceToDelete = stoi(input);
							if (choiceToDelete < 0 || (choiceToDelete != 0 && std::find(orders.begin(), orders.end(), choiceToDelete) == orders.end())) {
								validInput = false;
							}
						}
						if (!validInput) {
							cout << "Invalid choice. Please enter the number of the order to be deleted." << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					} while (!validInput);
					if (choiceToDelete == 0)  break;
					
					

					int count = std::count(orders.begin(), orders.end(), choiceToDelete);

					
					do {
						cout << "Enter the quantity of the order to be deleted: ";
						string input;
						cin >> input;
						validInput = true;

						for (char c : input) {
							if (!isdigit(c)) {
								validInput = false;
								break;
							}
						}

						if (validInput) {
							quantityToDelete = stoi(input);
							if (quantityToDelete < 0) {
								validInput = false;
							}
						}

						if (!validInput) {
							cout << "Invalid quantity. Please enter a valid positive number." << endl;
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
					} while (!validInput);

					for (int i = 0; i < quantityToDelete; i++) {
						// Get the iterator to the first occurrence of given value in vector
						auto it = std::find(orders.begin(), orders.end(), choiceToDelete);
						// Remove the element pointed by the iterator
						if (it != orders.end())
						{
							orders.erase(it);
						}

					}



					system("CLS");


					//orders.erase(orders.begin() + choiceToDelete - 1);
				}

				continue;

			}
			else if (setAlaCarteChoice == 3) {
				system("CLS");

				displayOrders(foods, orders, orderChoice);
				// cout << "Press ANY KEY to continue... ";
				cout << endl;
				// on windows
				system("pause");

				// on linux or mac
				system("read");

			}
			else if (setAlaCarteChoice == 5) {

				if (orders.size() <= 0) {
					cout << "Nothing to checkout!\n";
					goto operationMenu;
				}
				else {

					orderFlag = false;
					flag = false;
					system("CLS");

				}


			}
			else if (setAlaCarteChoice == 0) {
				string choice;
				cout << "Are you sure to cancel your order and return to previous page? (Y/other keys): ";
				cin >> choice;
				if (choice == "Y" || choice == "y") {
					orderFlag = false;
					isCheckout = false;
				}
				system("CLS");

			}
		}

	}

	if (isCheckout) {

		string yesOrNo;
		displayOrders(foods, orders, orderChoice);
		cout << "Proceed to checkout? (Y/N): ";
		cin >> yesOrNo;
		while (yesOrNo != "Y" && yesOrNo != "y" && yesOrNo != "N" && yesOrNo != "n") {
			cout << "Proceed to checkout? (Y/N): ";
			cin >> yesOrNo;

		}

		if (yesOrNo == "Y" || yesOrNo == "y") {
			system("CLS");

			cout << "Proceeding to checkout\n";

			payment(foods, orders, orderChoice);
		}
		else {
			goto order;
		}

		//	return orders;
	}



}
