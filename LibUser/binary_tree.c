#include <stdio.h>
#include <stdlib.h>
#include "type.h"

struct binary_node {
	int data;
	struct binary_node *left;
	struct binary_node *right;	
};

typedef struct binary_node btnode;


void insert(btnode **tree, int val) 
{
	btnode *temp = NULL;
	
	if(!(*tree)) {
		temp = (btnode *)malloc(sizeof(btnode));
		temp->left = temp->right = NULL;
		temp->data = val;
		*tree = temp;
		return ;
	}

	if (val < (*tree)->data) {
		insert(&(*tree)->left,val);
	}else if (val > (*tree)->data) {
		insert(&(*tree)->right,val);
	}
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

	insert(&root, 15);
	insert(&root, 9);
	insert(&root, 20);
	insert(&root, 8);
	insert(&root, 10);
	insert(&root, 18);	
	insert(&root, 24);
	insert(&root, 21);

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

