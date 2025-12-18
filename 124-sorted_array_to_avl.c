#include "binary_trees.h"

/**
 * build_avl - Builds an AVL tree from a sorted array (recursive helper)
 * @parent: Parent node of the subtree to create
 * @array: Pointer to the first element of the array
 * @start: Start index (inclusive)
 * @end: End index (inclusive)
 *
 * Return: Pointer to the root of the created subtree, or NULL on failure
 */
static avl_t *build_avl(avl_t *parent, int *array, int start, int end)
{
	avl_t *node;
	int mid;

	if (start > end)
		return (NULL);

	mid = start + (end - start) / 2;

	node = binary_tree_node(parent, array[mid]);
	if (!node)
		return (NULL);

	node->left = build_avl(node, array, start, mid - 1);
	node->right = build_avl(node, array, mid + 1, end);

	return (node);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array
 * @array: Pointer to the first element of the array
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || size == 0)
		return (NULL);

	return (build_avl(NULL, array, 0, (int)size - 1));
}
