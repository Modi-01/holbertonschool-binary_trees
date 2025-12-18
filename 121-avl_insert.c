#include "binary_trees.h"

/**
 * avl_insert_recursive - Insert a value in an AVL subtree (recursive)
 * @tree: Double pointer to the current subtree root
 * @parent: Parent node of the current subtree root
 * @value: Value to insert
 * @new_node: Address of pointer to store the newly created node
 *
 * Return: Pointer to the (possibly new) subtree root after rebalancing
 */
static avl_t *avl_insert_recursive(avl_t **tree, avl_t *parent, int value,
				  avl_t **new_node)
{
	int balance;

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		*new_node = (avl_t *)binary_tree_node(parent, value);
		*tree = *new_node;
		return (*tree);
	}

	if (value < (*tree)->n)
		(*tree)->left = avl_insert_recursive((avl_t **)&(*tree)->left,
						     *tree, value, new_node);
	else if (value > (*tree)->n)
		(*tree)->right = avl_insert_recursive((avl_t **)&(*tree)->right,
						      *tree, value, new_node);
	else
		return (*tree);

	if (*new_node == NULL)
		return (*tree);

	balance = binary_tree_balance((const binary_tree_t *)*tree);

	if (balance > 1 && value < (*tree)->left->n)
		*tree = (avl_t *)binary_tree_rotate_right((binary_tree_t *)*tree);
	else if (balance < -1 && value > (*tree)->right->n)
		*tree = (avl_t *)binary_tree_rotate_left((binary_tree_t *)*tree);
	else if (balance > 1 && value > (*tree)->left->n)
	{
		(*tree)->left = binary_tree_rotate_left((*tree)->left);
		*tree = (avl_t *)binary_tree_rotate_right((binary_tree_t *)*tree);
	}
	else if (balance < -1 && value < (*tree)->right->n)
	{
		(*tree)->right = binary_tree_rotate_right((*tree)->right);
		*tree = (avl_t *)binary_tree_rotate_left((binary_tree_t *)*tree);
	}

	(*tree)->parent = parent;
	return (*tree);
}

/**
 * avl_insert - Inserts a value in an AVL Tree
 * @tree: Double pointer to the root node of the AVL tree
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure/duplicate
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node = NULL;

	if (tree == NULL)
		return (NULL);

	avl_insert_recursive(tree, NULL, value, &new_node);

	return (new_node);
}
