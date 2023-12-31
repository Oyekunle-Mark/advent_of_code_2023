#pragma once

struct Node {
	int item;
	Node* next;
}

void add_to_tail(Node*, int);
void remove_from_list(Node*, int);
void get_from_list(Node*, int, int*);
