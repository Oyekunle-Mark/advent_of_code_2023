#include <stdlib.h>
#include <stdio.h>

#include "vec.h"

struct vector build() {
	int * items_ptr = (int *) malloc(DEFAULT_SIZE * sizeof(int)); // TODO: what happens when call to malloc fails?
	struct vector new_vec = { .items = items_ptr, .capacity = DEFAULT_SIZE };

	return new_vec;
}

size_t len(struct vector* vec) {
	return vec->length;
}

size_t capacity(struct vector* vec) {
	return vec->capacity;
}

void drop(struct vector* vec) {
	free(vec->items);
	vec->length = 0;
	vec->capacity = 0;
}

int get(struct vector* vec, size_t pos) {
	return vec->items[pos]; // TODO: handle cases where index out of bound of items is attempted to be assessed.
}

int put(struct vector* vec, int item) {
	if (vec->length == vec->capacity) {
		vec->items = (int*) realloc(vec->items, vec->capacity * 2);
		vec->capacity *= 2;
	}

	vec->items[vec->length++] = item;
	return 0; // better to return maybe a negative value when put fails(maybe incases where the vector couldn't be expanded successfully in a call to realloc
}
