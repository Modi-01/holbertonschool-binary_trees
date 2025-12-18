#include "binary_trees.h"

static avl_t *avl_rebalance_node(avl_t *node);
static avl_t *avl_insert_rec(avl_t *root, avl_t *parent, int value,
	int *inserted, avl_t **created);

/**
 * avl_insert - Inserts a value in an AVL Tree
 * @tree: Double pointer to the root node of the AVL tree
 * @value: Value to insert
 *
 * Return: Pointer to the created node, or NULL on failure/duplicate
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	int inserted;
	avl_t *created;

	if (!tree)
		return (NULL);

	inserted = 0;
	created = NULL;

	*tree = avl_insert_rec(*tree, NULL, value, &inserted, &created);

	if (!inserted)
		return (NULL);

	return (created);
}

/**
 * avl_insert_rec - Recursively insert then rebalance a subtree
 * @root: Current subtree root
 * @parent: Parent of current subtree root
 * @value: Value to insert
 * @inserted: Set to 1 if a new node was created
 * @created: Output pointer to the created node
 *
 * Return: New subtree root after rebalancing
 */
static avl_t *avl_insert_rec(avl_t *root, avl_t *parent, int value,
	int *inserted, avl_t **created)
{
	if (!root)
	{
		*created = binary_tree_node(parent, value);
		if (!*created)
			return (NULL);
		*inserted = 1;
		return (*created);
	}

	if (value < root->n)
	{
		root->left = avl_insert_rec(root->left, root, value, inserted, created);
		if (root->left)
			root->left->parent = root;
	}
	else if (value > root->n)
	{
		root->right = avl_insert_rec(root->right, root, value, inserted, created);
		if (root->right)
			root->right->parent = root;
	}
	else
	{
		*inserted = 0;
		*created = NULL;
		return (root);
	}

	return (avl_rebalance_node(root));
}

/**
 * avl_rebalance_node - Rebalance an AVL node if needed
 * @node: Pointer to the node to rebalance
 *
 * Return: New root of the subtree after rotation(s)
 */
static avl_t *avl_rebalance_node(avl_t *node)
{
	int balance;
	avl_t *parent, *new_root;

	if (!node)
		return (NULL);

	parent = node->parent;
	balance = binary_tree_balance(node);
	new_root = node;

	if (balance > 1)
	{
		if (binary_tree_balance(node->left) < 0)
		{
			node->left = binary_tree_rotate_left(node->left);
			if (node->left)
				node->left->parent = node;
		}
		new_root = binary_tree_rotate_right(node);
	}
	else if (balance < -1)
	{
		if (binary_tree_balance(node->right) > 0)
		{
			node->right = binary_tree_rotate_right(node->right);
			if (node->right)
				node->right->parent = node;
		}
		new_root = binary_tree_rotate_left(node);
	}

	if (new_root)
		new_root->parent = parent;

	return (new_root);
}
