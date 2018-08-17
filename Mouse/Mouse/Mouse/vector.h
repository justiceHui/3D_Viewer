#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define M_W 200 // 3d 공간 x축 길이 (왼오)
#define M_H 200 // 3d 공간 y축 길이 (위아래)
#define M_D 200 // 3d 공간 z축 길이 (앞뒤)

typedef struct _pos {
	int x, y, z;
}POS;

typedef struct _vector {
	POS *arr;
	int cnt, size;
} VECTOR;

VECTOR newVector() {
	VECTOR ret;
	ret.arr = (POS*)malloc(sizeof(POS) * 5);
	ret.cnt = 0;
	ret.size = 0;
	return ret;
}

void deleteVector(VECTOR* a) {
	free(a->arr);
}

void push(VECTOR *a, POS *value) {
	if (a->cnt >= a->size) {
		if (a->size == 0) a->size = 5;
		else a->size *= 2;
		a->arr = (POS*)realloc(a->arr, a->size * sizeof(POS));
	}
	a->arr[a->cnt].x = value->x;
	a->arr[a->cnt].y = value->y;
	a->arr[a->cnt].z = value->z;
	a->cnt++;
}

int length(VECTOR *a) {
	return a->cnt;
}

POS pop(VECTOR *a) {
	POS ret;
	ret.x = a->arr[length(a) - 1].x;
	ret.y = a->arr[length(a) - 1].y;
	ret.z = a->arr[length(a) - 1].z;
	a->cnt--;
	return ret;
}

POS* begin(VECTOR *a) {
	return a->arr;
}

POS* end(VECTOR *a) {
	return a->arr + a->cnt;
}

void print(VECTOR *a) {
	int i;
	for (i = 0; i < length(a); i++) {
		printf("%d %d %d\n", a->arr[i].x, a->arr[i].y, a->arr[i].z);
	}
}