#include <stdio.h>
#include <stdlib.h>
#include "type.h"

struct binary_node {
	int data;
	struct binary_node *left;
	struct binary_node *right;	
};

typedef struct binary_node btnode;

btnode *btnode_new(int val)
{
	btnode *tmp;

	tmp = malloc(sizeof(btnode));

	tmp->left = tmp->right = NULL;
	tmp->data = val;

	return tmp;
}

void __bt_insert(btnode **root, btnode *node)
{
	if (*root == NULL) {
		*root = node;
		return;
	}

	if (node->data < (*root)->data) {
		__bt_insert(&((*root)->left), node);
	} else {
		__bt_insert(&((*root)->right), node);
	}
}

void bt_insert(btnode **root, int val)
{
	btnode *new = btnode_new(val);

	__bt_insert(root, new);
}


btnode *bt_search(btnode *root, int val)
{
	if (root->data == val) {
		return root;
	} else if (root->data < val) {
		if (root->right != NULL) {
			return bt_search(root->right, val);
		} else {
			return NULL;
		}
	} else {
		if (root->left != NULL) {
			return bt_search(root->left, val);
		} else {
			return NULL;
		}
	}
}


void bt_remove(btnode **root, btnode *node)
{

}


void bt_destroy(btnode *root) 
{
	if(root) {
		bt_destroy(root->left);
		bt_destroy(root->right);
		free(root);
	}
}

void print_preorder(btnode *root) {
	if(root) {
		printf("%d\n",root->data);
		print_preorder(root->left);
		print_preorder(root->right);
	}
}

void print_inorder(btnode *root) {
	if(root) {
		print_inorder(root->left);
		printf("%d\n",root->data);
		print_inorder(root->right);
	}
}

void print_postorder(btnode *root) {
	if(root) {
		print_postorder(root->left);
		print_postorder(root->right);
		printf("%d\n",root->data);
	}
}

void binary_tree_test(int argc, char* argv[])
{
	int ret, a;
	btnode *root = NULL;
	btnode *node = NULL;

	bt_insert(&root, 15);
	bt_insert(&root, 9);
	bt_insert(&root, 20);
	bt_insert(&root, 8);
	bt_insert(&root, 10);
	bt_insert(&root, 18);	
	bt_insert(&root, 24);
	bt_insert(&root, 21);	
	bt_insert(&root, 19);
	bt_insert(&root, 25);
	bt_insert(&root, 12);

	printf("pls input the val:");
	scanf("%d", &a);
	node = bt_search(root, a);
	if (node) {
		printf("find %d in tree\n", a);
	} else {
		printf("Can't find %d in tree\n", a);
	}

	/*printf("preodrer\n");
	print_preorder(root);
	printf("===============\n");*/

	/*printf("inodrer\n");
	print_inorder(root);
	printf("===============\n");

	printf("postodrer\n");
	print_postorder(root);
	printf("===============\n");*/

	bt_destroy(root);
}


