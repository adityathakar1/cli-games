#include<iostream>
#include<conio.h>
#include<windows.h>
#include<chrono>
#include<thread>
using namespace std;
bool gameover;
int width = 30;
int height = 24;
int headx, heady;
int fruitx, fruity;
int tailx[100], taily[100];
int tailsize;
int score;
char ans = 'n';
enum Direction{
	STOP =0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
enum Direction dir;
void setup();
void draw();
void input();
void logic();
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(short x, short y)
{
	COORD pos = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
int main()
{
	restart:
	setup();
	while (!gameover)
	{
		this_thread::sleep_for(chrono::milliseconds(150));
		input();
		logic();
		draw();
		if (ans == 'y' || ans=='Y')
			goto restart;	

	}
}
void setup()
{
	system("color 06");	
	system("cls");
	gotoxy(width+5, 2);
	cout << "Hungry Snake";
	gotoxy(width+5, 4);
	cout << "Controls :  8 - UP";
	gotoxy(width+17, 5 );
	cout << "2 - DOWN";
	gotoxy(width+17, 6 );
	cout << "4 - LEFT";
	gotoxy(width+17, 7 );
	cout << "6 - RIGHT";
	gotoxy(width+17, 8 );
	cout << "5 - STOP";
	gotoxy(width+5, 10 );
	
	cout << "KUKI ENJOY...!!!";
	ans = 'n';
	dir = STOP;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
	gameover = false;
	tailsize = 1;
	score = 0;
	srand(time(0));
	do{
			fruitx = (rand() % (width - 3)) + 3;
			fruity = (rand() % (height - 3)) + 3;	
	}while(fruitx == 0 || fruitx == (width-1) || fruity == 0 || fruity == (height-1));
		
	headx = width/2;
	heady = height/2;	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if(x == 0 || x == (width-1) || y == 0 || y == (height-1))
			{
				SetConsoleTextAttribute( console , 244);			
				gotoxy(x,y);
				cout << char(219);
			}
			else if (x == headx && y == heady)
			{
				SetConsoleTextAttribute( console , 242);
				cout << 'O';
			}
			else if (x == fruitx && y== fruity)
			{
			
				SetConsoleTextAttribute( console , 245);
				cout << char(232);
			}
			else
			{
				cout << ' ';
			}
		}
	}
	SetConsoleTextAttribute( console , 06);
	gotoxy(0, short(height+1));
	cout << "Score = " << score;
	SetConsoleTextAttribute( console , 245);
}
void input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'w':
				if(dir != DOWN)
					dir = UP;
				break;
			case 's':
				if(dir != UP)
					dir = DOWN;
				break;
			case 'a':
				if(dir != RIGHT)
					dir = LEFT;
				break;
			case 'd':
				if(dir != LEFT)
					dir = RIGHT;
				break;
			case 'x':
				dir = STOP;
				break;
		}
	}
}
void logic()
{
	switch(dir)
	{
		case UP:
			if(heady>=1)
				heady--;
			break;
		case DOWN:
			if (heady<(height-1))
				heady++;
			break;
		case LEFT:
			if (headx>=1)
				headx--;
			break;
		case RIGHT:
			if (headx< (width-1))
				headx++;
			break;
	}
	if(headx == fruitx && heady == fruity)
	{
		Beep(900, 90);
		score++;
		tailsize++;
		do{
			fruitx = (rand() % (width - 3)) + 3;
			fruity = (rand() % (height - 3)) + 3;	
		}while(fruitx == 0 || fruitx == (width-1) || fruity == 0 || fruity == (height-1));
		SetConsoleTextAttribute( console , 06);
		gotoxy(0, short(height+1));
		cout << "Score = " << score;
	}
	
	else if(headx == 0 || headx == (width-1) || heady == 0 || heady == (height-1))
	{
		GAMEOVER:
		Beep(500, 1000);
		gameover = true; 
		system("cls");
		cout << "Game Over \nWanna try your luck again (y/n) : ";
		cin >> ans;
		if ( ans=='n' || ans == 'N')
		{
			system("cls");
			cout<< "Thanks for playing...come back soon..!!!";
			tailsize = 0;
			
		}
		goto END;
	}
	
	
	int prevx, prevy, prev2x, prev2y;
	for (int n = 1; n< tailsize; n++)
	{
		if(headx == tailx[n] && heady == taily[n])
			goto GAMEOVER;
		
	}
	END:
	prevx = tailx[0];
	prevy = taily[0];
	tailx[0] = headx;
	taily[0] = heady;
	for(int n= 1; n< tailsize; n++)
	{
		prev2x = tailx[n];
		prev2y = taily[n];
		tailx[n] = prevx;
		taily[n] = prevy;
		prevx = prev2x;
		prevy = prev2y;
		
	}
	
	
}
int tempx=1, tempy=1;
void draw()
{
	
	if(!gameover)
	{
		gotoxy(short(tempx), short(tempy));
		cout << ' ';
		gotoxy(short(headx), short(heady));
		SetConsoleTextAttribute( console , 242);
		cout << 'O';
		for(int n = 1; n < tailsize ; n++)
		{
			gotoxy(short(tailx[n]), short(taily[n]));
			cout << 'o';
		}
		gotoxy(short(fruitx), short(fruity));
		SetConsoleTextAttribute( console , 245);
		cout << char(232);
		if (tailsize==0)
		{
			tempx = headx;
			tempy = heady;	
		}
		else
		{
			tempx = tailx[tailsize-1];
			tempy = taily[tailsize-1];
			
		}
		
	}
}
