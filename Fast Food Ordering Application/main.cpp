#include <iostream>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "Food.h"
#include "Customer.h"
#include <stdlib.h>
using namespace std;

void centerify_output(std::string str, int num_cols) {
    // Calculate left padding
    int padding_left = (num_cols / 2) - (str.size() / 2);

    // Put padding spaces
    for (int i = 0; i < padding_left; ++i) std::cout << ' ';

    // Print the message
    std::cout << str;
}


int main() {

	bool flag = true;
	while (flag) {
		int menuChoice;
                                                                                                    

        system("Color E4");

        std::vector<std::string> lines = {

                                                                                                      
         "                                   .                                  ",          
         "                                   :**=:                              ",          
         "                                    -###*+.                           ",          
         "                                    .**####+.                         ",          
         "                                    -**#####*:                        ",          
         "                                    **********.                       ",          
         "                                   =**********=                       ",          
         "                           -=     :***********=  :-.                  ",          
         "                         =**-    :************=  .**=.                ",          
         "                       -****.   :**++++++++***:   +***=               ",          
         "                      =*****:   ++++++++++++++    +****+              ",          
         "               +=    -******-  -+++++++++++++=   .+*****+     +:      ",          
         "              +#*:  .******++  =+++++++++++++=   -++*****-   -**:     ",          
         "             =##**- -*****+++=.=++++++++++++++  .++++****=  -****     ",          
         "             *#****=-****++++++-+++========+++-:++++++***+.+****#:    ",          
         "             *#*********++++++++++===========+++++++++***+******#:    ",          
         "             +**********+++++++++============+++++++++++********#.    ",          
         "          .  .**********++++++++==-:::-======++++++++++++*******+     ",          
         "          +=  :*********++++-::::=*###*==-::-==++++++++*********.  +: ",          
         "         .##*-.:+*******+=.-*%%%%%###**##%%#+===--:-=+********= .=*#= ",          
         "         .#####******+-:-+#%%%#***%%#%##**++++***###+=-=+*****+*####+ ",          
         "         .######***=:=##***%%%#%%%#*+==========-----=*#*=-+***######+ ",          
         "          #######*:=%%%*%#+%%#%#*++======+*+==---=+-----*%=:+#######= ",          
         "          +#####=.*%*%%%#*+%%%*++++===========---------::-##:-*#####: ",          
         "          :####-:%#*%%%%##%%%*++++*===========---------+-::+%=:####*  ",          
         "           +##=:%##%%%#%%+*%*++++++=======+*=---=+-----:::::+%=:###-  ",          
         "           :##.#%+%%%*+%*=%%++++++==========----------:::::::*%.=#*   ",          
         "            =--%**#%%**%+*%#++++++====++====----------+-::::::%*.*.   ",          
         "              +%#%#%%##%*%%*++++++===========++------::::-=-::*%..    ",          
         "              *%#%%%*#%%#%#++++++++=========-------==-:::=+-::+%.     ",          
         "              +%*%%%***%%%*+++++++======+++=------+**+-:::::::#%      ",          
         "              -%*#%%%#%%%#+++++==+=====+***-------=++=::::::-*%:      ",          
         "               #%*%%%%%%#++++++==========+=-------------==+*#*.       ",          
         "                =%##%##********++++++**********#######*++=-:          ",          
         "                  :-====================---:::...                     ",          
                                                                                          
                                                                                               
        };

                                                 
        int num_cols = 125;

        //// VIRTUAL BORDER
        //std::cout << std::endl;
        //for (int i = 0; i < num_cols; ++i) std::cout << ' ';
        //std::cout << '|' << std::endl;

        // OUTPUT
        cout << "\n\n\n";
        for (int i = 0; i < lines.size(); ++i) {
            centerify_output(lines[i], num_cols);
            std::cout << std::endl;
        }

        //// VIRTUAL BORDER
        //std::cout << std::endl;
        //for (int i = 0; i < num_cols; ++i) std::cout << ' ';
        //std::cout << '|' << std::endl;
		cout << "\n\n\nWELCOME TO MTACO!\n\n";
        cout << "Input Selection to continue... \n";
		cout << "1. Register Customer\n";
		cout << "2. Make an order\n";
		//cout << "3. Redeem Gift Using Membership Point\n";
		cout << "3. Top Up Membership Card\n";

		cout << "\n0. Quit Program\n";

        string input;

        while (true) {
            cout << "Please Select Your Choice (number): ";
            cin >> input;

            // Check if the entire input is a valid integer
            if (input.find_first_not_of("0123456789") == string::npos) {
                menuChoice = stoi(input);

                // Check if it's within the specified range
                if (menuChoice >= 0 && menuChoice < 4) {
                    break; // Valid input, exit the loop.
                }
            }

            cout << "Invalid choice. Please enter again:\n ";
        }
		system("CLS");


		switch (menuChoice) {
		case 1:

		cout << "REGISTER AS MEMBER\n\n";
		{Customer customer = registerCustomer();
		system("CLS");
		cout << "Hi " << customer.getName() << ", congratulations on becoming one of our members!\n";
        cout << "Your Card No. is " << customer.getCardNo() << ", please take note of it for future use!\n\n";

	writeMemberToFile(customer);
		}
		break;
		case 2:

			foodSelection();
			break;
		case 3:
			cout << "TOP UP CARD\n\n";

			cardTopUp();
			break;
			
		case 0: 
            system("CLS");
            cout << "\n\n\n";
            for (int i = 0; i < lines.size(); ++i) {
                centerify_output(lines[i], num_cols);
                std::cout << std::endl;
            }
            cout << "\n\n\n";

			cout << "Bye! See you again!\n";

			flag = false;
			break;
		}

	}
	
	return 0;
}
