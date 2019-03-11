#include "shape.h"
#include <stdlib.h>

void y_rot(VECTOR *a, POS *value, double theta, int x, int y, int z) {
	if (a->cnt >= a->size) {
		if (a->size == 0) a->size = 5;
		else a->size *= 2;
		a->arr = (POS*)realloc(a->arr, a->size * sizeof(POS));
	}
	a->arr[a->cnt].x = (value->x - M_W / 2)*cos(theta) - (value->z - M_D / 2)*sin(theta) + M_W / 2;
	a->arr[a->cnt].y = value->y;
	a->arr[a->cnt].z = (value->x - M_W / 2)*sin(theta) + (value->z - M_D / 2)*cos(theta) + M_D / 2;
	a->cnt++;
}

void x_rot(VECTOR *a, POS *value, double theta, int x, int y, int z) {
	if (a->cnt >= a->size) {
		if (a->size == 0) a->size = 5;
		else a->size *= 2;
		a->arr = (POS*)realloc(a->arr, a->size * sizeof(POS));
	}
	a->arr[a->cnt].x = value->x;
	a->arr[a->cnt].y = (value->y - M_W / 2)*sin(theta) - (value->z - M_H / 2)*cos(theta) + M_H / 2;
	a->arr[a->cnt].z = (value->y - M_W / 2)*cos(theta) + (value->z - M_H / 2)*sin(theta) + M_W / 2;
	a->cnt++;
}
