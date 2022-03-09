#include "iostream"
#include "cstdlib"
#include "conio.h"
#include "ctime"
#include "fstream"
using namespace std;

const int wysokosc = 27, szerokosc = 27;

void mapa(char s[][szerokosc]);  //Mapa na poczatku
void poziom(char s[][szerokosc]);  //Wczytywanie aktualnej mapy
void move(char s[][szerokosc], int &x, int &y, int &pkt);  //Ruch gracza i przeciwników
void czekaj();  //Czas po którym program wykona ponownie polecenia
void przeciwnicy(char s[][szerokosc], int x, int y, int &xp, int &yp, int &k, int &pod, int &koniec); //Poruszanie sie przeciwników
void kolizje(char s[][szerokosc], int x, int y, int xp, int yp, int &koniec);

struct przeciwnik
{
	int x;
	int y;
	int k;
	int pod;
};

int main()  //G³ówna funkcja
{
	przeciwnik p1 = { 1,17,0,1 };
	przeciwnik p2 = { 1,9,0,1 };
	przeciwnik p3 = { 3,23,0,1 };
	przeciwnik p4 = { 15,23,0,1 };
	przeciwnik p5 = { 3,3,0,1 };
	przeciwnik p6 = { 15,3,0,1 };
	przeciwnik p7 = { 3,13,0,1 };
	char s[wysokosc][szerokosc];
	int y = 25, x = 13, koniec = 0, pkt = 0;
	mapa(s);
	while (koniec == 0 || pkt == 370)
	{
		move(s, x, y, pkt);
		move(s, x, y, pkt);
		cout << "Aktualny wynik: " << pkt;
		czekaj();
		przeciwnicy(s, x, y, p1.x, p1.y, p1.k, p1.pod, koniec);
		przeciwnicy(s, x, y, p2.x, p2.y, p2.k, p2.pod, koniec);
		przeciwnicy(s, x, y, p3.x, p3.y, p3.k, p3.pod, koniec);
		przeciwnicy(s, x, y, p4.x, p4.y, p4.k, p4.pod, koniec);
		przeciwnicy(s, x, y, p5.x, p5.y, p5.k, p5.pod, koniec);
		przeciwnicy(s, x, y, p6.x, p6.y, p6.k, p6.pod, koniec);
		przeciwnicy(s, x, y, p7.x, p7.y, p7.k, p7.pod, koniec);
		system("cls");
		poziom(s);
	}
	for (int i = 0; i < 10; i++)
		czekaj();
	if (pkt == 370)
		cout << "Gratulacje wygra³eœ!" << endl;
	else
		cout << "Przegrana" << endl;
	cout << "Twoj wynik to: " << pkt << endl;
	system("pause");
	return 0;
}

void mapa(char s[][szerokosc]) //Mapa na poczatku
{
	ifstream plik;
	plik.open("mapa.txt");
	int i, j;
	for (i = 0; i < 27; i++)
	{
		for (j = 0; j < 27; j++)
		{
			plik >> s[i][j];
		}
	}
}

void poziom(char s[][szerokosc])  //Wczytywanie aktualnej mapy
{
	int i, j;
	for (i = 0; i < 27; i++)
	{
		for (j = 0; j < 27; j++)
		{
			cout << s[i][j];
		}
		cout << endl;
	}
}

void move(char s[][szerokosc], int &x, int &y, int &pkt) //Ruch gracza i przeciwników
{
	char znak;
	{
		if (_kbhit() == 1)
		{
			znak = _getch();
			switch (znak)
			{
			case 72:  //gora
				if (y > 1 && s[y - 1][x] != 'X')
				{
					if (s[y - 1][x] == '*')
						pkt++;
					s[y - 1][x] = 'G';
					s[y][x] = ' ';
					y--;
				}
				break;
			case 80:  //dol
				if (y < 25 && s[y + 1][x] != 'X')
				{
					if (s[y + 1][x] == '*')
						pkt++;
					s[y + 1][x] = 'G';
					s[y][x] = ' ';
					y++;
				}
				break;
			case 75:  //lewo
				if (x > 1 && s[y][x - 1] != 'X')
				{
					if (s[y][x - 1] == '*')
						pkt++;
					s[y][x - 1] = 'G';
					s[y][x] = ' ';
					x--;
				}
				break;
			case 77:  //prawo
				if (x < 25 && s[y][x + 1] != 'X')
				{
					if (s[y][x + 1] == '*')
						pkt++;
					s[y][x + 1] = 'G';
					s[y][x] = ' ';
					x++;
				}
				break;
			}
		}
	}
}

void czekaj()  //Czas po którym program wykona ponownie polecenia
{
	clock_t a;
	a = clock() + 0.1 * CLOCKS_PER_SEC;
	while (clock() < a) {}
}

void przeciwnicy(char s[][szerokosc], int x, int y, int &xp, int &yp, int &k, int &pod, int &koniec)
{
	kolizje(s, x, y, xp, yp, koniec);
	switch (k)
	{
	case 0:
		switch (pod)
		{
		case 1:
			s[yp][xp] = '*';
			break;
		case 0:
			s[yp][xp] = ' ';
			break;
		}
		if (s[yp][xp + 1] == '*')
			pod = 1;
		else
			pod = 0;
		if (s[yp][xp + 2] == 'X')
			k = 1;
		s[yp][xp + 1] = 'P';
		xp++;
		break;
	case 1:
		switch (pod)
		{
		case 1:
			s[yp][xp] = '*';
			break;
		case 0:
			s[yp][xp] = ' ';
			break;
		}
		if (s[yp][xp - 1] == '*')
			pod = 1;
		else
			pod = 0;
		if (s[yp][xp - 2] == 'X')
			k = 0;
		s[yp][xp - 1] = 'P';
		xp--;
		break;
	}
	kolizje(s, x, y, xp, yp, koniec);
}


void kolizje(char s[][szerokosc], int x, int y, int xp, int yp, int &koniec)
{
	if (x == xp&&y == yp)
	{
		system("cls");
		poziom(s);
		czekaj();
		koniec = 1;
	}
}