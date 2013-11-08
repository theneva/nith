#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "helper.h"

/**
 * A node in the binary search tree.
 */
typedef struct Node
{
	char *value;

	// Will be initialised to 10 and expanded dynamically.
	int *line_numbers; // to be used as an array.
	int line_numbers_length;

	int occurrences;

	struct Node *left, *right;
} Node;

/**
 * Adds a new value to the binary search tree.
 */
void insert_value(Node **root, char *new_value, int line_number);

/**
 * Adds a new node to the binary search tree.
 */
void insert_node(Node **root_pointer, Node *new_node);

/**
 * Reallocates the size of the line number array if necessary.
 */
void realloc_line_numbers_if_necessary(Node **root_pointer);

/**
 * Initialises a node to default values.
 */
void initialise_node(Node **node, char *value, int line_number);

/**
 * Retrieves a node based on its value, or NULL if it does not exist. Case insensitive.
 */
Node* find_node(Node *current, char *target);

/**
 * Prints a node.
 */
void print_node(Node *node);
