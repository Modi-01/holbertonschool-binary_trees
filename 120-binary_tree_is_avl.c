#include "binary_trees.h"
#include <limits.h>

/**
 * height_avl - measures height of a binary tree
 * @tree: pointer to node
 *
 * Return: height
 */
static int height_avl(const binary_tree_t *tree)
{
	int left, right;

	if (tree == NULL)
		return (0);

	left = height_avl(tree->left);
	right = height_avl(tree->right);

	return ((left > right ? left : right) + 1);
}

/**
 * abs_int - absolute value
 * @n: integer
 *
 * Return: absolute value of n
 */
static int abs_int(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/**
 * is_bst_avl - checks if tree is a valid BST (no duplicates)
 * @tree: pointer to node
 * @min: min boundary (exclusive)
 * @max: max boundary (exclusive)
 *
 * Return: 1 if BST, otherwise 0
 */
static int is_bst_avl(const binary_tree_t *tree, long min, long max)
{
	if (tree == NULL)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);

	return (is_bst_avl(tree->left, min, tree->n) &&
		is_bst_avl(tree->right, tree->n, max));
}

/**
 * is_avl_balanced - checks AVL balance property recursively
 * @tree: pointer to node
 *
 * Return: 1 if balanced, otherwise 0
 */
static int is_avl_balanced(const binary_tree_t *tree)
{
	int lh, rh;

	if (tree == NULL)
		return (1);

	lh = height_avl(tree->left);
	rh = height_avl(tree->right);

	if (abs_int(lh - rh) > 1)
		return (0);

	return (is_avl_balanced(tree->left) &&
		is_avl_balanced(tree->right));
}

/**
 * binary_tree_is_avl - checks if a binary tree is a valid AVL tree
 * @tree: pointer to the root node
 *
 * Return: 1 if AVL, otherwise 0
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);

	if (!is_bst_avl(tree, LONG_MIN, LONG_MAX))
		return (0);

	if (!is_avl_balanced(tree))
		return (0);

	return (1);
}
