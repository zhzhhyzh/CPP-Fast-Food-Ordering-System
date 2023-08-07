#include "Food.h"

#include <iomanip>
#define COLUMN_WIDTH 25


vector<int> foodSelection() {

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
	while (flag) {
		int orderChoice, setAlaCarteChoice;
		cout << "Take away (0) Dine In (1)\n";
		cin >> orderChoice;
		while (!cin || orderChoice < 0 || orderChoice>1) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice\n";
			cin >> orderChoice;
		}

		bool orderFlag = true;
		while (orderFlag) {
			switch (orderChoice) {
			case 0:
				cout << "TAKE AWAY:\n";
				break;
			case 1:
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

	cout << "Proceeding to checkout";
	vector<Food>foods;
	foods.reserve(set_foods.size() + ala_carte_foods.size()); // preallocate memory
	foods.insert(foods.end(), set_foods.begin(), set_foods.end());
	foods.insert(foods.end(), ala_carte_foods.begin(), ala_carte_foods.end());
	payment(foods,orders);
	return orders;
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

	
	bool flagToProceed = false;
	double currentValue = 0;
	string deleteLine;

	while (!flagToProceed) {
		ifstream fileInput;
		fileInput.open("member.txt");
		string line;
		unsigned int curLine = 0;
		while (getline(fileInput, line)) { 
			if (line.find(cardNo, 0) != string::npos) {
				deleteLine = line;
				cout << "FOUND";
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
	currentValue = getCurrentTopUpValueFromFile(cardNo);

	if (currentValue<total) {
		// todo
		cout << "NOT ENOUGH";
	}
	else {
		string line;

		ifstream fin;
		fin.open("member.txt");
		// todo
		// cout << deleteLine;
		while (getline(fin, line)) {
//			line.replace(line.find(deleteLine), deleteLine.length(), "");


		}
		fin.close();
		ofstream MemberFile("member.txt", std::ios_base::app | std::ios_base::out);
		string name, cardNo, contactNo;
		int point;
		double value = currentValue - total ;
		int start, end;
		start = end = 0;
		char dl = ' ';
		vector<string> v;

		while ((start = deleteLine.find_first_not_of(dl, end))
			!= string::npos) {
			// str.find(dl, start) will return the index of dl
			// from start index
			end = deleteLine.find(dl, start);
			// substr function return the substring of the
			// original string from the given starting index
			// to the given end index
			v.push_back(deleteLine.substr(start, end - start));
			string name;
			for (auto it = v.begin(); it != v.end(); ++it) {

				//auto i = std::distance(v.begin(), it);
				name += (*it);
			}
		}
		MemberFile << setw(50) << (name )<< setw(COLUMN_WIDTH) << (v.at(-3)) << setw(COLUMN_WIDTH) << (v.at(-2)) << setw(COLUMN_WIDTH) << (v.at(-1)) << setw(COLUMN_WIDTH) << (to_string(value)) << endl;

		cout << "ENOUGH";
	}

}