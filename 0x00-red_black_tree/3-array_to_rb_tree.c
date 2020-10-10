#include "rb_trees.h"

/**
 * array_to_rb_tree - array to tree
 * @array: the array to transform
 * @size: the size og the array
 * Return: a node the root
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	rb_tree_t *node = NULL;
	unsigned int j = 0, i = 0, s = 0;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (array[i] == array[j])
			{
				s = 1;
				break;
			}
		}

		if (s)
			s = 0;
		else if (rb_tree_insert(&node, array[i]) == NULL)
			return (NULL);
	}

	return (node);
}
