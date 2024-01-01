#include<iostream>
#include<ctime>
#include<cstdlib>
#include<Windows.h>
#include<iomanip>
#include<string>
#include<regex>
#include<fstream>
using namespace std;

//GLOBAL DECLARATION
const int SIZE_ARRAY = 5;

//FUNCTIONS DECLARTAION
void bingo();
void title();
void mainMenu();
void howToPlay();
void gameHistory();
void credits();
void playGame(bool newGame);
void saveForResuming(int uniqueID, string player1Name, int scoreP1, string player2Name, int scoreP2, string playerTurn, int player1Board[][SIZE_ARRAY], int player2Board[][SIZE_ARRAY]);
void resumeGame(int &uniqueID, string &player1Name, int &scoreP1, string &player2Name, int &scoreP2, string &playerTurn, int player1Board[][SIZE_ARRAY], int player2Board[][SIZE_ARRAY]);
bool checkCharacters(string name); //the function return false when string contain anything except A-Z a-z or space
void toss(string&, string, string);
void populateTable(int[][SIZE_ARRAY], int[][SIZE_ARRAY]);
bool checkDuplicateNumber(const int[][SIZE_ARRAY], int);
void drawBoard(int[][SIZE_ARRAY], int, string);
void replaceNumber(int[][SIZE_ARRAY], int[][SIZE_ARRAY], int num);
void updateScore(const int[][SIZE_ARRAY], int&);
void resetColor()
{
	printf("\033[1;37m");
}
void grayColor()
{
	printf("\033[1;30m");
}
void greenColor()
{
	printf("\033[1;32m");
}
void redColor()
{
	printf("\033[1;31m");
}

int main()
{
	printf("\033[;37m");
	bingo();
	mainMenu();

	return 0;
}

void bingo()
{
	system("cls");
	cout << "\t\t\t\t0000000   00000000  000       00  00000000  00000000" << endl;
	cout << "\t\t\t\t00    00     00     00 00     00  00        00    00" << endl;
	cout << "\t\t\t\t00    00     00     00 00     00  00        00    00" << endl;
	cout << "\t\t\t\t00000000     00     00   00   00  00   000  00    00" << endl;
	cout << "\t\t\t\t00    00     00     00     00 00  00    00  00    00" << endl;
	cout << "\t\t\t\t00    00     00     00     00 00  00    00  00    00" << endl;
	cout << "\t\t\t\t0000000   00000000  00       000  00000000  00000000" << endl << endl;

	Sleep(2000);
}

void title()
{
	int delay = 80;
	cout << "\t\t\t-"; Sleep(delay); cout << "-"; cout << "-"; Sleep(delay); cout << "-"; Sleep(delay); cout << "|"; Sleep(delay); cout << "B"; Sleep(delay);
	cout << "I"; Sleep(delay); cout << "N"; Sleep(delay); cout << "G"; Sleep(delay); cout << "O"; Sleep(delay); cout << "|"; Sleep(delay); cout << "-"; Sleep(delay);
	cout << "-"; Sleep(delay); cout << "-"; Sleep(delay); cout << "-";
}

void mainMenu()
{
	int menu;

	system("cls");
	title();
	cout << "\n\n*************MAIN MENU*************";
	cout << "\n1. Play Game\n2. How To Play\n3. Resume Last Game\n4. History\n5. Credits\n6. Exit\nSelect an Option= ";
	cin >> menu;
	while (menu < 1 || menu > 5)
	{
		cout << "Invalid Choice! Enter Again= ";
		cin >> menu;
	}
	switch (menu)
	{
	case 1:
		playGame(true);
		break;
	case 2:
		howToPlay();
		break;
	case 3:
		playGame(false);
		break;
	case 4:
		gameHistory();
		break;
	case 5:
		credits();
		break;
	case 6:
		cout << "\nThank you for Playing.";
		return;
	}
}

