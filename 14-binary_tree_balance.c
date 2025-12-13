#include "binary_trees.h"

/**
 * height_edges - Measures height of a binary tree in terms of edges
 * @tree: Pointer to the root node
 *
 * Return: Height in edges, or 0 if tree is NULL
 */
static size_t height_edges(const binary_tree_t *tree)
{
	size_t left_h = 0, right_h = 0;

	if (tree == NULL)
		return (0);

	if (tree->left != NULL)
		left_h = 1 + height_edges(tree->left);

	if (tree->right != NULL)
		right_h = 1 + height_edges(tree->right);

	return (left_h > right_h ? left_h : right_h);
}

/**
 * binary_tree_balance - Measures the balance factor of a binary tree
 * @tree: Pointer to the root node of the tree to measure the balance factor
 *
 * Return: Balance factor, or 0 if tree is NULL
 */
int binary_tree_balance(const binary_tree_t *tree)
{
	int left_h, right_h;

	if (tree == NULL)
		return (0);

	left_h = (int)height_edges(tree->left);
	right_h = (int)height_edges(tree->right);

	return (left_h - right_h);
}
