#include "binary_trees.h"
#include <limits.h>

/**
 * is_bst - checks if a binary tree is a valid BST
 * @tree: pointer to the current node
 * @min: minimum allowed value
 * @max: maximum allowed value
 *
 * Return: 1 if valid BST, 0 otherwise
 */
int is_bst(const binary_tree_t *tree, int min, int max)
{
	if (tree == NULL)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst(tree->left, min, tree->n) &&
		is_bst(tree->right, tree->n, max));
}

/**
 * binary_tree_is_bst - checks if a binary tree is a valid BST
 * @tree: pointer to the root node
 *
 * Return: 1 if valid BST, otherwise 0
 */
int binary_tree_is_bst(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return (is_bst(tree, INT_MIN, INT_MAX));
}