void howToPlay()
{
	int delay = 80;
	system("cls");
	cout << "\t\t\t----|BINGO|----";
	cout << "\n\n*************H"; Sleep(delay); cout << "O"; Sleep(delay); cout << "W"; Sleep(delay); cout << " "; Sleep(delay); cout << "T"; Sleep(delay);
	cout << "O"; Sleep(delay); cout << " "; Sleep(delay); cout << "P"; Sleep(delay); cout << "L"; Sleep(delay); cout << "A"; Sleep(delay); cout << "Y"; Sleep(delay); cout << "*************";

	string instructions = "This game is a multiplayer game. Both Players will have a table filled with numbersfrom 1 - 25. Both players won't be able to see eachother's table. Each Player will choose a number in his turn from his own Table. The choosen number is replaced withZERO in the table of both players.Both players can't enter ZERO or any other numberthat is not present in the Table.When a player has placed 5 ZEROS in a row, either horizontally, vertically or diagonally.His score increases by 1. The Target of eachplayer is to Mark ZEROS in his table and be the firat to score 5.The player whoose five combination of ROWS, COLUMNS or DIAGONAL becomes ZEROS first.That Player WINS.\n";
	cout << endl << endl;
	//To justify TEXT
	for (int i = 0, c = 0; i < instructions.length(); ++i)
	{
		cout << instructions[i];
		c++;

		//printing 83 character in one line
		if (c == 83)
		{
			cout << endl;
			c = 0;
		}
	}

	cout << "Return to Menu? ";
	system("pause");
	mainMenu();

}

void gameHistory()
{
	int delay = 80;
	int uniqueID, scoreP1, scoreP2;
	string player1Name, player2Name, winner;
	ifstream readFromFile;

	system("cls");
	cout << "\t\t\t----|BINGO|----";
	cout << "\n\n*************H"; Sleep(delay); cout << "I"; Sleep(delay); cout << "S"; Sleep(delay); cout << "T"; Sleep(delay); cout << "O"; Sleep(delay);
	cout << "R"; Sleep(delay); cout << "Y"; Sleep(delay); cout << "*************\n\n";
	redColor();
	cout << left << setw(15) << "Unique ID" << setw(26) << "Player 1 Name" << setw(14) << "P1 Score" << setw(26) << "Player 2 Name" << setw(14) << "P2 Score" << setw(26) << "Winner Name" << endl << endl;
	resetColor();

	//Printing/Outputing File on Console Screen
	readFromFile.open("BINGO HISTORY.txt");
	if (readFromFile.is_open())
	{
		while (readFromFile >> uniqueID >> player1Name >> scoreP1 >> player2Name >> scoreP2 >> winner)
		{
			cout << setw(15) << uniqueID << setw(26) << player1Name << setw(14) << scoreP1 << setw(26) << player2Name << setw(14) << scoreP2;
			
			greenColor();
			cout << setw(26) << winner << endl;
			resetColor();
		}
		readFromFile.close();
	}
	else
		cout << "File can't be open";

	cout << "Return to Menu? ";
	system("pause");
	mainMenu();
}

void credits()
{
	int delay = 80;
	system("cls");
	cout << "\t\t\t----|BINGO|----";
	cout << "\n\n*************R"; Sleep(delay); cout << "U"; Sleep(delay); cout << "N"; Sleep(delay); cout << "T"; Sleep(delay); cout << "I"; Sleep(delay);
	cout << "M"; Sleep(delay); cout << "E"; Sleep(delay); cout << " "; Sleep(delay); cout << "T"; Sleep(delay); cout << "E"; Sleep(delay); cout << "R"; Sleep(delay);
	cout << "R"; Sleep(delay); cout << "O"; Sleep(delay); cout << "R"; Sleep(delay); cout << "S*************";
	cout << "\nMUHAMMAD TAHA - 22F 3277";

	cout << "Return to Menu? ";
	system("pause");
	mainMenu();

}

