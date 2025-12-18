#include "binary_trees.h"

/**
 * free_heap - Frees a binary heap (binary tree) recursively
 * @tree: Pointer to the root node of the heap to free
 */
static void free_heap(heap_t *tree)
{
	if (tree == NULL)
		return;

	free_heap(tree->left);
	free_heap(tree->right);
	free(tree);
}

/**
 * array_to_heap - Builds a Max Binary Heap tree from an array
 * @array: Pointer to the first element of the array to convert
 * @size: Number of elements in the array
 *
 * Return: Pointer to the root node of the created heap, or NULL on failure
 */
heap_t *array_to_heap(int *array, size_t size)
{
	heap_t *root;
	heap_t *node;
	size_t i;

	if (array == NULL || size == 0)
		return (NULL);

	root = NULL;

	for (i = 0; i < size; i++)
	{
		node = heap_insert(&root, array[i]);
		if (node == NULL)
		{
			free_heap(root);
			return (NULL);
		}
	}

	return (root);
}
