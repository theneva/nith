#pragma once

#include <stdlib.h>

#include "helper.h"

/**
 * A linked int node.
 */
typedef struct LinkedNode
{
	int value;
	struct LinkedNode *next;
} LinkedNode;

/**
 * Initialises a linked int node.
 */
void initialize_linked_node(LinkedNode **node, int value);

/**
 * Adds a node to the linked list.
 */
void add_linked_value(LinkedNode **head_pointer, int value);

/**
 * Prints a list.
 */
void print_linked_list(LinkedNode *head);

/**
 * Frees a list.
 */
void free_linked_list(LinkedNode **head_pointer);
