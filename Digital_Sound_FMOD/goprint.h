#pragma once
#ifndef GOPRINT_H_INCLUDED
#define GOPRINT_H_INCLUDED

/*
Go_print.h 파일은 출력과 관련된 기능인 함수를 다루는 헤더파일입니다.
*/

#include <stdio.h>
#include <windows.h>

void go_to_xy(int x, int y);
void go_print(int x, int y, float pos_x, float pos_z);
void print_boundary();
void RemoveCursor();

#endif // GOPRINT_H_INCLUDED