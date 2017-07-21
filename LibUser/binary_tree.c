#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "type.h"


#define LEFT_CHILD 	0
#define RIGHT_CHILD	1

// BST, Binary Sort Tree

struct BSTreeNode {
	int data;
	struct BSTreeNode *left;
	struct BSTreeNode *right;	
};

struct BSTreeRoot {
	struct BSTreeNode *node;
};

typedef struct BSTreeNode bst_node;
typedef struct BSTreeRoot bst_root;

bst_node *bst_search_node(bst_node *root, int val, bst_node **parent, int *dir);

//////////////////////////////

bst_node *BSTree_NewNode(int val)
{
	bst_node *tmp;

	tmp = malloc(sizeof(bst_node));

	tmp->left = tmp->right = NULL;
	tmp->data = val;

	return tmp;
}

void __bst_insert_node(bst_root *root, bst_node *node)
{
	bst_node *tmp = root->node;
	bst_node *tmp_parent = NULL;

	while (tmp) {
		tmp_parent = tmp;
		if (node->data < tmp->data) {
			tmp = tmp->left;
		} else {
			tmp = tmp->right;
		}
	}

	if (tmp_parent) {
		if (node->data < tmp_parent->data) {
			tmp_parent->left = node;			
		} else {
			tmp_parent->right = node;			
		}
	} else {
		root->node = node;
	} 

	/*if (root == NULL) {
		root = node;
		return;
	}

	if (node->data < (root)->data) {
		__bst_insert_node(&((root)->left), node);
	} else {
		__bst_insert_node(&((root)->right), node);
	}*/
}

void bst_insert_node(bst_root *root, int val)
{
	bst_node *new = BSTree_NewNode(val);

	__bst_insert_node(root, new);
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

void __bt_delete_node(bst_node** root, bst_node *deleteNode)
{  
	bst_node* parent = NULL;  
	int dir = -1; 

	// double check the deleteNode is exist, and get parent and dir
	if (bst_search_node(*root, deleteNode->data, &parent, &dir) == NULL) {
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
        	bst_root tmp;
		tmp.node = deleteNode->left;
                __bst_insert_node(&tmp, deleteNode->right);  
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

void bt_delete_node(bst_node** root, int value)
{
        int dir = -1;  
        bst_node* parent = NULL;  

        bst_node* deleteNode = bst_search_node(*root, value, &parent, &dir); 
        if(deleteNode == NULL){  
                printf("%s\n", "node not found");
        } else {
		__bt_delete_node(root, deleteNode);
	}
}


bst_node *bst_search_node(bst_node *fnode, int val, bst_node **parent, int *dir)
{
	if (fnode->data == val) {
		return fnode;
	} else if (fnode->data < val) {
		if (fnode->right != NULL) {
			*dir = RIGHT_CHILD;
			*parent = fnode;
			return bst_search_node(fnode->right, val, parent, dir);
		} else {
			return NULL;
		}
	} else {
		if (fnode->left != NULL) {			
			*dir = LEFT_CHILD;
			*parent = fnode;
			return bst_search_node(fnode->left, val, parent, dir);
		} else {
			return NULL;
		}
	}
}

void bst_destroy(bst_node *fnode) 
{
	if(fnode) {
		bst_destroy(fnode->left);
		bst_destroy(fnode->right);
		free(fnode);
	}
}

void travesal_bst(bst_node *fnode)
{
	//bst_node *node = root->node;

	if (fnode) {
		//bst_node *node = root->node;
		//do something, Just print
		printf("%d\n", fnode->data);
		
		travesal_bst(fnode->left);
		travesal_bst(fnode->right);
	}
}


void BSTree_test(int argc, char* argv[])
{
	bst_root root;
	memset(&root, 0x00, sizeof(root));

	bst_insert_node(&root, 15);
	bst_insert_node(&root, 9);
	bst_insert_node(&root, 20);
	bst_insert_node(&root, 8);
	bst_insert_node(&root, 10);
	bst_insert_node(&root, 18);	
	bst_insert_node(&root, 24);
	bst_insert_node(&root, 12);	
	bst_insert_node(&root, 19);
	bst_insert_node(&root, 22);
	bst_insert_node(&root, 28);
	bst_insert_node(&root, 21);
	bst_insert_node(&root, 27);

	travesal_bst(root.node);

#if 1
	int a, dir = 0;
	bst_node *node = NULL;
	bst_node *parent = NULL;

	printf("pls input the val:");
	scanf("%d", &a);
	node = bst_search_node(root.node, a, &parent, &dir);
	if (node) {
		printf("find %d in tree, parent:%d dir:%d[L-0  R-1]\n", 
				a, parent->data, dir);
	} else {
		printf("Can't find %d in tree\n", a);
	}
#endif

	bst_destroy(root.node);
}

