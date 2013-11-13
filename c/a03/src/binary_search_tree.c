#include "binary_search_tree.h"

void insert_value(Node **root_pointer, char *new_value, int line_number)
{
	// Set up a new node
	Node *new_node;
	initialise_node(&new_node, new_value, line_number);

	insert_node(root_pointer, new_node);
}

void insert_node(Node **root_pointer, Node *new_node)
{
	Node *root = *root_pointer;

	int difference = strcasecmp(new_node->value, root->value);

	// If the value already exists...
	if (difference == 0)
	{
		DEBUG("%s already exists.\n", new_node->value);
		
		/*
		realloc_line_numbers_if_necessary(root_pointer);

		// Line number has already been set
		root->line_numbers[root->occurrences++] = new_node->line_numbers[0];
		*/

		return;
	}

	// If the new node has a lower value than the current root...
	if (difference < 0)
	{
		DEBUG("%s was less than %s!\n", new_node->value, root->value);

		if (root->left == NULL)
			root->left = new_node;
		else
			insert_node(&root->left, new_node);
	}

	// If the new node has a greater value than the current root...
	else
	{
		DEBUG("%s was greater than %s!\n", new_node->value, root->value);
		
		if (root->right == NULL)
			root->right = new_node;
		else
			insert_node(&root->right, new_node);
	}
}

void realloc_line_numbers_if_necessary(Node **root_pointer)
{
	Node *root = *root_pointer;

	// Is the array not half full yet?
	if (root->line_numbers_length > root->occurrences * 2)
	{
		return;
	}

	int new_length = root->line_numbers_length * 2;

	DEBUG("NEW LENGTH: %d\n", new_length);

	int *result_of_realloc = realloc(root->line_numbers, new_length);

	if (result_of_realloc != NULL)
	{
		root->line_numbers_length = new_length;
		root->line_numbers = result_of_realloc;
		DEBUG("Line number array reallocated to %d.\n", root->line_numbers_length);
	}
	else
	{
		DEBUG("Something went wrong when reallocating the line number array to %d.\n", new_length);
	}
}

void initialise_node(Node **node_pointer, char *value, int line_number)
{
	Node *node = malloc(sizeof(Node));

	int default_capacity = 10;

	node->value = value;
	node->occurrences = 1;
	
	node->line_numbers = malloc(default_capacity * sizeof(int));
	node->line_numbers_length = default_capacity;
	node->line_numbers[0] = line_number;

	*node_pointer = node;
}

Node* find_node(Node *current, char *target)
{
	// The target is not in the tree
	if (current == NULL)
		return NULL;

	int difference = strcasecmp(target, current->value);

	// Target == current node
	if (difference == 0)
		return current;

	// Target < current node -- move left
	else if (difference < 0)
		return find_node(current->left, target);

	// Target > current node -- move right
	else
		return find_node(current->right, target);
}

void print_node(Node *node)
{
	if (node == NULL)
	{
		printf("null\n");
		return;
	}
	
	// 0 is kind of the same as false, right?
	int plural = node->occurrences == 1 ? 0 : 1;
	
	printf("Node:\n{\n\tvalue: %s,\n\toccurs %d %s on %s:\n\t{\n",
		node->value,
		node->occurrences,
		plural ? "times" : "time",
		plural ? "lines" : "line"
		);

	printf("\t\t%d", node->line_numbers[0]);

	int i;
	for(i = 1; i < node->occurrences; i++)
	{
		printf(", %d", node->line_numbers[i]);
	}

	printf("\n\t}\n}\n");
}
