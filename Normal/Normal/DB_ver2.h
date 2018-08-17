#pragma once
#include<windows.h>
#include<stdio.h>

#define S_W 180 // 화면 가로 길이
#define S_H 50 // 화면 세로 길이

char back_buffer[S_H][S_W] = { 0, }; //이중버퍼링 백 버퍼
char front_buffer[S_H][S_W] = { 0, }; //이중버퍼링 프론트 버퍼

void cursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 0;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	return;
}

void gotoxy(int x, int y) { // 커서 위치 이동(API)
	COORD CursorPosition = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void draw(int x, int y, const char *image) { //백버퍼에 출력할 내용 저장
	int i;
	for (i = 0; image[i] != '\0'; i++) back_buffer[y][x + i] = image[i];
}

void render() { //프론트 버퍼랑 다른 부분만 바꿈
	int i, j;
	for (i = 0; i<S_H; i++) {
		for (j = 0; j<S_W; j++) {
			if (front_buffer[i][j] != back_buffer[i][j] && i >= 0 && i < S_H && j >= 0 && j < S_W) {
				gotoxy(j, i);
				if (back_buffer[i][j] == '\0') printf(" ");
				else printf("%c", back_buffer[i][j]);
			}
		}
	}
}

void copy() { // 백버퍼를 프론트 버퍼에 복사
	int i, j;
	for (i = 0; i<S_H; i++) {
		for (j = 0; j<S_W; j++) {
			front_buffer[i][j] = back_buffer[i][j];
			back_buffer[i][j] = '\0';
		}
	}
}