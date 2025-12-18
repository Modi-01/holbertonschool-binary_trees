#include "binary_trees.h"

/**
 * tree_size - Computes the size of a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Size of the tree
 */
static size_t tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * heap_to_sorted_array - Converts a Max Binary Heap to a sorted array
 * @heap: Pointer to the root node of the heap to convert
 * @size: Address to store the size of the array
 *
 * Return: Pointer to the created array, or NULL on failure
 */
int *heap_to_sorted_array(heap_t *heap, size_t *size)
{
	size_t i, n;
	int *array;

	if (!size)
		return (NULL);

	*size = 0;

	if (!heap)
		return (NULL);

	n = tree_size(heap);
	array = malloc(sizeof(int) * n);
	if (!array)
		return (NULL);

	for (i = 0; i < n; i++)
		array[i] = heap_extract(&heap);

	*size = n;

	return (array);
}
