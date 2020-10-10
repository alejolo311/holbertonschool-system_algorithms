#include "rb_trees.h"
/**
 * rb_tree_remove - remove froma tree
 * @root: root
 * @n: the new value
 * Return: the new node or null
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	rb_tree_t *new = NULL, *nf = NULL;

	if (root == NULL)
		return (root);
	nf = sValue(root, n);
	if (nf == NULL)
		return (root);
	new = delete(nf);
	if (new == NULL)
		return (NULL);
	while (GetP(new))
		new = GetP(new);
	return (new);
}
/**
 * _succesor - select the node that replace the deleted node
 * @node: node
 * Return: succesor
 */
rb_tree_t *_succesor(rb_tree_t *node)
{
	rb_tree_t *tmp = NULL;

	if (node->left && node->right)
	{
		tmp = node->right;
		while (tmp->left)
			tmp = tmp->left;
		return (tmp);
	}

	if (!node->left && !node->right)
		return (NULL);
	if (node->left)
		return (node->left);
	else
		return (node->right);
}

/**
 * sValue - search a number
 * @root: root
 * @n: number
 * Return: the fund node
 */
rb_tree_t *sValue(rb_tree_t *root, int n)
{
	rb_tree_t *find = NULL;

	if (root == NULL)
		return (NULL);

	if (n < root->n)
		find = sValue(root->left, n);
	else if (n > root->n)
		find = sValue(root->right, n);
	else
		return (root);

	return (find);
}

/**
 * move_black - move black nodes
 * @node: node to fix
 * Return: void
 */
void move_black(rb_tree_t *node)
{
	rb_tree_t  *p = node->parent, *deleted = GetS(node);

	if (GetP(node) == NULL)
		return;
	if (deleted == NULL)
		move_black(p);
	else
	{
		if (deleted->color == RED)
		{
			p->color = RED, deleted->color = BLACK;
			if (deleted->parent->left == deleted)
				rotate(p, 1);
			else
				rotate(p, 0);
			move_black(node);
		}
		else
		{
			if (moveRed(deleted))
				move_red(deleted, p);
			else
			{
				deleted->color = RED;
				if (p->color == BLACK)
					move_black(p);
				else
					p->color = BLACK;
			}
		}
	}
}
/**
 * move_red - fix when is necessary move red node
 * @deleted: deleted node's deleted
 * @p: deleted node's p
 * Return: nothing
 */
void move_red(rb_tree_t *deleted, rb_tree_t *p)
{
	if (deleted->left && deleted->left->color == RED)
	{
		if (deleted->parent->left == deleted)
		{
			deleted->left->color = deleted->color;
			deleted->color = p->color;
			rotate(p, 1);
		}
		else
		{
			deleted->left->color = p->color;
			rotate(deleted, 1);
			rotate(p, 0);
		}
	}
	else
	{
		if (deleted->parent->left == deleted)
		{
			deleted->right->color = p->color;
			rotate(deleted, 0);
			rotate(p, 1);
		}
		else
		{
			deleted->right->color = deleted->color;
			deleted->color = p->color;
			rotate(p, 0);
		}
	}
	p->color = BLACK;
}


/**
 * delete - delete a node of a RED-BLACK tree
 * @node: node to delete
 * Return: a pointer of the tree for letting search the new root, NULL otherw
 */
rb_tree_t *delete(rb_tree_t *node)
{
	rb_tree_t *succesor = _succesor(node), *parent = GetP(node);
	int double_black = moveBlack(node, succesor), temp = 0;

	if (!succesor)
	{
		if (parent)
		{
			if (double_black)
				move_black(node);
			else if (GetS(node))
				GetS(node)->color = RED;
			if (parent->left == node)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		free(node);
		return (parent ? parent : NULL);
	} else if (!node->left || !node->right)
	{
		if (!GetP(node))
		{
			node->n = succesor->n, node->left = node->right = NULL;
			free(succesor);
			return (node);
		}
		if (node->parent->left == node)
			parent->left = succesor;
		else
			parent->right = succesor;
		free(node);
		succesor->parent = parent;
		if (double_black)
			move_black(succesor);
		else
			succesor->color = BLACK;
		return (succesor);
	}
	temp = node->n, node->n = succesor->n, succesor->n = temp;
	return (delete(succesor));
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
