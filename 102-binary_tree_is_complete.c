#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_is_complete - checks if a binary tree is complete
 * @tree: pointer to the root node
 *
 * Return: 1 if complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	const binary_tree_t **q, *node;
	size_t size, front = 0, back = 0;
	int seen_null = 0;

	if (!tree)
		return (0);

	size = binary_tree_size(tree);
	q = malloc(sizeof(*q) * size);
	if (!q)
		return (0);

	q[back++] = tree;
	while (front < back)
	{
		node = q[front++];
		if (node->left)
		{ if (seen_null) { free(q); return (0); } q[back++] = node->left; }
		else
			seen_null = 1;

		if (node->right)
		{ if (seen_null) { free(q); return (0); } q[back++] = node->right; }
		else
			seen_null = 1;
	}
	free(q);
	return (1);
}
