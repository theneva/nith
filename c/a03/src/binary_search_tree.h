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

	// Default value, will be expanded
	int line_numbers[10];
	int occurrences;

	struct Node *left, *right;
} Node;

/**
 * Adds a new value to the binary search tree.
 */
void insert_value(Node *root, char *new_value, int line_number);

/**
 * Adds a new node to the binary search tree.
 */
void insert_node(Node *root, Node *new_node, int line_number);

/**
 * Initialises a node to default values.
 */
Node* initialise_node(Node *node, int line_number);

/**
 * Retrieves a node based on its value, or NULL if it does not exist. Case insensitive.
 */
Node* find_node(Node *current, char *target);

/**
 * Prints a node.
 */
void print_node(Node *node);
