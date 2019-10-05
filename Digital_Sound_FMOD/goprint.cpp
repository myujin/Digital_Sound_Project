#include"goprint.h"

void go_to_xy(int x, int y)                                  /* Go to the coordinate */
{
	COORD pos = { 2 * x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void go_print(int x, int y, float pos_x, float pos_z)                  /* Print the char */
{
	go_to_xy(x, y);
	printf("x:%f z:%f", pos_x, pos_z);
}

void print_boundary()
{
	go_to_xy(2, 2);
	printf("┏");
	for (int k = 0; k < 33; k++)
	{
		printf("━");
	}
	printf("┓\n");
	go_to_xy(2, 3);
	printf("┃");
	go_to_xy(19, 3);
	printf("┃\n");
	go_to_xy(2, 4);
	printf("┗");
	for (int k = 0; k < 33; k++)
	{
		printf("━");
	}
	printf("┛");
}

void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}