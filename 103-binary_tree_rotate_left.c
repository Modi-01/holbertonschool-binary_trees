#include "binary_trees.h"

/**
 * binary_tree_rotate_left - Performs a left-rotation on a binary tree
 * @tree: Pointer to the root node of the tree to rotate
 *
 * Return: Pointer to the new root node of the tree after rotation, or NULL
 */
binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)
{
	binary_tree_t *pivot, *pivot_left, *parent;

	if (tree == NULL || tree->right == NULL)
		return (NULL);

	pivot = tree->right;
	pivot_left = pivot->left;
	parent = tree->parent;

	/* Rotation */
	pivot->left = tree;
	tree->parent = pivot;

	tree->right = pivot_left;
	if (pivot_left != NULL)
		pivot_left->parent = tree;

	/* Re-attach to parent */
	pivot->parent = parent;
	if (parent != NULL)
	{
		if (parent->left == tree)
			parent->left = pivot;
		else
			parent->right = pivot;
	}

	return (pivot);
}
