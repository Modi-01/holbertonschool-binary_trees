#include "binary_trees.h"

static int avl_contains(const avl_t *tree, int value);
static void rebalance_from(avl_t **tree, avl_t *node);
static void update_root_if_needed(avl_t **tree, avl_t *subroot);

/**
 * avl_insert - Inserts a value in an AVL Tree
 * @tree: Double pointer to the root node of the AVL tree
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure / duplicate
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node, *parent, *cur;

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		*tree = binary_tree_node(NULL, value);
		return (*tree);
	}

	if (avl_contains(*tree, value))
		return (NULL);

	parent = NULL;
	cur = *tree;

	while (cur != NULL)
	{
		parent = cur;
		if (value < cur->n)
			cur = cur->left;
		else
			cur = cur->right;
	}

	new_node = binary_tree_node(parent, value);
	if (new_node == NULL)
		return (NULL);

	if (value < parent->n)
		parent->left = new_node;
	else
		parent->right = new_node;

	rebalance_from(tree, parent);
	return (new_node);
}

/**
 * avl_contains - Checks if a value exists in an AVL/BST
 * @tree: Root pointer
 * @value: Value to find
 *
 * Return: 1 if found, 0 otherwise
 */
static int avl_contains(const avl_t *tree, int value)
{
	while (tree != NULL)
	{
		if (value < tree->n)
			tree = tree->left;
		else if (value > tree->n)
			tree = tree->right;
		else
			return (1);
	}
	return (0);
}

/**
 * rebalance_from - Rebalances AVL walking upwards from a node
 * @tree: Address of root pointer
 * @node: Start node (typically parent of inserted node)
 */
static void rebalance_from(avl_t **tree, avl_t *node)
{
	int bf;

	while (node != NULL)
	{
		bf = binary_tree_balance(node);

		if (bf > 1)
		{
			if (binary_tree_balance(node->left) < 0)
				binary_tree_rotate_left(node->left);
			node = binary_tree_rotate_right(node);
			update_root_if_needed(tree, node);
		}
		else if (bf < -1)
		{
			if (binary_tree_balance(node->right) > 0)
				binary_tree_rotate_right(node->right);
			node = binary_tree_rotate_left(node);
			update_root_if_needed(tree, node);
		}

		node = node->parent;
	}
}

/**
 * update_root_if_needed - Ensures *tree points to the real root after rotations
 * @tree: Address of root pointer
 * @subroot: A node returned by rotation (subtree root)
 */
static void update_root_if_needed(avl_t **tree, avl_t *subroot)
{
	(void)subroot;

	while ((*tree)->parent != NULL)
		*tree = (*tree)->parent;
}
