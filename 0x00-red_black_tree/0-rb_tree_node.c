#include "rb_trees.h"
/**
* rb_tree_node - CREATE A NEW NODE
* @parent: the parent
* @value: the value of the new node
* @color: the color of the node
* Return: a new node in fail return null
*/
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *new = NULL;

	new = malloc(sizeof(rb_tree_t));
	if (new == NULL)
		return (NULL);

	new->parent = parent;
	new->n = value;
	new->color = color;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
