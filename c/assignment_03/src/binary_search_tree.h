#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "helper.h"
#include "linked_int_list.h"

/**
 * A node in the binary search tree.
 */
typedef struct Node
{

	/** The text value. */
 	char *value;

 	/** The number of times the word has occurred. */
 	int occurrences;

 	/** The line numbers on which the word has occurred. */
 	LinkedNode *line_numbers;

	/** The children. */
 	struct Node *left, *right;
 } Node;

/**
 * Initializes a node.
 */
void initialize_node(Node **node_pointer, char *value, int line_number);

/**
 * Adds a value to the tree.
 */
void add_value(Node *root, char *value, int line_number);

/**
 * Adds a node to the tree.
 */
void add_node(Node *root, Node *new_node);

/**
 * Finds a node based on its value.
 */
Node* find_node(Node *current, char *target);

/**
 * Pretty-prints a node.
 */
void print_node(Node *node);
