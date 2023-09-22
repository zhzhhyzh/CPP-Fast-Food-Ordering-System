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
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
  /*  cout<<"                          !JJY?~.                           .^                                  " << endl;
    cout<<"                          P!:?JPP7         :~7?YJ^        .^~7!~.                               "<<endl;
    cout<<"                          75.!!!JB5^    :7?7!!!5#5         :!!J~         ^.                     "<<endl;
    cout<<"                          ~G:~7!!7PG7:!YY!^~!!?GB?         .:..:..   ...:7!....                 "<<endl;
    cout<<"               :~~~^^:...:YJ.!!!!!!JYYY7~~!!!JBBG?7!~^.         ...::^~!!7???~.                 "<<endl;
    cout<<"              ?G?JJJYYYYJJ7:~!!!!!7?JYJYYYJJ557^:^~7YGGPY?!:.        ..!77?57                   "<<endl;
    cout<<"              ^JJJ?!!!!!!!~!?JYYYYY?~:..:~!!^.~7??JJ~:?5PPGGPJ!:      .^:. :~.                  "<<endl;
    cout<<"                .~YGYJYYJJJYJ~. .:~7???7!~~!?J?7??YBB~:YYYYY5PGG57:                             "<<endl;
    cout<<"               ^???J?7^^~!~^..:!?J???????7??7?5PPPGBB^^YYYJYYJJJ5GGY~                           "<<endl;
    cout<<"              !G~   .~?J???????77J5Y55G#BBGGBBBGGPPPGYYYY?^?YYYYYJY5G5!                         "<<endl;
    cout<<"              ?P.~?JJ??JJYY5555PBBBGPP5YJ?7!~^^:....^PBPYYYYYYJYYYYJJ5GP~                       "<<endl;
    cout<<"               5PYJJYPBBGP55YJ?7~^^:...              !BB5JYYY7.~JYYYYJJPB5^                     "<<endl;
    cout<<"              !GGPP5?~^:..    ..:^~~~!!!!!!!!!~~^^.  J#B5YYYYJ??YYYJJJ?7?J7.                    "<<endl;
    cout<<"             ?BPYY!       .^~!!7777777????7777!~~^: ^55Y77!!!~~~^^^^::..::^~~!7?JYYYJJ7^        "<<endl;
    cout<<"            ?BPYYYJ.  .:~!77777777!!~~^^::.........::::^^~!!7??JJY55PPPYJJYGBBBB5!~^:^7PP~      "<<endl;
    cout<<"           7#GYYYYGY: .:::::........:::^^~~!77?JYY555PGGBGY?77?PBBBBB?::~^ .YBGB7 :5Y^ .PB?     "<<endl;
    cout<<"           ^~^... .::::^^^~!77??JY555555PBBBBB#Y!~^^:5BB5:.!?^ .PBBB! ~B#B^ ~BBB! ~##G. !#B~    "<<endl;
    cout<<"         ::^^~~!7?JY5PPGGBGJ7!?BB7^^::::PBGGBBG: 7Y55BBP. 5##P. YBB5  P#GB! ^BBB~ !#BB^ ^BBJ    "<<endl;
    cout<<"       ~YYJJ??GB#G~~GBBBBJ.^7??BGJY: ?GGBGGBBB5 .B#BBBB! !#BBP. Y#B? ^BBGB! ^BBB^ 7#BB^ ^BBY    "<<endl;
    cout<<"      ~B~ ^~~?BBB~ :BBBBJ !B##BBB#P..GBGGBBBBB? !#BBBBG. Y#BB5  PBB~ !#BBB~ ~#BG: ?#BB^ ~#BY    "<<endl;
    cout<<"     .PJ ~####BB7..^BBBB: J#BBBBBB7 !BBBBBBBBB^ ^!~7BBY .GBBB? .GBG: ?#BBB^ 7#BG. J#BG. 7#B7    "<<endl;
    cout<<"     ?G: P#BBBB? J.!#BBB~ .5BBBBBG: Y#BBBBBBBP. !775#B7 ^BBBB! ~#BP. J#BBP. J#BP. Y#BJ  5#G.    "<<endl;
    cout<<"    :B? ^5JYBBY ?P 7#BBBG^ .PBBBBY :BBGJJ??GBJ ^###BBB~ !#BBG: J#BP. J#B#J .GBB5  5B5. ~B#7     "<<endl;
    cout<<"    YG. ...J#5.~#J J#BBBBP: ~BBBB~ 7#BY~!!?BB~ 7#BBBBB^ !#BB? :GBBG: ^PPJ. J#BBY  ^: :?B#J      "<<endl;
    cout<<"   ~B! ~BBB#P. 5G~ J#BBBB#J ^BBBP. P#BBB###BG. 5#BBBBB! .?J! :5#BBBY^....~5#BBB57JJYPB#B7       "<<endl;
    cout<<"   55  P#BBG^  ..  5#BBBBG~ J#BB? ^BBBBBBBBB? .BBBBBBBG7^:^~JG#BBBBBBGPGB##BBBBBB##BBBYJ7       "<<endl;
    cout<<"  ~B^ !#BBB~ !5PY  P#J!?7: ?#BBB^ J#BBBBBBBBJ7YBBBBBBGBBBBB##BBBBBBBBBBBBBBBBBBBBBBB#P          "<<endl;
    cout<<"  YJ .GBBB! ~B##Y .GB!::^7P#BBBG5PBBBBBBBBBBBBBBBBGGBBBBBBBBBBBBBBBBBBBBBBGGPP55YJJ?7^          "<<endl;
    cout<<" .P!^J#BBG?JB#BBGPGBGBBBB#BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBGGGPP5YYJ?77!~~^::...     ...:^^.       "<<endl;
    cout<<"  ~J5P55YYYYJ7!JBBBBBBBBBBBBBBBBBBBBBBBGGPPP5YJJ?77!~^^::...  .....::^^~~!!77777?JJJYY7:        "<<endl;
    cout<<"                ~PBBBGGGPP55YJJ?7!~~^^::........::^^^~!!!77??JJ?JYYYY!?Y77YY7!:!?YYJ7:          "<<endl;
    cout<<"                 .^^:::......:::^^~~~!!777?JJJJ?YY7JYY7~7~?YYY7:^?YYY^!!~^YYYJ.?YYY~            "<<endl;
    cout<<"       ....:^^^~~~~!!!7??JJ777JYJ7!~!?YY?:~JYY?.JY^~YY!.!.7YYY:~~:?YY!7?~^YYYY!7YYYJ7^.         "<<endl;
    cout<<"    .~?JJJJY777?YYY7^!!JYY^^!!?YJJ?.JYYY^^^:JYY^!J~~YY?:?7~?YJ!JY?7JJJJJJJYYYYYJJJJ???!.        "<<endl;
    cout<<"      .~JYYY^~!.JYY7.!!?YY?!!~^YYYJ:?JY?^?J7!YYJ777JJJJJJYJJJJYJJJJJJJY5Y7~~^^::...             "<<endl;
    cout<<"         !YY!:7^!JYJ:!!7JY?!!!?JJJJ?JJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ5GGY^                       "<<endl;
    cout<<"       :7JYYJ?YY?JYYJJJJJJYYYYJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJ??JJ5GGP?:                         "<<endl;
    cout<<"     :7JJ???777!!~~^^^::..^7YPPP5YJJJJJJJJJJJJJJJ?????????JJY5PGG5?^                            "<<endl;
    cout<<"     ::...                   .^7J5PPP55YYJJJJJJJJJJJYY55PPGGPY?~:                               "<<endl;
    cout<<"                                  .:~!7JJY555555555YYJ?7!~^.                                    "<<endl;
    cout<<"                                             ...                                                "<<endl;
    cout<<"                                                                                                "<<endl;
                                                                                                    
                                                                                                    */

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
                                                                                          
                                                                                          


