#include "binary_trees.h"

/**
 * binary_tree_rotate_right - Performs a right-rotation on a binary tree
 * @tree: Pointer to the root node of the tree to rotate
 *
 * Return: Pointer to the new root node of the tree after rotation, or NULL
 */
binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
	binary_tree_t *pivot, *pivot_right, *parent;

	if (tree == NULL || tree->left == NULL)
		return (NULL);

	pivot = tree->left;
	pivot_right = pivot->right;
	parent = tree->parent;

	/* Rotation */
	pivot->right = tree;
	tree->parent = pivot;

	tree->left = pivot_right;
	if (pivot_right != NULL)
		pivot_right->parent = tree;

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
