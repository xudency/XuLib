#include <stdio.h>
#include <stdlib.h>
#include "type.h"

struct binary_node {
	int data;
	struct binary_node *left;
	struct binary_node *right;	
};

typedef struct binary_node btnode;

void bt_insert(btnode **tree, int val)
{
	if (*tree == NULL) {
		btnode * tmp = malloc(sizeof(btnode));

		tmp->left = tmp->right = NULL;
		tmp->data = val;
		*tree = tmp;
		return;
	}

	if (val < (*tree)->data) {
		bt_insert(&((*tree)->left), val);
	} else if (val > (*tree)->data) {
		bt_insert(&((*tree)->right), val);
	}

	return;
}

void deltree(btnode *tree) 
{
	if(tree) {
		deltree(tree->left);
		deltree(tree->right);
		free(tree);
	}
}


void print_preorder(btnode *tree) {
	if(tree) {
		printf("%d\n",tree->data);
		print_preorder(tree->left);
		print_preorder(tree->right);
	}
}

void print_inorder(btnode *tree) {
	if(tree) {
		print_inorder(tree->left);
		printf("%d\n",tree->data);
		print_inorder(tree->right);
	}
}

void print_postorder(btnode *tree) {
	if(tree) {
		print_postorder(tree->left);
		print_postorder(tree->right);
		printf("%d\n",tree->data);
	}
}


void binary_tree_test(int argc, char* argv[])
{
	btnode *root = NULL;

	bt_insert(&root, 15);
	bt_insert(&root, 9);
	bt_insert(&root, 20);
	bt_insert(&root, 8);
	bt_insert(&root, 10);
	bt_insert(&root, 18);	
	bt_insert(&root, 24);
	bt_insert(&root, 21);	
	bt_insert(&root, 19);

	printf("preodrer\n");
	print_preorder(root);
	printf("===============\n");

	printf("inodrer\n");
	print_inorder(root);
	printf("===============\n");

	printf("postodrer\n");
	print_postorder(root);
	printf("===============\n");

	deltree(root);
}

