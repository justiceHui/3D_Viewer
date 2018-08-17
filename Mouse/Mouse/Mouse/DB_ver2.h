#pragma once
#include<windows.h>
#include<stdio.h>

#define S_W 180 // ȭ�� ���� ����
#define S_H 50 // ȭ�� ���� ����

char back_buffer[S_H][S_W] = { 0, }; //���߹��۸� �� ����
char front_buffer[S_H][S_W] = { 0, }; //���߹��۸� ����Ʈ ����

void cursor() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 0;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	return;
}

void gotoxy(int x, int y) { // Ŀ�� ��ġ �̵�(API)
	COORD CursorPosition = { (short)x,(short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
}

void draw(int x, int y, const char *image) { //����ۿ� ����� ���� ����
	int i;
	for (i = 0; image[i] != '\0'; i++) back_buffer[y][x + i] = image[i];
}

void render() { //����Ʈ ���۶� �ٸ� �κи� �ٲ�
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

void copy() { // ����۸� ����Ʈ ���ۿ� ����
	int i, j;
	for (i = 0; i<S_H; i++) {
		for (j = 0; j<S_W; j++) {
			front_buffer[i][j] = back_buffer[i][j];
			back_buffer[i][j] = '\0';
		}
	}
}