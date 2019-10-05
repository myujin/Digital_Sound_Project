#include"goprint.h"

void go_to_xy(int x, int y)                                  /* Go to the coordinate */
{
	COORD pos = { 2 * x, y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void go_print(int x, int y, float pos_x,float pos_z)                  /* Print the char */
{
	go_to_xy(x, y);
	printf("x:%f z:%f", pos_x,pos_z);
}

void print_boundary()
{
	go_to_xy(2, 2);
	printf("旨");
	for (int k = 0; k < 33; k++)
	{
		printf("收");
	}
	printf("旬\n");
	go_to_xy(2, 3);
	printf("早");
	go_to_xy(19, 3);
	printf("早\n");
	go_to_xy(2, 4);
	printf("曲");
	for (int k = 0; k < 33; k++)
	{
		printf("收");
	}
	printf("旭");
}

void print_effect() {
	int nKey;
	go_to_xy(2, 6);
	printf("********** Sound Effect **********\n");
	go_to_xy(2, 7);
	printf("1: ROOM \n");
	go_to_xy(2, 8);
	printf("2: CAVE \n");
	go_to_xy(2, 9);
	printf("3: BATHROOM \n");
	go_to_xy(2, 10);
	printf("4: CONCERTHALL \n");
	go_to_xy(2, 11);
	printf("5: OFF \n");
}

void RemoveCursor()
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}