#include "client.h"

int main(void)
{
	Node *root;
	initialise_node(&root, "Hello", 0);

	print_node(root);

	insert_value(&root, "ac", 50);
	insert_value(&root, "zzz", 60);
	insert_value(&root, "yyy", 70);

	print_node(root->left);
	print_node(root->right);
	print_node(root->right->left);

	int i;
	for (i = 0; i < 19; i++)
	{
		insert_value(&root, "ac", i);
	}

		FILE *fp;
	const char *file_name = "pg3400.txt";
	const char *mode = "r";

	fp = fopen(file_name, mode);

	if (fp == NULL)
	{
		printf("Could not read the file. Terminating.");
		return -1;
	}

	DEBUG("[%s] was opened with mode: %s.\n", file_name, mode);

	const int line_length = 2000;
	char word[line_length];
	
	int line_number = 0;

	int word_counter = 0;

	// TODO remove word_counter
	while (word_counter++ < 20 && fscanf(fp, "%s", word) == 1)
	{
		printf("%s\n", word);
		insert_value(&root, word, line_number);
		printf("\n");

		int i;
		for (i = 0; i < 5000; i++) {
			printf("%s", "");
		}
	}

	DEBUG("The book [%s] was scanned.\n", file_name);

	printf("%s\n", root->value);
	printf("%s\n", root->right->value);

	fclose(fp);


/*
	print_node(find_node(root, "zZZ")); // case insensitive
	printf("\n");
	print_node(find_node(root, "world"));
	printf("\n");
	print_node(find_node(root, "mumblemumble")); // doesn't exist
	printf("\n");
	print_node(find_node(root, "ac"));

*/

	// printf("Size of 'ac' line numbers: %d\n", find_node(root, "ac")->line_numbers_length);
	return 0;
}
