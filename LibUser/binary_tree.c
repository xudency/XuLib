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


void print_preorder(btnode * tree) 
{
	if(tree) {
		printf("%d\n",tree->data);
		print_preorder(tree->left);
		print_preorder(tree->right);
	}
}


void binary_tree_test(int argc, char* argv[])
{
	btnode *root = NULL;

	PRINT("start insert");

	insert(&root, 15);
	insert(&root, 9);
	insert(&root, 20);
	insert(&root, 8);
	insert(&root, 10);
	insert(&root, 18);	
	insert(&root, 24);
	insert(&root, 21);

	PRINT("end insert");
	print_preorder(root);

	deltree(root);
}

