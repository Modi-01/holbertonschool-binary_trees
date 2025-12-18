#include "binary_trees.h"

static void avl_set_parent(avl_t *node, avl_t *parent)
{
	if (node)
		node->parent = parent;
}

static avl_t *avl_rebalance(avl_t *node)
{
	int bf;

	if (!node)
		return (NULL);

	bf = binary_tree_balance(node);

	if (bf > 1)
	{
		if (binary_tree_balance(node->left) < 0)
			node->left = binary_tree_rotate_left(node->left);
		node = binary_tree_rotate_right(node);
	}
	else if (bf < -1)
	{
		if (binary_tree_balance(node->right) > 0)
			node->right = binary_tree_rotate_right(node->right);
		node = binary_tree_rotate_left(node);
	}

	return (node);
}

static avl_t *avl_insert_rec(avl_t **root, avl_t *parent, int value,
			    avl_t **new_node)
{
	if (*root == NULL)
	{
		*root = (avl_t *)binary_tree_node(parent, value);
		*new_node = *root;
		return (*root);
	}

	if (value < (*root)->n)
	{
		(*root)->left = avl_insert_rec((avl_t **)&(*root)->left, *root,
					       value, new_node);
	}
	else if (value > (*root)->n)
	{
		(*root)->right = avl_insert_rec((avl_t **)&(*root)->right, *root,
						value, new_node);
	}
	else
	{
		*new_node = NULL;
		return (*root);
	}

	*root = avl_rebalance(*root);
	avl_set_parent(*root, parent);

	return (*root);
}

/**
 * avl_insert - Inserts a value in an AVL Tree
 * @tree: double pointer to the root node
 * @value: value to insert
 *
 * Return: pointer to the created node, or NULL on failure/duplicate
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node;

	if (tree == NULL)
		return (NULL);

	new_node = NULL;
	(void)avl_insert_rec(tree, NULL, value, &new_node);

	return (new_node);
}
