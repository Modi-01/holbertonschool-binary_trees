#include "binary_trees.h"

/**
 * tree_size - Counts the number of nodes in a binary tree
 * @tree: Pointer to the root node
 *
 * Return: Number of nodes
 */
static size_t tree_size(const binary_tree_t *tree)
{
	if (!tree)
		return (0);

	return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * node_by_index - Gets the node at a given 1-based index in level-order
 * @root: Pointer to the root node
 * @idx: 1-based index (as in array representation)
 *
 * Return: Pointer to the node, or NULL on failure
 */
static heap_t *node_by_index(heap_t *root, size_t idx)
{
	size_t bit;
	heap_t *cur;

	if (!root || idx == 0)
		return (NULL);

	cur = root;
	for (bit = 1; bit <= idx; bit <<= 1)
		;

	bit >>= 2;

	while (cur && bit > 0)
	{
		if (idx & bit)
			cur = cur->right;
		else
			cur = cur->left;
		bit >>= 1;
	}

	return (cur);
}

/**
 * heapify_down - Restores Max Heap ordering starting from a node
 * @node: Pointer to the node to heapify from
 */
static void heapify_down(heap_t *node)
{
	heap_t *child;
	int tmp;

	while (node && (node->left || node->right))
	{
		if (!node->right)
			child = node->left;
		else if (!node->left)
			child = node->right;
		else
			child = (node->left->n >= node->right->n) ?
				node->left : node->right;

		if (!child || node->n >= child->n)
			break;

		tmp = node->n;
		node->n = child->n;
		child->n = tmp;

		node = child;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 * @root: Double pointer to the root node of the heap
 *
 * Return: Value stored in the root node, or 0 on failure
 */
int heap_extract(heap_t **root)
{
	size_t size;
	int value;
	heap_t *last, *parent;

	if (!root || !*root)
		return (0);

	value = (*root)->n;
	size = tree_size(*root);

	if (size == 1)
	{
		free(*root);
		*root = NULL;
		return (value);
	}

	last = node_by_index(*root, size);
	parent = node_by_index(*root, size / 2);

	if (!last || !parent)
		return (0);

	(*root)->n = last->n;

	if (parent->left == last)
		parent->left = NULL;
	else
		parent->right = NULL;

	free(last);

	heapify_down(*root);

	return (value);
}
