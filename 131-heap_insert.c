#include "binary_trees.h"

/**
 * heap_size - Counts nodes in a binary tree
 * @tree: Pointer to root node
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
 * node_at_index - Gets node at a given 1-based index in a complete binary tree
 * @root: Root of the tree
 * @idx: 1-based index (like array representation)
 *
 * Return: Pointer to the node, or NULL on failure
 */
static heap_t *node_at_index(heap_t *root, size_t idx)
{
	size_t bit, msb;
	heap_t *node;

	if (root == NULL || idx == 0)
		return (NULL);

	node = root;
	msb = 1;
	while (msb <= idx)
		msb <<= 1;
	msb >>= 1;

	for (bit = msb >> 1; bit > 0 && node; bit >>= 1)
	{
		if (idx & bit)
			node = node->right;
		else
			node = node->left;
	}
	return (node);
}

/**
 * heap_insert - Inserts a value in a Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the new node
 *
 * Return: Pointer to the node containing @value after reheapify, or NULL
 */
heap_t *heap_insert(heap_t **root, int value)
{
	size_t size, idx, parent_idx;
	heap_t *parent, *node;
	int tmp;

	if (root == NULL)
		return (NULL);

	if (*root == NULL)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	size = heap_size(*root);
	idx = size + 1;
	parent_idx = idx / 2;

	parent = node_at_index(*root, parent_idx);
	if (parent == NULL)
		return (NULL);

	node = binary_tree_node(parent, value);
	if (node == NULL)
		return (NULL);

	if ((idx % 2) == 0)
		parent->left = node;
	else
		parent->right = node;

	while (node->parent && node->n > node->parent->n)
	{
		tmp = node->n;
		node->n = node->parent->n;
		node->parent->n = tmp;
		node = node->parent;
	}

	return (node);
}
