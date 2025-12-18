#include "binary_trees.h"

/**
 * build_avl_from_sorted - Builds an AVL tree from a sorted array slice
 * @array: Pointer to the first element of the sorted array
 * @start: Start index (inclusive)
 * @end: End index (inclusive)
 * @parent: Parent node of the created subtree
 *
 * Return: Pointer to the root of the created subtree, or NULL on failure
 */
static avl_t *build_avl_from_sorted(int *array, int start, int end, avl_t *parent)
{
	int mid;
	avl_t *node;

	if (!array || start > end)
		return (NULL);

	mid = start + (end - start) / 2;

	node = binary_tree_node(parent, array[mid]);
	if (!node)
		return (NULL);

	node->left = build_avl_from_sorted(array, start, mid - 1, node);
	node->right = build_avl_from_sorted(array, mid + 1, end, node);

	return (node);
}

/**
 * sorted_array_to_avl - Builds an AVL tree from a sorted array (no rotations)
 * @array: Pointer to the first element of the array to be converted
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created AVL tree, or NULL on failure
 */
avl_t *sorted_array_to_avl(int *array, size_t size)
{
	if (!array || size == 0)
		return (NULL);

	return (build_avl_from_sorted(array, 0, (int)size - 1, NULL));
}
