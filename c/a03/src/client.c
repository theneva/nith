#include "client.h"

int main(void)
{
	Node *root = malloc(sizeof(Node));
	root->value = "hello";
	
	print_node(root);

	const char *filename = "pg3400.txt";
	const char *mode = "r";

	FILE *book = fopen(filename, mode);

	if (book) { // was able to read
		DEBUG("[%s] was opened!\n", filename);
	} else {
		DEBUG("[%s] could not be opened.\n", filename);
		return -1;
	}
	
	insert_value(root, "zzz", 1);
	insert_value(root, "world", 2);
	insert_value(root, "ac", 3);
	insert_value(root, "banana", 3);
	insert_value(root, "ac", 5);

	// Print both children of root
	DEBUG("Left: %s\n", root->left == NULL ? "null" : root->left->value);
	DEBUG("Right: %s\n", root->right == NULL ? "null" : root->right->value);

	DEBUG("root->right->left: %s\n", root->right->left == NULL ? "null" : root->right->left->value);

	print_node(find_node(root, "zZZ"));
	printf("\n");
	print_node(find_node(root, "world"));
	printf("\n");
	print_node(find_node(root, "mumblemumble")); // doesn't exist
	printf("\n");
	print_node(find_node(root, "ac"));

	return 0;
}
