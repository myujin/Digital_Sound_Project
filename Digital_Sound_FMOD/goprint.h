#pragma once
#ifndef GOPRINT_H_INCLUDED
#define GOPRINT_H_INCLUDED

/*
Go_print.h ������ ��°� ���õ� ����� �Լ��� �ٷ�� ��������Դϴ�.
*/

#include <stdio.h>
#include <windows.h>

void go_to_xy(int x, int y);
void go_print(int x, int y, float pos_x, float pos_z);
void print_boundary();
void RemoveCursor();

#endif // GOPRINT_H_INCLUDED