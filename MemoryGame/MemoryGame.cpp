#include "stdafx.h"
#include <iostream>
#include <random>
#include<ctime>
#include<Windows.h>
#include<iomanip>

using namespace std;

int redova = 4 * 4;
int kolona = 4 * 4;

struct Pozicija {
	int x;
	int y;
};

Pozicija jednaOtvorenaKarticaP;
bool jednaOtvorenaKartica = false;

void alokacija(char **&matrica)
{
	matrica = new char *[redova];
	for (int i = 0; i < redova; i++)
		matrica[i] = new char[kolona];
}

void dealokacija(char **&matrica)
{
	for (int i = 0; i < redova; i++)
		delete[] matrica[i];
	delete matrica;
	matrica = nullptr;
}

void ocisti(char **matrica)
{
	for (int i = 0; i < redova; i++)
		for (int j = 0; j < kolona; j++)
			matrica[i][j] = ' ';
}

void prikazi(char **matrica, char rjesenje[][4], bool otvoreno[][4])
{
	int ukrasBrojI, ukrasBrojJ;
	system("cls");
	cout << "\n------------------------------------+\n";
	cout << "|           IGRA MEMORIJE           |";
	cout << endl;
	for (int i = 0; i < redova; i++)
	{
		if (i % 4 == 0)
		{
			cout << "+";
			for (int i = 0; i < kolona; i++)
				cout << "--";
			cout << "---+";
			cout << endl;
		}
		for (int j = 0; j < kolona; j++)
		{
			if (j % 4 == 0)
				cout << "|";
			if (otvoreno[i / 4][j / 4])
				cout << rjesenje[i / 4][j / 4] << rjesenje[i / 4][j / 4];
			else
			{
				ukrasBrojI = (i - 2 + 4) % 4;
				ukrasBrojJ = (j - 4 + 4) % 4;

				if (ukrasBrojI == 0 && ukrasBrojJ == 2)
					cout << setw(2) << (i / 4) * 4 + j / 4 + 1;
				else
					cout << "  ";
			}
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int i = 0; i < kolona; i++)
		cout << "--";
	cout << "---+";
	cout << endl;
}

void izmisliRjesenje(char matrica[][4])
{
	srand(time(NULL));
	int slucajniZnak;
	bool ispravanZnak;
	int slucajnoMjestoX, slucajnoMjestoY;
	int brojac2 = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrica[i][j] = ' ';
		}
	}

	for (int i = 0; i < 8; i++)
	{
		slucajniZnak = i;
		brojac2 = 0;
		do
		{
			slucajnoMjestoX = rand() % 4;
			slucajnoMjestoY = rand() % 4;
			if (matrica[slucajnoMjestoY][slucajnoMjestoX] == ' ')
			{
				matrica[slucajnoMjestoY][slucajnoMjestoX] = slucajniZnak + 65;
				brojac2++;
			}
		} while (brojac2 != 2);
	}
}

void otvoriKartice(char **matrica, bool otvoreno[][4], char rjesenje[][4])
{
	int komanda;
	cout << "UNOS(1-16): ";
	do
	{
		cin >> komanda;
	} while (komanda<1 || komanda>16);
	komanda--;
	Pozicija polozaj;
	polozaj.x = komanda % 4;
	polozaj.y = komanda / 4;
	if (otvoreno[polozaj.y][polozaj.x] == true)
	{
		cout << "Kartica je vec otvorena!!!" << endl;
		return;
	}
	else
	{
		otvoreno[polozaj.y][polozaj.x] = true;
		if (jednaOtvorenaKartica)
		{
			prikazi(matrica, rjesenje, otvoreno);
			if (rjesenje[jednaOtvorenaKarticaP.y][jednaOtvorenaKarticaP.x] == rjesenje[polozaj.y][polozaj.x])
			{
				jednaOtvorenaKartica = false;
			}
			else
			{
				Sleep(1000);
				otvoreno[jednaOtvorenaKarticaP.y][jednaOtvorenaKarticaP.x] = false;
				jednaOtvorenaKartica = false;
				otvoreno[polozaj.y][polozaj.x] = false;
			}
		}
		else
		{
			jednaOtvorenaKartica = true;
			otvoreno[polozaj.y][polozaj.x] = true;
			jednaOtvorenaKarticaP.x = polozaj.x;
			jednaOtvorenaKarticaP.y = polozaj.y;
		}
	}
}

bool provjeriKraj(bool otvoreno[][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (!otvoreno[i][j])
				return false;
	return true;
}

void ispisiVrijeme(time_t start, time_t kraj)
{
	int sec = kraj - start;
	int min = sec / 60;
	sec %= 60;
	cout << "\n\n\n";
	cout << "-------------------------------------------------------\n";
	cout << "                VRIJEME: " << min << " min " << sec << " sec     \n";
	cout << "-------------------------------------------------------\n";
}

void main() {
	char **matrica = nullptr;
	alokacija(matrica);
	ocisti(matrica);
	char rjesenje[4][4];
	izmisliRjesenje(rjesenje);
	bool otvoreno[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	time_t vrijemeStart = time(0);
	do
	{
		prikazi(matrica, rjesenje, otvoreno);
		otvoriKartice(matrica, otvoreno, rjesenje);
	} while (!provjeriKraj(otvoreno));
	system("cls");
	time_t vrijemeKraj = time(0);
	ispisiVrijeme(vrijemeStart, vrijemeKraj);
	dealokacija(matrica);
	system("pause>0");
	system("pause>0");
}