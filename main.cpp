#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Food.h"
#include "Customer.h"
using namespace std;



int main() {

	bool flag = true;
	while (flag) {
		int menuChoice;
		cout << "WELCOME TO OUR RESTAURANT\n";
		cout << "1. Register Customer\n";
		cout << "2. Make an order\n";
		cout << "3. Redeem Gift Using Membership Point\n";
		cout << "4. Top Up Membership Card\n";

		cout << "0. Quit Program\n";
		cin >> menuChoice;
		while (!cin || menuChoice < 0 || menuChoice>3) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice\n";
			cin >> menuChoice;
		}
		switch (menuChoice) {
		case 1:

		{Customer customer = registerCustomer();

		//cout << "Hi " << customer.getName() << ", congratulations on becoming one of our members!";
		//writeMemberToFile(customer);
		}
		break;
		case 2:
			foodSelection();
			break;
		case 3:

			// membershipPoint();
			break;

		case 4:
			cardTopUp();
			break;
		case 0: 
			cout << "BYE";

			flag = false;
			break;
		}

	}
	
	return 0;
}
