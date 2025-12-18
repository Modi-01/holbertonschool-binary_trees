#include "binary_trees.h"

/**
 * heap_size - Counts the number of nodes in a binary tree
 * @tree: Pointer to the root node of the tree to count
 *
 * Return: Number of nodes
 */
static size_t heap_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (1 + heap_size(tree->left) + heap_size(tree->right));
}

/**
 * is_complete - Checks if a binary tree is complete using array indexing
 * @tree: Pointer to the root node of the tree to check
 * @index: Index of the current node (as if stored in an array)
 * @size: Total number of nodes in the tree
 *
 * Return: 1 if complete, 0 otherwise
 */
static int is_complete(const binary_tree_t *tree, size_t index, size_t size)
{
	if (tree == NULL)
		return (1);

	if (index >= size)
		return (0);

	return (is_complete(tree->left, index * 2 + 1, size) &&
		is_complete(tree->right, index * 2 + 2, size));
}

/**
 * is_max_heap - Checks if a binary tree satisfies the Max-Heap property
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if valid Max-Heap property, 0 otherwise
 */
static int is_max_heap(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (1);

	if (tree->left && tree->n < tree->left->n)
		return (0);

	if (tree->right && tree->n < tree->right->n)
		return (0);

	return (is_max_heap(tree->left) && is_max_heap(tree->right));
}

/**
 * binary_tree_is_heap - Checks if a binary tree is a valid Max Binary Heap
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if tree is a valid Max Binary Heap, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	size_t size;

	if (tree == NULL)
		return (0);

	size = heap_size(tree);

	if (!is_complete(tree, 0, size))
		return (0);

	return (is_max_heap(tree));
}