//
//        "        :~7?JJJJJJJJJJJJ?!:.        ",
//        "    .7PGPYJ?77777777777??YPGGJ:     ",
//        "  .5#Y~^^^^^^^^^^^^^^^^^^^^^!Y#G.   ",
//        " :&P^:^^^^^^^^^^^^^^^^^^^^^^^^^5&!  ",
//        ".&Y.:^^^^^^^^^^^^^^^^^^^^^^^^^^:?@^ ",
//        "?@???JJJJJJJJJJJJJJJJJJJJJJJJJJJ?&G ",
//        "J@BB##################&&&#&######@B ",
//        "J@                              G&B ",
//        "J@##&&&&&&&&&&&&&&&&&&#GGB&&&&&&&@B ",
//        "J&                              G#B ",
//        "J@55GGGGGGGGGGGGGGGGGGGB#GGGGGGGG&B ",
//        "J@                               &# ",
//        "J@:.^^^^^^^^^^^^^^^^^^^^^^^^^^^^:#B ",
//        ".BB7!!!!!!!!!!!!!!!!!!!!!!!!!!!?G&^ ",
//        "  ^JY55555555555555555555555555Y!   " ,      
        };

                                                  
        //cout<<"        :~7?JJJJJJJJJJJJ?!:.        "<<endl;      
        //cout<<"    .7PGPYJ?77777777777??YPGGJ:     "<<endl;      
        //cout<<"  .5#Y~^^^^^^^^^^^^^^^^^^^^^!Y#G.   "<<endl;      
        //cout<<" :&P^:^^^^^^^^^^^^^^^^^^^^^^^^^5&!  "<<endl;      
        //cout<<".&Y.:^^^^^^^^^^^^^^^^^^^^^^^^^^:?@^ "<<endl;      
        //cout<<"?@???JJJJJJJJJJJJJJJJJJJJJJJJJJJ?&G "<<endl;      
        //cout<<"J@BB##################&&&#&######@B "<<endl;      
        //cout<<"J@                              G&B "<<endl;      
        //cout<<"J@##&&&&&&&&&&&&&&&&&&#GGB&&&&&&&@B "<<endl;      
        //cout<<"J&                              G#B "<<endl;      
        //cout<<"J@55GGGGGGGGGGGGGGGGGGGB#GGGGGGGG&B "<<endl;      
        //cout<<"J@                               &# "<<endl;      
        //cout<<"J@:.^^^^^^^^^^^^^^^^^^^^^^^^^^^^:#B "<<endl;      
        //cout<<".BB7!!!!!!!!!!!!!!!!!!!!!!!!!!!?G&^ "<<endl;      
        //cout<<"  ^JY55555555555555555555555555Y! " << endl;
        int num_cols = 100;

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
		cout << "1. Register Customer\n";
		cout << "2. Make an order\n";
		//cout << "3. Redeem Gift Using Membership Point\n";
		cout << "3. Top Up Membership Card\n";

		cout << "\n0. Quit Program\n";
		cout << "\nPlease enter: ";

		cin >> menuChoice;
		while (!cin || menuChoice < 0 || menuChoice>4) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid choice. Please enter again: ";
			cin >> menuChoice;
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
