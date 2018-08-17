#pragma once
#include "vector.h"

typedef struct _shape {
	VECTOR arr;
}SHAPE;

SHAPE newShape() {
	SHAPE ret;
	ret.arr = newVector();
	return ret;
}

void pushDot(SHAPE *a, POS *value) {
	push(&a->arr, value);
}
