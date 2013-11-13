#include "binary_search_tree.h"

void initialize_node(Node **node_pointer, char *value, int line_number)
{
	// Set up a new node, allocate, and initializ
	*node_pointer = malloc(sizeof(Node));

	Node *node = *node_pointer;
	node->value = value;

	node->occurrences = 1;

	add_linked_value(&node->line_numbers, line_number);
	
	// Initialize these guys as well.
	node->left = NULL;
	node->right = NULL;
}

void add_value(Node *root, char *value, int line_number)
{
	Node *node;
	initialize_node(&node, value, line_number);

	add_node(root, node);
}

void add_node(Node *root, Node *new_node)
{

	int difference = strcasecmp(new_node->value, root->value);

	DEBUG("Root value = %s\nNew  value = %s\nDiff = %d\n\n", root->value, new_node->value, difference);
	
	// The value exists already.
	if (difference == 0)
	{
		// TODO add occurrence
		DEBUG("%s already exists.\n", new_node->value);
	}

	// New < root and goes to the left.
	else if (difference < 0)
	{
		if (root->left != NULL)
		{
			DEBUG("%s < %s and moves left.\n", new_node->value, root->value);
			add_node(root->left, new_node);
		}
		else
		{
			DEBUG("Adding %s to %s's left.\n", new_node->value, root->value);
			root->left = new_node;
		}
	}

	// New > root and goes to the right.
	else
	{
		// A node already exists
		if (root->right != NULL)
		{
			DEBUG("%s > %s and moves right.\n", new_node->value, root->value);
			add_node(root->right, new_node);
		}
		else
		{
			DEBUG("Adding %s to %s's right.\n", new_node->value, root->value);
			root->right = new_node;
		}
	}
}

Node* find_node(Node *root, char *target)
{
	// The target is not in the tree
	if (root == NULL)
		return NULL;

	int difference = strcasecmp(target, root->value);

	// Target == root node
	if (difference == 0)
		return root;

	// Target < root node -- move left
	else if (difference < 0)
		return find_node(root->left, target);

	// Target > root node -- move right
	else
		return find_node(root->right, target);
}

void print_node(Node *node)
{
 	if (node == NULL)
 	{
 		printf("null\n");
 		return;
 	}

 	printf("Node: { value = %s, }\n", node->value);
}
