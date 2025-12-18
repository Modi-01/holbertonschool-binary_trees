#include "binary_trees.h"

/**
 * avl_rebalance - Rebalance an AVL node after insertion
 * @node: Pointer to node to rebalance
 * @value: Inserted value (used to detect the case)
 *
 * Return: New root of the (sub)tree after rotations
 */
static avl_t *avl_rebalance(avl_t *node, int value)
{
	int balance;

	if (!node)
		return (NULL);

	balance = binary_tree_balance((const binary_tree_t *)node);

	if (balance > 1 && node->left && value < node->left->n)
		return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)node));

	if (balance < -1 && node->right && value > node->right->n)
		return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)node));

	if (balance > 1 && node->left && value > node->left->n)
	{
		node->left = binary_tree_rotate_left(node->left);
		return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)node));
	}

	if (balance < -1 && node->right && value < node->right->n)
	{
		node->right = binary_tree_rotate_right(node->right);
		return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)node));
	}

	return (node);
}

/**
 * avl_insert_bst - Insert a value like BST and rebalance on the way up
 * @node: Current subtree root
 * @parent: Parent of current subtree root
 * @value: Value to insert
 * @new_node: Address to store pointer to created node
 *
 * Return: New subtree root after insertion/rebalancing
 */
static avl_t *avl_insert_bst(avl_t *node, avl_t *parent, int value,
			     avl_t **new_node)
{
	if (node == NULL)
	{
		*new_node = (avl_t *)binary_tree_node(parent, value);
		return (*new_node);
	}

	if (value < node->n)
		node->left = avl_insert_bst((avl_t *)node->left, node, value,
					    new_node);
	else if (value > node->n)
		node->right = avl_insert_bst((avl_t *)node->right, node, value,
					     new_node);
	else
		return (node);

	node = avl_rebalance(node, value);
	node->parent = parent;

	return (node);
}

/**
 * avl_insert - Inserts a value in an AVL Tree
 * @tree: Double pointer to root node of the AVL tree
 * @value: Value to insert
 *
 * Return: Pointer to created node, or NULL on failure/duplicate
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node = NULL;

	if (tree == NULL)
		return (NULL);

	*tree = avl_insert_bst(*tree, NULL, value, &new_node);

	return (new_node);
}
