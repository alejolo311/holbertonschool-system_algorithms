#include "rb_trees.h"

/**
 * rb_tree_insert - insert a new value
 * @tree: the tree
 * @value: the new value
 * Return: a pointer of the new node
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *new = NULL, *root = NULL;

	if (*tree == NULL)
		return (*tree = rb_tree_node(NULL, value, BLACK));

	new = insert_r(*tree, value);
	if (new == NULL)
		return (NULL);

	fix_tree(new);

	root = new;
	while (GetP(root) != NULL)
		root = GetP(root);
	*tree = root;
	return (new);
}
/**
 * insert_r - insert recursive
 * @root: root
 * @value: value
 * Return: a pointer inserted
 */
rb_tree_t *insert_r(rb_tree_t *root, int value)
{
	rb_tree_t *new = NULL;

	if (root)
	{
		if (value < root->n)
		{
			if (root->left != NULL)
				return (insert_r(root->left, value));

			new = rb_tree_node(root, value, RED);
			if (new == NULL)
				return (NULL);
			root->left = new;
		}
		else if (value > root->n)
		{
			if (root->right != NULL)
				return (insert_r(root->right, value));

			new = rb_tree_node(root, value, RED);
			if (new == NULL)
				return (NULL);
			root->right = new;
		}
		else
			return (NULL);
	}
	return (new);
}
/**
 * rotate - ROTATE
 * @node: the node
 * @sense: sense
 * Return: nothing
 */
void rotate(rb_tree_t *node, int sense)
{
	rb_tree_t  *parent = GetP(node), *rNew = NULL;

	rNew = sense ? node->left : node->right;
	if (sense != 0)
	{
		node->left = rNew->right;
		rNew->right = node;
		node->parent = rNew;
		node->left != NULL ? node->left->parent = node : 0;
		if (parent != NULL)
		{
			if (node == parent->left)
				parent->left = rNew;
			else if (node == parent->right)
				parent->right = rNew;
		}
	}
	else
	{
		node->right = rNew->left;
		rNew->left = node;
		node->parent = rNew;
		if (node->right)
			node->right->parent = node;
		if (parent)
		{
			if (node == parent->left)
				parent->left = rNew;
			else if (node == parent->right)
				parent->right = rNew;
		}
	}
	rNew->parent = parent;
}

/**
 * fix_tree - make back a RB Tree
 * @node:fixing
 * Return: Nothing
 */
void fix_tree(rb_tree_t *node)
{
	rb_tree_t *p = NULL, *Gp = NULL;

	if (GetP(node) == NULL)
		node->color = BLACK;
	else if (GetP(node)->color == BLACK)
		return;
	else if (GetU(node) && (GetU(node))->color == RED)
	{
		GetP(node)->color = BLACK, GetU(node)->color = BLACK;
		GetGP(node)->color = RED, fix_tree(GetGP(node));
	}
	else
	{
		p = GetP(node), Gp = GetGP(node);
		if (node == p->right && p == Gp->left)
			rotate(p, 0), node = node->left;
		else if (node == p->left && p == Gp->right)
			rotate(p, 1), node = node->right;
		p = GetP(node), Gp = GetGP(node);
		if (node == p->left)
			rotate(Gp, 1);
		else
			rotate(Gp, 0);
		p->color = BLACK, Gp->color = RED;
	}
}
