#include "binary_trees.h"

/**
 * height_nodes - Measures height of a binary tree in terms of nodes
 * @tree: Pointer to the root node
 *
 * Return: Height in nodes, 0 if tree is NULL
 */
static size_t height_nodes(const binary_tree_t *tree)
{
	size_t left_h, right_h;

	if (tree == NULL)
		return (0);

	left_h = height_nodes(tree->left);
	right_h = height_nodes(tree->right);

	return (1 + (left_h > right_h ? left_h : right_h));
}

/**
 * binary_tree_balance - Measures the balance factor of a binary tree
 * @tree: Pointer to the root node of the tree to measure the balance factor
 *
 * Return: Balance factor, or 0 if tree is NULL
 */
int binary_tree_balance(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	return ((int)height_nodes(tree->left) - (int)height_nodes(tree->right));
}