void playGame(bool newGame)
{
	int player1Board[SIZE_ARRAY][SIZE_ARRAY];
	int player2Board[SIZE_ARRAY][SIZE_ARRAY];
	int num, choose, uniqueID;
	//score resets to zero for every new game
	int scoreP1 = 0, scoreP2 = 0;
	string playerTurn, player1Name, player2Name;
	ofstream writeInFile;
	ifstream readFromFile;

	//if to play newGame than take input 
	if (newGame == true)
	{
		cout << "\n*Maximum 20 letters inclding Space*\nEnter Player 1 Name= ";
		cin.ignore();
		getline(cin, player1Name);
		while (checkCharacters(player1Name) == false || player1Name.length() > 20)
		{
			cout << "Enter Again= ";
			getline(cin, player1Name);
		}

		cout << "Enter Player 2 Name= ";
		getline(cin, player2Name);
		while (checkCharacters(player2Name) == false || player2Name.length() > 20 || player1Name == player2Name)
		{
			cout << "Enter Again= ";
			getline(cin, player2Name);
		}

		toss(playerTurn, player1Name, player2Name);
		cout << playerTurn << " won the Toss and will play first!\n";
		system("pause");

		writeInFile.open("BINGO HISTORY.txt", ios::app);
		srand(time(0));

		int id;
		bool flag = false;
		do
		{
			uniqueID = rand() % 9000 + 1000; //generates a four digit number
			while (!readFromFile.eof())
			{
				readFromFile >> id;

				if (id == uniqueID)	//checking is the unique id already exists in file
				{
					flag = true;
					break;
				}
				flag = false;
			}
		} while (flag == true);		//TO check if unique id id repeated again
		writeInFile.close();

		populateTable(player1Board, player2Board);
		cout << "3 "; Sleep(350); cout << " 2 "; Sleep(350); cout << " 1..."; Sleep(350);
	}

	bool resumeGameAlreadyFinished = false;
	//if want to RESUME GAME
	if (newGame == false)
	{
		resumeGame(uniqueID, player1Name, scoreP1, player2Name, scoreP2, playerTurn, player1Board, player2Board);
		
		if (scoreP1 >= 5 || scoreP2 >= 5)
			resumeGameAlreadyFinished = true;
	}


	while (scoreP1 < 5 && scoreP2 < 5)
	{
		playerTurn == player1Name ? drawBoard(player1Board, scoreP1, playerTurn) : drawBoard(player2Board, scoreP2, playerTurn);

		cout << "\nUnique ID= " << uniqueID;
		cout << "\n" << player1Name << " Score = " << scoreP1;
		cout << "\n" << player2Name << " Score = " << scoreP2 << endl;
		cout << "Enter a number = ";
		cin >> num;
		while (checkDuplicateNumber(player1Board, num) == false || num == 0)		//both table will have same values so we can check only in one
		{
			num == 0 ? cout << "You can't Enter 0, Enter Again= " : cout << "The number don't exist in Table, Enter Again= ";
			cin >> num;
		}
		replaceNumber(player1Board, player2Board, num);

		updateScore(player1Board, scoreP1);
		updateScore(player2Board, scoreP2);

		//changing player
		playerTurn == player1Name ? playerTurn = player2Name : playerTurn = player1Name;

		//WRITING IN FILE for Resuming Game 
		saveForResuming(uniqueID, player1Name, scoreP1, player2Name, scoreP2, playerTurn, player1Board, player2Board);
		
	}

	//printing Table of WINNER
	scoreP1 == 5 ? playerTurn = player1Name : playerTurn = player2Name;
	playerTurn == player1Name ? drawBoard(player1Board, scoreP1, playerTurn) : drawBoard(player2Board, scoreP2, playerTurn);
	greenColor();
	cout << playerTurn << " WINS!!!...\n";
	resetColor();

	//this check is only to see if the resumed game is already finished or not, if it is than don't write it again in BINGO HISTORY file
	if (!resumeGameAlreadyFinished)
	{
		//WRITING IN FILE for History 
		writeInFile.open("BINGO HISTORY.txt", ios::app);
		if (writeInFile.is_open())
		{
			cout << endl;
			writeInFile << uniqueID << "\t" << player1Name << "\t" << scoreP1 << "\t" << player2Name << "\t" << scoreP2 << "\t" << playerTurn << endl;
			writeInFile.close();
		}
		else
			cout << "File Not open";
	}

	system("Pause");
	system("cls");
	cout << "1. Return to Menu\n2. Exit\n";
	cin >> choose;
	while (choose < 1 || choose > 2)
	{
		cout << "Invalid Choice! Enter Again= ";
		cin >> choose;
	}
	switch (choose)
	{
	case 1:
		mainMenu();
		break;
	case 2:
		cout << "Thank you for Playing";
		return;
	}
}

