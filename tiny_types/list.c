#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "vec.h"

void add_to_tail(struct Node** head, char* key, int value)
{
	if (*head == NULL) {
		struct Node* new = (struct Node *) malloc(sizeof(struct Node));
		new->key = key;
		new->value = value;
		new->next = NULL;

		*head = new;
		return;
	}

	struct Node* new = (struct Node *) malloc(sizeof(struct Node));
	new->key = key;
	new->value = value;
	new->next = NULL;

	(*head)->next = new;
	return;
}

void remove_from_list(struct Node** head, char* key)
{
	if (*head == NULL) return;

	if (strcmp((*head)->key, key) == 0) {
		*head = (*head)->next;
		return;
	}

	struct Node* prev = *head;
	struct Node* curr = (*head)->next;

	while(curr) {
		if (strcmp(curr->key, key) == 0) {
			prev->next = curr->next;
			break;
		}

		prev = curr;
		curr = curr->next;
	}

	return;
}

void get_from_list(struct Node** head, char* key, int** value)
{
	struct Node* curr = *head;

	while(curr) {
		if (strcmp(curr->key, key) == 0) {
			*value = &(curr->value);
			return;
		}

		curr = curr->next;
	}

	*value = NULL;
	return;
}

void free_list(struct Node** head)
{
	// if (*head == NULL) return;

	// struct Node* next_ptr = (*head)->next;

	// if  (next_ptr == NULL) {
	// 	free(*head);
	// 	return;
	// }

	// struct Node curr = *next_ptr;

	// free(*head);

	// while(next) {
	// 	struct Node* prev = next;
	// 	next = next->next;
	// 	free(prev);
	// }

	// FIXME: leaking memory
}
