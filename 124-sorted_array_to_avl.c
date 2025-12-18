#include "binary_trees.h"

/**
 * build_avl - Builds an AVL tree from a sorted array (recursive helper)
 * @array: Pointer to the first element of the array
 * @start: Start index
 * @end: End index (inclusive)
 * @parent: Parent node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
static avl_t *build_avl(int *array, size_t start, size_t end, avl_t *parent)
{
	size_t mid;
	avl_t *node;

	if (!array || start > end)
		return (NULL);

	mid = start + (end - start) / 2;

	node = binary_tree_node(parent, array[mid]);
	if (!node)
		return (NULL);

	if (mid > start)
		node->left = build_avl(array, start, mid - 1, node);
	if (mid < end)
		node->right = build_avl(array, mid + 1, end, node);

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

	return (build_avl(array, 0, size - 1, NULL));
}
