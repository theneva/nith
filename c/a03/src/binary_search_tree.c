#include "binary_search_tree.h"

void insert_value(Node *root, char *new_value, int line_number)
{
	// Set up a new node
	Node *new_node = malloc(sizeof(Node));

	new_node->value = new_value;

	insert_node(root, new_node, line_number);
}

void insert_node(Node *root, Node *new_node, int line_number)
{
	if (root == NULL)
	{
		root = initialise_node(new_node, line_number);
		return;
	}

	int difference = strcasecmp(new_node->value, root->value);

	// If the value already exists...
	if (difference == 0)
	{
		DEBUG("%s already exists.\n", new_node->value);

		root->line_numbers[root->occurrences++] = line_number;

		// Double the size of the array whenever if necessary
		int line_number_array_capacity = sizeof(root->line_numbers) / sizeof(int);
		if (line_number_array_capacity < root->occurrences / 2)
		{
			int new_size = line_number_array_capacity * 2;
			
			int *result_of_realloc = realloc(root->line_numbers, new_size);

			if (result_of_realloc != NULL)
				DEBUG("Line number array reallocated to %d.\n", new_size);
			else
				DEBUG("Something went wrong when reallocating the line number array to %d.\n", line_number_array_capacity);
		}

		return;
	}



	// If the new node has a lower value than the current root...
	if (difference < 0)
	{
		DEBUG("%s was less than %s!\n", new_node->value, root->value);

		if (root->left == NULL)
			root->left = initialise_node(new_node, line_number);
		else
			insert_node(root->left, new_node, line_number);
	}

	// If the new node has a greater value than the current root...
	else
	{
		DEBUG("%s was greater than %s!\n", new_node->value, root->value);
		
		if (root->right == NULL)
			root->right = initialise_node(new_node, line_number);
		else
			insert_node(root->right, new_node, line_number);
	}
}

Node* initialise_node(Node *node, int line_number)
{
	node->line_numbers[0] = line_number;
	node->occurrences = 1;

	return node;
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
