#include "binary_trees.h"
#include <stdlib.h>

/**
 * tree_size - counts the number of nodes in a binary tree
 * @tree: pointer to the root node
 *
 * Return: number of nodes
 */
static size_t tree_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * binary_tree_is_complete - checks if a binary tree is complete
 * @tree: pointer to the root node of the tree to check
 *
 * Return: 1 if complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	binary_tree_t **queue;
	binary_tree_t *node;
	size_t size, front, rear;
	int must_be_leaf;

	if (tree == NULL)
		return (0);

	size = tree_size(tree);
	queue = malloc(sizeof(binary_tree_t *) * size);
	if (queue == NULL)
		return (0);

	front = 0;
	rear = 0;
	must_be_leaf = 0;

	queue[rear++] = (binary_tree_t *)tree;

	while (front < rear)
	{
		node = queue[front++];

		if (node->left != NULL)
		{
			if (must_be_leaf)
			{
				free(queue);
				return (0);
			}
			queue[rear++] = node->left;
		}
		else
			must_be_leaf = 1;

		if (node->right != NULL)
		{
			if (must_be_leaf)
			{
				free(queue);
				return (0);
			}
			queue[rear++] = node->right;
		}
		else
			must_be_leaf = 1;
	}

	free(queue);
	return (1);
}