void saveForResuming(int uniqueID, string player1Name, int scoreP1, string player2Name, int scoreP2, string playerTurn, int player1Board[][SIZE_ARRAY], int player2Board[][SIZE_ARRAY])
{
	ofstream writeInFile;
	writeInFile.open("RESUME GAME.txt");
	if (writeInFile.is_open())
	{
		writeInFile << uniqueID << "\t" << player1Name << "\t" << scoreP1 << "\t" << player2Name << "\t" << scoreP2 << "\t" << playerTurn << endl;

		for (int i = 0; i < SIZE_ARRAY; i++)
			for (int j = 0; j < SIZE_ARRAY; j++)
				writeInFile << player1Board[i][j] << endl;

		for (int i = 0; i < SIZE_ARRAY; i++)
			for (int j = 0; j < SIZE_ARRAY; j++)
				writeInFile << player2Board[i][j] << endl;

		writeInFile.close();
	}
	else
		cout << "File Not open for saving";
}

void resumeGame(int& uniqueID, string& player1Name, int& scoreP1, string& player2Name, int& scoreP2, string& playerTurn, int player1Board[][SIZE_ARRAY], int player2Board[][SIZE_ARRAY])
{
	ifstream readFromFile;
	readFromFile.open("RESUME GAME.txt");
	if (readFromFile.is_open())
	{
		readFromFile >> uniqueID >> player1Name >> scoreP1 >> player2Name >> scoreP2 >> playerTurn;

		for (int i = 0; i < SIZE_ARRAY; i++)
			for (int j = 0; j < SIZE_ARRAY; j++)
				readFromFile >> player1Board[i][j];

		for (int i = 0; i < SIZE_ARRAY; i++)
			for (int j = 0; j < SIZE_ARRAY; j++)
				readFromFile >> player2Board[i][j];

		readFromFile.close();
	}
	else
		cout << "File Not open for resuming";
}

bool checkCharacters(string name)
{
	return regex_match(name, regex("^[A-Z a-z]+$"));			//regex to check if string contains only letters and Space 
}

void toss(string& playerTurn, string player1Name, string player2Name)
{
	srand(time(0));
	int tosschoice = 0, randomNumber;
	bool flag;
	int delay = 200, delay1 = 300;

	cout << player1Name << ",Select your Option? \n1.Heads  \n2.Tails \nEnter=  ";
	cin >> tosschoice;
	while (tosschoice < 1 || tosschoice > 2)
	{
		cout << "Invalid input. Enter again= ";
		cin >> tosschoice;
	}

	randomNumber = 1 + rand() % 2;
	if (randomNumber == 1)
	{
		if (tosschoice == 1)
			flag = true;
		else
			flag = false;
	}
	else
	{
		if (tosschoice == 2)
			flag = true;
		else
			flag = false;
	}
	flag == true ? playerTurn = player1Name : playerTurn = player2Name;

	system("cls");
	for (int i = 0; i < 10; ++i)
	{
		cout << "HEADS";
		Sleep(50);
		system("cls");
		cout << "TAILS";
		Sleep(50);
		system("cls");
	}
	//Showing Toss Result
	if (flag == true)
	{
		if (tosschoice == 1)
			cout << "HEADS";
		else
			cout << "TAILS";
	}
	else
	{
		if (tosschoice == 1)
			cout << "TAILS";
		else
			cout << "HEADS";
	}
	cout << endl;
}

