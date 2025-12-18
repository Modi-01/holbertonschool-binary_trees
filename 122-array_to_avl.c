#include "binary_trees.h"

static avl_t *avl_find(avl_t *tree, int value);

/**
 * array_to_avl - Builds an AVL tree from an array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *array_to_avl(int *array, size_t size)
{
	size_t i;
	avl_t *root;

	if (!array || size == 0)
		return (NULL);

	root = NULL;

	for (i = 0; i < size; i++)
	{
		if (avl_find(root, array[i]))
			continue;
		if (!avl_insert(&root, array[i]))
		{
			binary_tree_delete(root);
			return (NULL);
		}
	}

	return (root);
}

/**
 * avl_find - Searches for a value in an AVL tree
 * @tree: Pointer to the root node
 * @value: Value to search for
 *
 * Return: Pointer to the node if found, otherwise NULL
 */
static avl_t *avl_find(avl_t *tree, int value)
{
	while (tree)
	{
		if (value < tree->n)
			tree = tree->left;
		else if (value > tree->n)
			tree = tree->right;
		else
			return (tree);
	}

	return (NULL);
}
