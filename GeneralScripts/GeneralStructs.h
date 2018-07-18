#pragma once

typedef struct {
	int x;
	int y;
} Vector2;

static int CompareVector2(Vector2 vec1, Vector2 vec2) {
	if (vec1.x == vec2.x &&
		vec1.y == vec2.y) {
		return 1;
	}
	return 0;
}

static void PrintVector2(Vector2 vec2) {
	printf("{%d, %d}", vec2.x, vec2.y);
}