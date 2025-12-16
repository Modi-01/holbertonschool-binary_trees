#include "binary_trees.h"

/**
 * print_level - prints nodes at a given level
 * @tree: pointer to the tree
 * @func: function to print node value
 * @level: current level
 */
void print_level(const binary_tree_t *tree, void (*func)(int), size_t level)
{
	if (tree == NULL)
		return;

	if (level == 0)
		func(tree->n);
	else
	{
		print_level(tree->left, func, level - 1);
		print_level(tree->right, func, level - 1);
	}
}

/**
 * binary_tree_levelorder - traverses a binary tree using level-order
 * @tree: pointer to the root node
 * @func: function to call for each node
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	size_t height, i;

	if (tree == NULL || func == NULL)
		return;

	height = binary_tree_height(tree);

	for (i = 0; i <= height; i++)
		print_level(tree, func, i);
}
