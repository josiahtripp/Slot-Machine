#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string tw, slotMessage = "noWin"; // Lines 9-20 can be changed to adjust different values
                         //Amount to reward for each type 
const int jackpot = 100;// '7'
const int award8 = 5;// '8'
const int awardO = 3; // 'O'
const int awardA = 2; // '@'
const int awardBlank = 1; // ' '
                              //Coin cost (line 15) & starting values (lines 16 & 17)
const int coinsPerDollar = 4; //# of coins per dollar
const int coinStart = 0; //# of starting coins
const double moneyStart = 5.00; //Amount of starting money
						  //Reward multipliers
const int doubleWin = 2; //Double win
const int tripleWin = 5; //Triple win

//Created on 11/16/2023 by Josiah Tripp

char display[3][3] = {

	{' ',' ',' '},
	{' ',' ',' '},
	{' ',' ',' '}
};

void spinWheels(char display[3][3], int &coinAmount) {

	int wheelRand, dispColumn = 0;
	coinAmount--;

	char wheels[22] = { '7','@','8',' ','O','8',' ','@','8',' ','O','8','@',' ','O','@',' ','O','8',' ','7','@'};

	for (int j = 0; j < 3; j++) {

		dispColumn = 0;
		wheelRand = rand() % 20;
		for (int i = wheelRand; i < wheelRand + 3; i++) {

			display[dispColumn][j] = wheels[i];
			dispColumn++;
		}
	}
}

bool coinChecker(double &money, int &coinAmount, string &message) {

	bool hasBoughtCoins = false;

	if (coinAmount == 0 && money == 0) {//User has nothing left

		cout << "You're broke!" << endl << "Goodbye!" << endl;
		cin.ignore();
		getline(cin, tw);
		exit(0);
	}
	else if (coinAmount == 0) {//User has money, but no coins

		while (hasBoughtCoins == false) {

			cout << "Insert Coins: ($1 = " << coinsPerDollar << " coins)" << endl
				<< "Max amount of coins you can currently buy: " << fixed 
				<< setprecision(0) << money * coinsPerDollar << endl 
				<< "Enter the amount of coins you'd like to purchase" << endl;
			cin >> coinAmount;

			if (coinAmount == 0) {//User wants to buy no coins (Exits if y, loops if n)

				while (tw != "n" && tw != "N") {
					cout << "You'd like to walk away? (y/n)" << endl;
					cin >> tw;

					if (tw == "y" || tw == "Y") exit(0);
				}
			}
			else if (coinAmount / 4.0 <= money) {

				money = money - coinAmount / 4.0;
				message = "Purchased " + to_string(coinAmount) + " coins!";
				hasBoughtCoins = true;
			}
			else cout << "Not enough Funds! Please enter an amount you can afford!" << endl;

			cout << endl;
		}
	}
	return hasBoughtCoins;
}

void printMachine(char screen[][3], double money, int coinAmount, string &winMessage){

	cout << fixed << setprecision(0)//Prints scoreBoard
		<< endl << "__________________________" << endl
		<< "|7|7|7| = Jackpot! ($" << left << setw(3) << jackpot << ")|" << endl
		<< fixed << setprecision(2)
		<< "|8|8|8| = $" << left << setw(14) << award8 << "|" << endl
		<< "|O|O|O| = $" << left << setw(14) << awardO << "|" << endl
		<< "|@|@|@| = $" << left << setw(14) << awardA << "|" << endl
		<< "| | | | = $" << left << setw(14) << awardBlank << "|" << endl
		<< "--------------------------" << endl << endl;

	//Prints machine with wheel characters
 cout << R"(   Slot Machine!
=====================        
|                   |        
|___________________|
||     |     |     ||
||     |     |     ||
)";

	for (int i = 0; i < 3; i++) {//Prints wheel characters and wheel dividers
		cout << "||  ";
		for (int j = 0; j < 2; j++) cout << screen[i][j] << "  |  ";
		cout << screen[i][2] << "  ||" << endl;
	}
	cout << R"(||     |     |     ||
||-----|-----|-----||
|                   |
|                   |
[][][][][]X[][][][][]
 Hit Enter to roll!

)";
	if (winMessage != "noWin") cout << winMessage << endl << endl;//Prints the message unless the message is "noWin"

	cout << "$: " << fixed << setprecision(2) << money//Prints current stats (Money and Coins)
		<< "        Coins: " << coinAmount << endl << endl;
}

void checkWinnings(char arr[][3], double& money, string& message) {

	char winType[3];
	int winNum = 0, earnings = 0;
	bool jp = false;
	message = "";

	for (int i = 0; i < 3; i++) //Horizontal Win
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) winType[winNum] = arr[i][0], winNum++;

	if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] //Diagonal Win
		|| arr[2][0] == arr[1][1] && arr[1][1] == arr[0][2]) winType[winNum] = arr[1][1], winNum++;

	for (int i = 0; i < winNum; i++) {//Adds winning character(s) to string

		message += "|";
		message += winType[i];
		message += "|";

		switch (winType[i]) {//adds initial earnings

		case '7':
			earnings += jackpot;
			jp = true;
			break;

		case '8':
			earnings += award8;
			break;

		case 'O':
			earnings += awardO;
			break;

		case '@':
			earnings += awardA;
			break;

		case ' ':
			earnings += awardBlank;
			break;
		}
	}
	message += " x3: "; //Used for message display, removed if wins = 0
	if (jp) message += "Jackpot! ";//Adds if applicable

	switch (winNum) {//Actions based on Number of Wins

	case 0:
		message = "noWin";
		break;

	case 1:
		message += "Single Win";
		break;

	case 2:
		message += "Double Win: Earnings x " + to_string(doubleWin);
		earnings = earnings * doubleWin;
		break;

	case 3:
		message += "Triple Win: Earnings x " + to_string(tripleWin);
		earnings = earnings * tripleWin;
		break;
	}

	if (winNum > 0) {
		message += "! | + $" + to_string(earnings) + "!";//Completes msg string and sets slotMessage to it
		money += earnings;
	}
	else message = "noWin";
}

int main() {

	srand(static_cast<unsigned>(time(nullptr)));//Sets random number seed
	int coinAmount = coinStart;
	double money = moneyStart;

	for (int i = 0; i < 1;) {//Indefinite Loop

		if (coinChecker(money, coinAmount, slotMessage)) cin.ignore();//Returns true if the user purchases coins
		printMachine(display, money, coinAmount, slotMessage);
		getline(cin, tw);
		system("cls");
		spinWheels(display, coinAmount);
		checkWinnings(display, money, slotMessage);//Resets message to noWin if no win is present
	}
}