#include "binary_trees.h"
#include <stdlib.h>

static bst_t *min_value_node(bst_t *node);
static bst_t *remove_node(bst_t *root, bst_t *node);

/**
 * min_value_node - finds the minimum value node in a subtree
 * @node: subtree root
 *
 * Return: pointer to the minimum node
 */
static bst_t *min_value_node(bst_t *node)
{
	bst_t *current = node;

	if (current == NULL)
		return (NULL);

	while (current->left != NULL)
		current = current->left;

	return (current);
}

/**
 * remove_node - removes a specific node from BST and fixes links
 * @root: tree root (may change)
 * @node: node to remove
 *
 * Return: new root
 */
static bst_t *remove_node(bst_t *root, bst_t *node)
{
	bst_t *child = NULL;
	bst_t *parent = NULL;

	if (node == NULL)
		return (root);

	parent = node->parent;

	/* Case 1: node has no children */
	if (node->left == NULL && node->right == NULL)
	{
		if (parent == NULL)
		{
			free(node);
			return (NULL);
		}
		if (parent->left == node)
			parent->left = NULL;
		else
			parent->right = NULL;
		free(node);
		return (root);
	}

	/* Case 2: node has one child */
	if (node->left == NULL || node->right == NULL)
	{
		child = (node->left != NULL) ? node->left : node->right;

		if (parent == NULL)
		{
			child->parent = NULL;
			free(node);
			return (child);
		}

		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;

		child->parent = parent;
		free(node);
		return (root);
	}

	/* Case 3: node has two children -> replace with inorder successor */
	{
		bst_t *succ = min_value_node(node->right);

		node->n = succ->n;
		return (remove_node(root, succ));
	}
}

/**
 * bst_remove - removes a node from a Binary Search Tree
 * @root: pointer to the root node of the tree
 * @value: value to remove
 *
 * Return: new root node after removing, or original root if not found
 */
bst_t *bst_remove(bst_t *root, int value)
{
	bst_t *current = root;

	while (current != NULL)
	{
		if (value == current->n)
			return (remove_node(root, current));
		if (value < current->n)
			current = current->left;
		else
			current = current->right;
	}

	return (root);
}
