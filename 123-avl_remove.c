#include "binary_trees.h"
#include <stdlib.h>

/**
 * min_node - finds the minimum node in a subtree
 * @node: root of the subtree
 *
 * Return: pointer to the minimum node, or NULL
 */
static avl_t *min_node(avl_t *node)
{
	while (node && node->left)
		node = node->left;
	return (node);
}

/**
 * find_node - searches for a value in a BST/AVL tree
 * @root: pointer to the root node
 * @value: value to find
 *
 * Return: pointer to the node containing value, or NULL
 */
static avl_t *find_node(avl_t *root, int value)
{
	while (root)
	{
		if (value == root->n)
			return (root);
		if (value < root->n)
			root = root->left;
		else
			root = root->right;
	}
	return (NULL);
}

/**
 * rebalance_up - rebalances an AVL tree from a node up to the root
 * @root: address of the root pointer
 * @node: start node (usually parent of deleted node)
 */
static void rebalance_up(avl_t **root, avl_t *node)
{
	int bal, child_bal;
	avl_t *parent, *newn;

	while (node)
	{
		parent = node->parent;
		bal = binary_tree_balance(node);
		newn = NULL;

		if (bal > 1)
		{
			child_bal = binary_tree_balance(node->left);
			if (child_bal < 0)
				node->left = binary_tree_rotate_left(node->left);
			newn = binary_tree_rotate_right(node);
		}
		else if (bal < -1)
		{
			child_bal = binary_tree_balance(node->right);
			if (child_bal > 0)
				node->right = binary_tree_rotate_right(node->right);
			newn = binary_tree_rotate_left(node);
		}

		if (newn)
		{
			if (!parent)
				*root = newn;
			else if (parent->left == node)
				parent->left = newn;
			else
				parent->right = newn;
			newn->parent = parent;
		}

		node = parent;
	}
}

/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to the root node of the tree
 * @value: value to remove in the tree
 *
 * Return: pointer to the new root node of the tree after removing the desired
 * value, and after rebalancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *node, *succ, *child, *parent;

	node = find_node(root, value);
	if (!node)
		return (root);

	if (node->left && node->right)
	{
		succ = min_node(node->right);
		node->n = succ->n;
		node = succ;
	}

	child = node->left ? node->left : node->right;
	parent = node->parent;

	if (child)
		child->parent = parent;

	if (!parent)
		root = child;
	else if (parent->left == node)
		parent->left = child;
	else
		parent->right = child;

	free(node);
	rebalance_up(&root, parent);

	return (root);
}
