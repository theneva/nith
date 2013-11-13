#include "client.h"

int main(void)
{

	Node *root;
	initialize_node(&root, "", 1);

// The function works properly as long as it's not called inside the loop.
	// Yes, seriously.
/*
	add_value(root, "The", 0);
	printf("\n");
	add_value(root, "Project", 0);
	printf("\n");
	add_value(root, "Gutenberg", 0);
	printf("\n");
	add_value(root, "EBook", 0);
	printf("\n");
	add_value(root, "of", 0);
	printf("\n");
	add_value(root, "Ulysses,", 0);
	printf("\n");
	add_value(root, "By", 0);
	printf("\n");
	add_value(root, "James", 0);
	printf("\n");
	add_value(root, "Joyce", 0);
*/

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

	// TODO remove word_counter and condition -- for debugging purposes only.
	int word_counter = 0;
	while (word_counter++ < 20 && fscanf(fp, "%s", word) == 1)
	{
		printf("%s\n", word);

		// Apparently, every single word exists already
			// ... unless it can be a child of a word that existed before this loop.
		add_value(root, word, line_number);
		printf("\n");
	}

	DEBUG("The book [%s] was scanned.\n", file_name);

	printf("%s\n", root->value);
	printf("%s\n", root->right->value);

	fclose(fp);

	return 0;
}
