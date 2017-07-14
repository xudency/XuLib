#include <stdio.h>
#include <stdlib.h>
#include "type.h"


#define LEFT_CHILD 	0
#define RIGHT_CHILD	1

struct binary_node {
	int data;
	struct binary_node *left;
	struct binary_node *right;	
};

typedef struct binary_node btnode;

// binary_tree ops
//	insert
//	delete
//	search
//	traversal

btnode *bt_search_node(btnode *root, int val, btnode **parent, int *dir);


btnode *btnode_new(int val)
{
	btnode *tmp;

	tmp = malloc(sizeof(btnode));

	tmp->left = tmp->right = NULL;
	tmp->data = val;

	return tmp;
}

void __bt_insert_node(btnode **root, btnode *node)
{
	if (*root == NULL) {
		*root = node;
		return;
	}

	if (node->data < (*root)->data) {
		__bt_insert_node(&((*root)->left), node);
	} else {
		__bt_insert_node(&((*root)->right), node);
	}
}

void bt_insert_node(btnode **root, int val)
{
	btnode *new = btnode_new(val);

	__bt_insert_node(root, new);
}

// when remove a node in binary_tree, we need rebuild it
// No child
//    a.leaf node && has parent && parent's left
//    b.leaf node && has parent && parent's right
//    c.leaf node && no parent, this is root node
// Only one Child
//    d. (has left child && no right child) && parent's left 
//    e. (has left child && no right child) && parent's right
//    f. (has left child && no right child) && no parent
//    g. (has right child && no left child) && parent's left 
//    h. (has right child && no left child) && parent's right
//    i. (has right child && no left child) && no parent
// Two Child
//    j. (both child && has parent) && parent's left
//    k. (both child && has parent) && parent's right
//    l. (both child && no parent)

void __bt_delete_node(btnode** root, btnode *deleteNode)
{  
	btnode* parent = NULL;  
	int dir = -1; 

	// double check the deleteNode is exist, and get parent and dir
	if (bt_search_node(*root, deleteNode->data, &parent, &dir) == NULL) {
		printf("Error state");
		return;
	}

	//leaf node
        if(deleteNode->left == NULL && deleteNode->right == NULL) {  
                if(parent != NULL) {  
                        if (dir == LEFT_CHILD)  
                                parent->left = NULL;   //a
                        else  
                                parent->right = NULL;  //b
                } else {
                        *root = NULL;  		       //c
                }  
        } else if (deleteNode->left != NULL && deleteNode->right == NULL) {  
    		if (parent != NULL) {  
                        if (dir == LEFT_CHILD)  
                                parent->left = deleteNode->left;  //d
                        else  
                                parent->right = deleteNode->left;  //e
                } else {
                        *root = deleteNode->left;  		//f
                }  
        } else if (deleteNode->left == NULL && deleteNode->right != NULL){  
    		if (parent != NULL) {  
                        if (dir == LEFT_CHILD)  
                                parent->left = deleteNode->right;  //g
                        else  
                                parent->right = deleteNode->right;  //h
                } else {
                        *root = deleteNode->right;  //i
                }  
        } else {  
                __bt_insert_node(&deleteNode->left,deleteNode->right);  
    		if (parent != NULL) {  
                        if(dir == LEFT_CHILD)  
                                parent->left = deleteNode->left;  //j 
                        else  
                                parent->right = deleteNode->left; //k
                } else {
                        *root = deleteNode->left;    //l
                }  
        }  
        free(deleteNode); 
        deleteNode = NULL;
}

void bt_delete_node(btnode** root, int value)
{
        int dir = -1;  
        btnode* parent = NULL;  

        btnode* deleteNode = bt_search_node(*root, value, &parent, &dir); 
        if(deleteNode == NULL){  
                printf("%s\n", "node not found");
        } else {
		__bt_delete_node(root, deleteNode);
	}
}


btnode *bt_search_node(btnode *root, int val, btnode **parent, int *dir)
{
	if (root->data == val) {
		return root;
	} else if (root->data < val) {
		if (root->right != NULL) {
			*dir = RIGHT_CHILD;
			*parent = root;
			return bt_search_node(root->right, val, parent, dir);
		} else {
			return NULL;
		}
	} else {
		if (root->left != NULL) {			
			*dir = LEFT_CHILD;
			*parent = root;
			return bt_search_node(root->left, val, parent, dir);
		} else {
			return NULL;
		}
	}
}


void bt_destroy(btnode *root) 
{
	if(root) {
		bt_destroy(root->left);
		bt_destroy(root->right);
		free(root);
	}
}

btnode *bt_next_entry(btnode **root)
{
	btnode *node = *root;

	if ((*root)->left) {
		*root = (*root)->left;
		return node;
	}

	if ((*root)->right) {
		*root = (*root)->right;
		return node;
	}

	return NULL;
}

void travesal_bt(btnode *root)
{
	if (root) {
		btnode *node = root;
		//do something, Just print
		printf("%d\n", node->data);
		
		travesal_bt(root->left);
		travesal_bt(root->right);
	}
}

/*btnode *next_entry(btnode **root)
{
	if (root) {
		btnode *node = root;
		
		//do something, Just print
		printf("%d\n", node->data);
		
		travesal_bt(root->left);
		travesal_bt(root->right);
	} else {
		return NULL;
	}
}*

/*
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
}*/

void binary_tree_test(int argc, char* argv[])
{
	int a, dir = 0;
	btnode *root = NULL;
	btnode *node = NULL;
	btnode *parent = NULL;

	bt_insert_node(&root, 15);
	bt_insert_node(&root, 9);
	bt_insert_node(&root, 20);
	bt_insert_node(&root, 8);
	bt_insert_node(&root, 10);
	bt_insert_node(&root, 18);	
	bt_insert_node(&root, 24);
	bt_insert_node(&root, 12);	
	bt_insert_node(&root, 19);
	bt_insert_node(&root, 22);
	bt_insert_node(&root, 28);
	bt_insert_node(&root, 21);
	bt_insert_node(&root, 27);

	travesal_bt(root);

#if 0
	printf("pls input the val:");
	scanf("%d", &a);
	node = bt_search_node(root, a, &parent, &dir);
	if (node) {
		printf("find %d in tree, parent:%d dir:%d[L-0  R-1]\n", 
				a, parent->data, dir);
	} else {
		printf("Can't find %d in tree\n", a);
	}
#endif

#if 0
	printf("preodrer\n");
	print_preorder(root);
	printf("===============\n");

	printf("inodrer\n");
	print_inorder(root);
	printf("===============\n");

	printf("postodrer\n");
	print_postorder(root);
	printf("===============\n");
#endif

	bt_destroy(root);
}


