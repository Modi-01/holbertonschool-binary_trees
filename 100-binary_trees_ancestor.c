#include "binary_trees.h"

/**
 * binary_trees_ancestor - finds the lowest common ancestor of two nodes
 * @first: pointer to the first node
 * @second: pointer to the second node
 *
 * Return: pointer to the lowest common ancestor node, or NULL
 */
binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,
		const binary_tree_t *second)
{
	const binary_tree_t *a;
	const binary_tree_t *b;

	if (first == NULL || second == NULL)
		return (NULL);

	a = first;
	while (a != NULL)
	{
		b = second;
		while (b != NULL)
		{
			if (a == b)
				return ((binary_tree_t *)a);
			b = b->parent;
		}
		a = a->parent;
	}

	return (NULL);
}
