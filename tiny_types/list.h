#pragma once

struct Node {
	char* key;
	int value;
	struct Node* next;
};

void add_to_tail(struct Node**, char*, int);
void remove_from_list(struct Node**, char*);
void get_from_list(struct Node**, char*, int**);
void free_list(struct Node**);
