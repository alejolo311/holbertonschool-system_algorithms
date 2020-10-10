#include "rb_trees.h"

/**
* rb_tree_is_valid - verify if a tree is real black red
* @tree: the root
* Return: 1 in real black red 0 in other case
*/
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int black = 0;
	rb_tree_t *tmp = (rb_tree_t *) tree;

	if (tree == NULL || tree->color == RED)
		return (0);

	while (tmp != NULL)
	{
		if (tmp->color == BLACK)
			black++;
		tmp = tmp->left;
		if (tmp == NULL)
			black++;
	}
	if (CheckColors((rb_tree_t *) tree, 2, black, 0) == 0)
		return (0);
	return (1);
}
/**
* CheckColors - VERIFY EACH NODE COLOR
* @pColor: prevous color
* @b: black nodes
* @b_path:path of black
* @tree: the tree
* Return: 1 on success, 0 otherwise
*/
int CheckColors(rb_tree_t *tree, int pColor, int b,
	int b_path)
{
	int lnode = 0, rnode = 0;

	if (tree == NULL)
	{
		if (b == b_path + 1)
			return (1);
		return (0);
	}
	if ((tree->left != NULL && tree->n < tree->left->n) ||
		(tree->right != NULL && tree->n > tree->right->n))
		return (0);

	if ((tree->color != BLACK && tree->color != RED) ||
		(pColor == 1 && tree->color == RED))
		return (0);

	if (tree->color == BLACK)
	{
		lnode = CheckColors(tree->left, (tree->color == RED) ? 1 : 0,
			b, b_path + 1);
		if (lnode == 0)
			return (0);
		rnode = CheckColors(tree->right, (tree->color == RED) ? 1 : 0,
			b, b_path + 1);
		if (rnode == 0)
			return (0);
	}
	else
	{
		lnode = CheckColors(tree->left, (tree->color == RED) ? 1 : 0,
			b, b_path);
		if (lnode == 0)
			return (0);
		rnode = CheckColors(tree->right, (tree->color == RED) ? 1 : 0,
			b, b_path);
		if (rnode == 0)
			return (0);
	}
	return (1);
}
