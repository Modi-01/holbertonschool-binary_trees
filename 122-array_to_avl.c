#include "binary_trees.h"

/**
 * avl_find - Find a node by value in an AVL tree
 * @root: Pointer to the root node of the AVL tree
 * @value: Value to search for
 *
 * Return: Pointer to the node if found, otherwise NULL
 */

static avl_t *avl_find(avl_t *root, int value)
{
	while (root)
	{
		if (value == root->n)
			return (root);
		if (value < root->n)
			root = root->left;
		else
			root = root->right;
	}
	return (NULL);
}

/**
 * array_to_avl - Builds an AVL tree from an array
 * @array: pointer to first element of the array
 * @size: number of elements in the array
 *
 * Return: pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *array_to_avl(int *array, size_t size)
{
	avl_t *tree;
	avl_t *node;
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	tree = NULL;

	for (i = 0; i < size; i++)
	{
		if (avl_find(tree, array[i]) != NULL)
			continue;

		node = avl_insert(&tree, array[i]);
		if (node == NULL)
			return (NULL);
	}

	return (tree);
}
