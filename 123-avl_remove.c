#include "binary_trees.h"
#include <stdlib.h>

static avl_t *min_node(avl_t *node)
{
	while (node && node->left)
		node = node->left;
	return (node);
}

static void link_parent(avl_t **root, avl_t *parent, avl_t *old, avl_t *newn)
{
	if (!parent)
		*root = newn;
	else if (parent->left == old)
		parent->left = newn;
	else
		parent->right = newn;

	if (newn)
		newn->parent = parent;
}

static void rebalance_at(avl_t **root, avl_t *node)
{
	int bal, child_bal;
	avl_t *parent, *newn;

	if (!node)
		return;

	parent = node->parent;
	bal = binary_tree_balance(node);

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
	else
		return;

	link_parent(root, parent, node, newn);
}

static void rebalance_up(avl_t **root, avl_t *from)
{
	avl_t *cur, *next;

	cur = from;
	while (cur)
	{
		next = cur->parent;
		rebalance_at(root, cur);
		if (next && next->parent)
			cur = next->parent;
		else
			cur = next;
	}
}

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

static avl_t *remove_one(avl_t **root, avl_t *node)
{
	avl_t *child, *parent;

	child = node->left ? node->left : node->right;
	parent = node->parent;

	if (child)
		child->parent = parent;

	if (!parent)
		*root = child;
	else if (parent->left == node)
		parent->left = child;
	else
		parent->right = child;

	free(node);
	return (parent);
}

/**
 * avl_remove - removes a node from an AVL tree
 * @root: pointer to root node
 * @value: value to remove
 *
 * Return: new root after removal/rebalancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	avl_t *node, *succ, *start;

	node = find_node(root, value);
	if (!node)
		return (root);

	if (node->left && node->right)
	{
		succ = min_node(node->right);
		node->n = succ->n;
		node = succ;
	}

	start = remove_one(&root, node);
	rebalance_up(&root, start);

	return (root);
}
