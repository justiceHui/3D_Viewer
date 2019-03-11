#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<windows.h>
#include <string.h>
#include <stdlib.h>
#include "shape.h"
#include "move.h"
#include "DB_ver2.h" //자작 헤더

static int s = 20;
int map[M_W][M_H][M_D] = { '\0', }; //3D 공간
SHAPE shape;
int cubeSize = 20;
int x, y, z;
int xa = 0, ya = 0;

double deg2rad(double angle) {
	return angle / 180 * 3.14;
}

int main() {
	int i, j, k, c;
	shape = newShape();
	x = y = z = 0;
	//x = 10;
	for (i = -1 * cubeSize; i <= cubeSize; i++) { //정육면체 이동
		for (j = -1 * cubeSize; j <= cubeSize; j++) {
			for (k = -1 * cubeSize; k <= cubeSize; k++) {
				if ((abs(i) == cubeSize) + (abs(j) == cubeSize) + (abs(k) == cubeSize) > 1) {
					POS input;
					input.x = M_W / 2 + i; //0이고  초기값이라서 안더해도 됨
					input.y = M_H / 2 + j;
					input.z = M_D / 2 + k;
					push(&shape.arr, &input);
				}
			}
		}
	}
	cursor();
	system("mode con cols=180 lines=50"); //화면 크기 
	while (1) {
		SHAPE tmpShape = newShape();
		SHAPE tmptmpShape = newShape();
		memset(map, 0, sizeof(map));
		if (kbhit() != 0) { //키보드 입력
			c = getch();
			switch (c) {
			case 'a': {
				x--;
				break;
			}
			case 'd': {
				x++;
				break;
			}
			case 'w': {
				y--;
				break;
			}
			case 's': {
				y++;
				break;
			}
			case 'z': {
				z++;
				break;
			}
			case 'x': {
				z--;
				break;
			}
			case 'j': {
				xa -= 10;
				break;
			}
			case 'l': {
				xa += 10;
				break;
			}
			case 'i': {
				ya += 10;
				break;
			}
			case 'k': {
				ya -= 10;
				break;
			}
			case 'o': {
				xa += 10; ya += 10;
				break;
			}
			case 'u': {
				xa -= 10; ya += 10;
				break;
			}
			}
		}
		gotoxy(0, 0);
		xa = (xa + 720) % 360;
		ya = (ya + 720) % 360;
		for (i = 0; i < shape.arr.cnt; i++) {
			y_rot(&tmptmpShape.arr, &shape.arr.arr[i], deg2rad(xa), x, y, z);
			x_rot(&tmpShape.arr, &tmptmpShape.arr.arr[i], deg2rad(ya), x, y, z);
		}
		for (i = 0; i < tmpShape.arr.cnt; i++) {
			tmpShape.arr.arr[i].x += x;
			tmpShape.arr.arr[i].y += y;
			tmpShape.arr.arr[i].z += z;
		}

		for (i = 0; i < tmpShape.arr.cnt; i++) {
			map[tmpShape.arr.arr[i].x][tmpShape.arr.arr[i].y][tmpShape.arr.arr[i].z] = 1;
		}

		printf("(%d %d %d %d %d)", x, y, z, xa, ya);
		for (i = -1 * M_H / 2; i < M_H / 2; i++) { //제일 중요한 부분 시야 구현
			for (j = -1 * M_W / 2; j < M_W / 2; j++) {
				for (int k = -1 * M_D / 2; k < M_D / 2; k++) {
					if (map[M_W / 2 + i][M_W / 2 + j][M_D / 2 + k] == 1 && k > 0) { //k가 z이면 zero division 오류
						if ((i)* s / (k) >= -1 * S_W / 2 && (i)* s / (k) < S_W / 2 && (j)* s / (k) >= -1 * S_H / 2 && (j)* s / (k) < S_H / 2) {
							draw(S_W / 2 + (i)* s / (k), S_H / 2 + (j)* s / (k), "*");
						}
					}
				}
			}
		}
		render(); // DB의 렌더링 함수
		copy(); // DB의 복사 함수
	}
}
