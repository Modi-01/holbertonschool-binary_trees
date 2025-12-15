#include "binary_trees.h"

static size_t leftmost_leaf_depth(const binary_tree_t *tree);
static int is_perfect_recursive(const binary_tree_t *tree,
				size_t level, size_t leaf_depth);

/**
 * binary_tree_is_perfect - Checks if a binary tree is perfect
 * @tree: Pointer to the root node of the tree
 *
 * Return: 1 if perfect, otherwise 0
 */
int binary_tree_is_perfect(const binary_tree_t *tree)
{
	size_t leaf_depth;

	if (tree == NULL)
		return (0);

	leaf_depth = leftmost_leaf_depth(tree);
	return (is_perfect_recursive(tree, 0, leaf_depth));
}

/**
 * leftmost_leaf_depth - Gets depth of the leftmost leaf
 * @tree: Pointer to the root node
 *
 * Return: Depth of the leftmost leaf
 */
static size_t leftmost_leaf_depth(const binary_tree_t *tree)
{
	size_t depth = 0;

	while (tree && tree->left)
	{
		depth++;
		tree = tree->left;
	}
	return (depth);
}

/**
 * is_perfect_recursive - Checks if tree is perfect using recursion
 * @tree: Pointer to current node
 * @level: Current level (depth) of node
 * @leaf_depth: Expected depth for all leaves
 *
 * Return: 1 if perfect, otherwise 0
 */
static int is_perfect_recursive(const binary_tree_t *tree,
				size_t level, size_t leaf_depth)
{
	if (tree->left == NULL && tree->right == NULL)
		return (level == leaf_depth);

	if (tree->left == NULL || tree->right == NULL)
		return (0);

	return (is_perfect_recursive(tree->left, level + 1, leaf_depth) &&
		is_perfect_recursive(tree->right, level + 1, leaf_depth));
}
