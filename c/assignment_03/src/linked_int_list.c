#include "linked_int_list.h"

void initialize_linked_node(LinkedNode **node, int value)
{
	*node = malloc(sizeof(LinkedNode));

	(*node)->value = value;
	(*node)->next = NULL;
}

void add_linked_value(LinkedNode **head_pointer, int value)
{
	LinkedNode *head = *head_pointer;

	LinkedNode *new_node;
	initialize_linked_node(&new_node, value);

	// The list is empty.
	if (head == NULL)
	{
		head = new_node;
		return;
	}

	// The list has one element.
	if (head->next == NULL)
	{
		head->next = new_node;
		return;
	}

	// The list has more than one element.
	while (head->next != NULL)
	{
		head = head->next;
	}

	// head->next is now NULL.
	head->next = new_node;
}

void print_linked_list(LinkedNode *head)
{
	if (head == NULL)
	{
		printf("null\n");
		return;
	}
	
	printf("%d", head->value);

	while (head->next != NULL)
	{
		head = head->next;
		printf(", %d", head->value);
	}

	printf("\n");
}

void free_linked_list(LinkedNode **head_pointer)
{
	LinkedNode *head = *head_pointer;

	if (head == NULL)
	{
		return;
	}
	
	free(head);

	if (head->next == NULL)
	{
		return;
	}

	while (head->next != NULL)
	{
		LinkedNode *temp = head;
		head = head->next;
		free(temp);
	}

	free(head);
}