void populateTable(int table1[][SIZE_ARRAY], int table2[][SIZE_ARRAY])
{
	srand(time(0));
	int num;

	for (int i = 0; i < SIZE_ARRAY; ++i)			//populating player one Table
	{
		for (int j = 0; j < SIZE_ARRAY; ++j)
		{
			num = rand() % 25 + 1;
			checkDuplicateNumber(table1, num) == true ? --j : table1[i][j] = num;

		}
	}

	for (int i = 0; i < SIZE_ARRAY; ++i)			//populating player two Table
	{
		for (int j = 0; j < SIZE_ARRAY; ++j)
		{
			num = rand() % 25 + 1;
			checkDuplicateNumber(table2, num) == true ? --j : table2[i][j] = num;

		}
	}
}

bool checkDuplicateNumber(const int table[][SIZE_ARRAY], int num)
{	//This Function prevents repeatation of Number in Table by scanning the whole table, if it find same number in the table it return true, else it return false
	int flag = false;
	for (int k = 0; k < SIZE_ARRAY; ++k)
	{
		for (int l = 0; l < SIZE_ARRAY; ++l)
		{
			if (table[k][l] == num)
			{
				return true;
			}
			else
				flag = false;
		}
	}
	return flag;
}

void drawBoard(int table[][SIZE_ARRAY], int score, string playerTurn)
{
	char BINGO[5] = { 'B','I','N','G','O' };
	system("cls");
	cout << "\t\t\t----|BINGO|----\n";


	for (int i = 0; i < 5; ++i)
		BINGO[i] = '\0';

	cout << playerTurn << "'s Turn!\n";
	cout << "        " << "   " << setw(1) << BINGO[0] << "      " << setw(1) << BINGO[1] << "      " << setw(1) << BINGO[2] << "      " << setw(1) << BINGO[3] << "      " << setw(1) << BINGO[4] << endl;
	cout << "       " << "____________________________________\n";
	for (int i = 0; i < SIZE_ARRAY; ++i)
	{
		cout << "       |" << "      |	     |      |      |      |\n";
		cout << "       |" << "  " << setw(2);
		
		//printing columns
		for (int j = 0; j < SIZE_ARRAY; j++)
		{
			if (table[i][j] == 0)
			{
				grayColor();
				cout << table[i][j];
				resetColor();
			}
			else
				cout << table[i][j];

			cout << "  |  " << setw(2);

		}

		cout << "\n       |" << "______|______|______|______|______|" << "\n";
	}

}

void replaceNumber(int table1[][SIZE_ARRAY], int table2[][SIZE_ARRAY], int num)
{
	//This Function Replaces the num with ZERO in Table of Both PLayers by scanning the whole table 
	for (int i = 0; i < SIZE_ARRAY; ++i)
	{
		for (int j = 0; j < SIZE_ARRAY; ++j)
		{
			if (table1[i][j] == num)
			{
				table1[i][j] = 0;
			}
			if (table2[i][j] == num)
			{
				table2[i][j] = 0;
			}
		}
	}
}

void updateScore(const int table[][SIZE_ARRAY], int& score)
{
	score = 0;
	int col;

	//ROWS
	for (int i = 0; i < SIZE_ARRAY; ++i)
	{
		if (table[i][0] == 0 && table[i][1] == 0 && table[i][2] == 0 && table[i][3] == 0 && table[i][4] == 0)
			score += 1;
	}

	//COLUMN
	for (int i = 0; i < SIZE_ARRAY; ++i)
	{
		if (table[0][i] == 0 && table[1][i] == 0 && table[2][i] == 0 && table[3][i] == 0 && table[4][i] == 0)
			score += 1;
	}

	//DIAGONAL
	if (table[0][0] == 0 && table[1][1] == 0 && table[2][2] == 0 && table[3][3] == 0 && table[4][4] == 0)
		score += 1;

	if (table[0][4] == 0 && table[1][3] == 0 && table[2][2] == 0 && table[3][1] == 0 && table[4][0] == 0)
		score += 1;
}