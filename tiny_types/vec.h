#pragma once

#define DEFAULT_SIZE 16

struct vector {
	int length;
	int capacity;
	int* items;
};

struct vector build();
size_t len(struct vector*);
size_t capacity(struct vector*);
void drop(struct vector*);
int get(struct vector *, size_t);
int put(struct vector *, int);
