#include <iostream>
#include <Windows.h>
#include <conio.h>

#pragma execution_character_set("utf-8");

#define SLEEP_TIME 300

#define PUZZLE_SIZE 25
#define PUZZLE_ROW 5
#define PUZZLE_COL 5
#define BLANK	-1
#define W		-5
#define S		 5
#define A		-1
#define D		 1

enum DIRECTION {
	DIRECTION_UP,	// W
	DIRECTION_DOWN, // S
	DIRECTION_LEFT, // A
	DIRECTION_RIGHT,// D

	DIRECTION_COUNT
};


using std::cout;
using std::endl;
using std::cin;

int main()
{
	SetConsoleOutputCP(65001);
	SetConsoleTitle(L"Numer Puzzle");
	system("mode con:cols=50 lines=30");
	srand(time(NULL));

	int iPuzzle[PUZZLE_SIZE];
	for (int i = 0; i < 24; i++)
	{
		iPuzzle[i] = i + 1;
	}
	int blanckIdx = PUZZLE_SIZE - 1;
	iPuzzle[blanckIdx] = BLANK;


	bool bExit = false;

	// Shuffle
	system("cls");
	cout << "\t_____________ PUZZLE _____________" << endl << endl << endl;

	int suffleCount;
	cout << "\t\tShuffle Count : ";
	cin >> suffleCount;

	int switchIdx = 0;
	for (int i = 0; i < suffleCount; i++)
	{
		int direction = rand() % DIRECTION_COUNT;
		bool bSwap = true;
		switch (direction)
		{
		case DIRECTION_UP:
			switchIdx = blanckIdx + W;
			if (0 > switchIdx)
				bSwap = false;
			break;
		case DIRECTION_DOWN:
			switchIdx = blanckIdx + S;
			if (switchIdx > 25)
				bSwap = false;
			break;
		case DIRECTION_LEFT:
			switchIdx = blanckIdx + A;
			if (blanckIdx % 5 == 0)
				bSwap = false;
			break;
		case DIRECTION_RIGHT:
			switchIdx = blanckIdx + D;
			if (blanckIdx % 5 == 4)
				bSwap = false;
			break;
		}

		if (bSwap)
		{
			iPuzzle[blanckIdx] = iPuzzle[switchIdx];
			iPuzzle[switchIdx] = BLANK;
			blanckIdx = switchIdx;
		}
		else
		{
			i--;
			continue;
		}


		system("cls");
		cout << "\t_____________ PUZZLE _____________" << endl << endl << endl;
		for (int j = 0; j < PUZZLE_ROW; j++)
		{
			cout << "\t";
			for (int k = 0; k < PUZZLE_COL; k++)
			{
				if (j * PUZZLE_COL + k == switchIdx)
					cout << "\t";
				else
					cout << iPuzzle[j * PUZZLE_COL + k] << "\t";
			}
			cout << endl << endl << endl << endl;
		}
		Sleep(SLEEP_TIME);


	}


	// Game Logic
	int totalGameCount = 0;
	while (true)
	{
		system("cls");
		cout << "\t_____________ PUZZLE _____________" << endl << endl << endl;

		for (int i = 0; i < 5; i++)
		{
			cout << "\t";
			for (int j = 0; j < 5; j++)
			{
				if (iPuzzle[i * 5 + j] == -1)
				{
					blanckIdx = i * 5 + j;
					cout << "\t";
				}
				else
				{
					cout << iPuzzle[i * 5 + j] << "\t";

				}
			}
			cout << endl << endl << endl << endl;
		}

		bool bClear = true;
		for (int i = 0; i < 24; i++)
		{
			if (iPuzzle[i] != i + 1)
			{
				bClear = false;
				break;
			}
		}

		if (bClear)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
			cout << "\t------------------------------------" << endl;
			cout << "\t\t G A M E   C L E A R" << endl;
			cout << "\t------------------------------------";
			Sleep(1000);

			break;
		}

		cout << "\tMove: " << totalGameCount << endl;
		cout << "\tW: ก่" << "\t";
		cout << "S: ก้" << "\t";
		cout << "A: ก็" << "\t";
		cout << "D: กๆ" << endl;
		cout << "\tX: Exit" << endl << endl;

		// Move
		int switchIdx = 0;
		bool bSwap = false;
		switch (_getch())
		{
		case 'W':
		case 'w':
			switchIdx = blanckIdx + W;
			if (switchIdx >= 0)
				bSwap = true;
			break;
		case 'S':
		case 's':
			switchIdx = blanckIdx + S;
			if (switchIdx <= 25)
				bSwap = true;
			break;
		case 'A':
		case 'a':
			switchIdx = blanckIdx + A;
			if (switchIdx % 5 != 4)
				bSwap = true;
			break;
		case 'D':
		case 'd':
			switchIdx = blanckIdx + D;
			if (switchIdx % 5 != 0)
				bSwap = true;
			break;
		case 'X':
		case 'x':
			bExit = true;
			break;
		}

		if (bSwap)
		{
			iPuzzle[blanckIdx] = iPuzzle[switchIdx];
			iPuzzle[switchIdx] = BLANK;
			++totalGameCount;
		}

		if (bExit)
		{
			break;
		}

	}
	Sleep(500);
	return 0;
}