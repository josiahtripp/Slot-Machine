#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
int coinAmount = 0;
double money = 5;
string tw;

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

bool coinChecker(double &money, int &coinAmount) {

	bool hasBoughtCoins = false;

	if (coinAmount == 0 && money == 0) {

		cout << "You're broke!" << endl << "Goodbye!" << endl;
		cin.ignore();
		getline(cin, tw);
		exit(0);
	}
	else if (coinAmount == 0) {

		while (hasBoughtCoins == false) {

			cout << "Insert Coins: ($1 = 4 coins)" << endl
				<< "Max amount of coins you can currently buy: " << fixed 
				<< setprecision(0) << money * 4 << endl 
				<< "Enter the amount of coins you'd like to purchase" << endl;
			cin >> coinAmount;

			if (coinAmount == 0) {

				while (tw != "n" && tw != "N") {
					cout << "You'd like to walk away? (y/n)" << endl;
					cin >> tw;

					if (tw == "y" || tw == "Y") exit(0);
				}
			}
			else if (coinAmount / 4.0 <= money) {

				money = money - coinAmount / 4.0;
				cout << "Purchased " << coinAmount << " coins!";

				hasBoughtCoins = true;
			}
			else cout << "Not enough Funds!" << endl;

			cout << endl;
			cin.ignore();
		}
	}

	return hasBoughtCoins;
}

void printMachine(char screen[][3], double money, int coinAmount) {


	cout << R"(                             __________________________
    Slot Machine!            | 7 7 7 = Jackpot! ($100)|
=====================        | 8 8 8 = $30            |
|                   |        | O O O = $10            |
|___________________|        | @ @ @ = $5             |
||     |     |     ||        |       = $1             |
||     |     |     ||        --------------------------
)";

	for (int i = 0; i < 3; i++) {
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

$: )" << fixed << setprecision(2) << money 
<< "        Coins: " << coinAmount << endl << endl;
}

void checkWinnings(char arr[][3], double &money) {

	bool win = false;
	char winType[3] = { '-','-','-' };
	string winDisp = "";
	int earnings = 0, winNum = 0;

	for (int i = 0; i < 3; i++) //Horizontal Win
		if (arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2]) winType[i] = arr[i][0];
			
		if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] //Diagonal Win
			|| arr[2][0] == arr[1][1] && arr[1][1] == arr[0][2]) winType[0] = arr[1][1];

		for (int i = 0; i < 3; i++) {
			switch (winType[i]) {
			case '7':
				earnings = earnings + 100;
				winDisp += '7';
				winNum++;
				break;
			case '8':
				earnings = earnings + 30;
				winDisp += '8';
				winNum++;
				break;
			case 'O':
				earnings = earnings + 10;
				winDisp += 'O';
				winNum++;
				break;
			case '@':
				earnings = earnings + 5;
				winDisp += '@';
				winNum++;
				break;
			case ' ':
				earnings = earnings + 1;
				winDisp += ' ';
				winNum++;
				break;
			case '-':
				break;
			}
		}

		switch (winNum) {

		case 0:
			cout << "Nothing this time." << endl;
			break;

		case 1: 
			cout << winDisp << " " << winDisp << " " << winDisp
				<< endl << "Win!" << endl;
			money = money + earnings;
			break;
		case 2:
			cout << winDisp << " " << winDisp << " " << winDisp
				<< endl << "Double Win! (Earnings x 2)" << endl;
			money = money + (earnings * 2);
			break;
		case 3:
			cout << winDisp << " " << winDisp << " " << winDisp
				<< endl << "Triple Win! (Earnings x 5)" << endl;
			money = money + (earnings * 5);
			break;
		}
}



int main() {

	srand(static_cast<unsigned>(time(nullptr)));

	for (int i = 0; i < 1;) {
		if (coinChecker(money, coinAmount)) printMachine(display, money, coinAmount);
		getline(cin, tw);
		spinWheels(display, coinAmount);

		checkWinnings(display, money);
		printMachine(display, money, coinAmount);
	}

}