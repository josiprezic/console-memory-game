#include "stdafx.h"
#include <iostream>
#include <random>
#include<ctime>
#include<Windows.h>
#include<iomanip>

using namespace std;

int numberOfRows = 4 * 4;
int numberOfColumns = 4 * 4;

struct Position {
	int x;
	int y;
};

Position positionOfOneAndOnlyOpenCard;
bool oneOpenCard = false;

void allocation(char **&matrix)
{
	matrix = new char *[numberOfRows];
	for (int i = 0; i < numberOfRows; i++)
		matrix[i] = new char[numberOfColumns];
}

void deallocation(char **&matrix)
{
	for (int i = 0; i < numberOfRows; i++)
		delete[] matrix[i];
	delete matrix;
	matrix = nullptr;
}

void cleanMatrix(char **matrix)
{
	for (int i = 0; i < numberOfRows; i++)
		for (int j = 0; j < numberOfColumns; j++)
			matrix[i][j] = ' ';
}

void show(char **matrix, char resultMap[][4], bool open[][4])
{
	int decorationNumberI, decorationNumberJ;
	system("cls");
	cout << "\n------------------------------------+\n";
	cout << "|            MEMORY GAME            |";
	cout << endl;
	for (int i = 0; i < numberOfRows; i++)
	{
		if (i % 4 == 0)
		{
			cout << "+";
			for (int i = 0; i < numberOfColumns; i++)
				cout << "--";
			cout << "---+";
			cout << endl;
		}
		for (int j = 0; j < numberOfColumns; j++)
		{
			if (j % 4 == 0)
				cout << "|";
			if (open[i / 4][j / 4])
				cout << resultMap[i / 4][j / 4] << resultMap[i / 4][j / 4];
			else
			{
				decorationNumberI = (i - 2 + 4) % 4;
				decorationNumberJ = (j - 4 + 4) % 4;

				if (decorationNumberI == 0 && decorationNumberJ == 2)
					cout << setw(2) << (i / 4) * 4 + j / 4 + 1;
				else
					cout << "  ";
			}
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int i = 0; i < numberOfColumns; i++)
		cout << "--";
	cout << "---+";
	cout << endl;
}

void makeUpTheSolution(char matrix[][4])
{
	srand(time(NULL));
	int randomSign;
	bool correctSign;
	int randomX, randomY;
	int counter2 = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{ 
			matrix[i][j] = ' ';
		}
	}

	for (int i = 0; i < 8; i++)
	{
		randomSign = i;
		counter2 = 0;
		do
		{
			randomX = rand() % 4;
			randomY = rand() % 4;
			if (matrix[randomY][randomX] == ' ')
			{
				matrix[randomY][randomX] = randomSign + 65;
				counter2++;
			}
		} while (counter2 != 2);
	}
}

void openCards(char **matrix, bool open[][4], char solution[][4])
{
	int command;
	cout << "INPUT(1-16): ";
	do
	{
		cin >> command;
	} while (command<1 || command>16);
	command--;
	Position position;
	position.x = command % 4;
	position.y = command / 4;
	if (open[position.y][position.x] == true)
	{
		/*cout << "The card is already open" << endl;*/
		return;
	}
	else
	{
		open[position.y][position.x] = true;
		if (oneOpenCard)
		{
			show(matrix, solution, open);
			if (solution[positionOfOneAndOnlyOpenCard.y][positionOfOneAndOnlyOpenCard.x] == solution[position.y][position.x])
			{
				oneOpenCard = false;
			}
			else
			{
				Sleep(1000);
				open[positionOfOneAndOnlyOpenCard.y][positionOfOneAndOnlyOpenCard.x] = false;
				oneOpenCard = false;
				open[position.y][position.x] = false;
			}
		}
		else
		{
			oneOpenCard = true;
			open[position.y][position.x] = true;
			positionOfOneAndOnlyOpenCard.x = position.x;
			positionOfOneAndOnlyOpenCard.y = position.y;
		}
	}
}

bool checkForGameOver(bool open[][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (!open[i][j])
				return false;
	return true;
}

void printTime(time_t start, time_t end)
{
	int sec = end - start;
	int min = sec / 60;
	sec %= 60;
	cout << "\n\n\n";
	cout << "-------------------------------------------------------\n";
	cout << "                TIME: " << min << " min " << sec << " sec     \n";
	cout << "-------------------------------------------------------\n";
}

void main() {
	char **matrix = nullptr;
	allocation(matrix);
	cleanMatrix(matrix);
	char solution[4][4];
	makeUpTheSolution(solution);
	bool open[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	time_t startTime = time(0);
	do
	{
		show(matrix, solution, open);
		openCards(matrix, open, solution);
	} while (!checkForGameOver(open));
	system("cls");
	time_t endTime = time(0);
	printTime(startTime, endTime);
	deallocation(matrix);
	system("pause>0");
	system("pause>0");
}