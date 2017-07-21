#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "rb_tree.h"

/* * 对红黑树的节点(x)进行左旋转 * * 左旋示意图(对节点x进行左旋)： */  

void _left_rotate(rb_root *root, rb_node *node) 
{
	rb_node *right = node->rb_right, *parent = rb_parent(node);

	// 第一步：将ly连接到x的右结点上
	rb_set_right(node, right->rb_left);

	// 第二步：将x设置为y的左子结点
	rb_set_left(right, node);

	// 第三步：将y设置为px的子结点
	if (parent) {
		if (rb_is_left(node, parent)) {
			rb_set_left(right, parent);
		} else {
			rb_set_right(right, parent);
		}
	} else {
		root->rb_node = right; // 根结点
	}
}

/* 对红黑树的节点(y)进行右旋转 * * 右旋示意图(对节点y进行左旋) */

void _right_rotate(rb_root *root, rb_node *node) 
{
	rb_node *left = node->rb_left, *parent = rb_parent(node);

	// 第一步：将rx设置为y的左子结点
	rb_set_left(node, left->rb_right);

	// 第二步：将y设置为x的右子结点
	rb_set_right(left, node);

	// 第三步：将x设置为py的子结点
	if (parent) {
		if (rb_is_left(node, parent)) {
			rb_set_left(parent, left);
		} else {
			rb_set_right(parent, left);
		}
	}
}

// parent is g_parent's Right
// 	parent=Red && uncle=Black(NULL)         //left rotate
// 	parent=Red && uncle=Red

// parent is g_parent's Left
//	parent=Red && uncle=Black(NULL)		//right rotate
//	parent=Red && uncle=Red
void rb_rebalance(rb_root *root, rb_node * node) 
{
    rb_node *parent, *g_parent;

    // 满足性质4
    while ((parent = rb_parent(node)) && rb_is_red(parent)) {
    	g_parent = rb_parent(parent);

        if (rb_is_left(parent, g_parent)) 
	{
            {
                // case 1：叔叔结点是红色
                // 寄存器变量，提高效率
                rb_node *uncle = g_parent->rb_right;
                // 无法满足性质4
                if (uncle && rb_is_red(uncle)) {
                    // step1：将父亲和叔叔结点设置成黑色
		    rb_set_black(parent);		    
		    rb_set_black(uncle);
                    // step2：将祖父设置成红色（因为之前必然为黑色，不然无法满足性质4）
                    rb_set_red(g_parent);
                    // step3：递归检查祖父结点
                    node = g_parent;
                    continue;
                }
            }

            // 无法满足性质5
            // case 2：叔叔结点是黑色，并且当前结点在右边，必然要进行双旋转
            if (rb_is_right(node, parent)) {
                rb_node *temp;

                // step 1：将父亲结点进行左旋
                _left_rotate(root, parent); // 此时父结点为当前结点的左子结点
                // step 2：将当前结点和父结点进行交换
                temp = parent;
                parent = node;
                node = temp;
            }

            // 此时父亲结点和当前结点均是红色，无法满足性质4和性质5
            // case 3：叔叔结点是黑色，并且当前结点在左边，只用单旋转
            // step 1：将父亲结点改成改成黑色，祖父结点改成红色，以便后面进行旋转后，
            // 红色的左子结点和祖父结点为黑色的父结点的子结点
            rb_set_black(parent);
            rb_set_red(g_parent);
            // step 2：右旋转
            _right_rotate(root, g_parent);  // 经过右旋转后，红色均分布在两边
        }
	
        else 
	{  // 顺序相反而已
            {
                // case 4：叔叔结点是红色
                // 寄存器变量，提高效率
                rb_node *uncle = g_parent->rb_left;
                // 无法满足性质4
                if (uncle && rb_is_red(uncle)) {
                    // step1：将父亲和叔叔结点设置成黑色                    
		    rb_set_black(parent);		    
		    rb_set_black(uncle);
                    // step2：将祖父设置成红色（因为之前必然为黑色，不然无法满足性质4）
                    rb_set_red(g_parent);
                    // step3：递归检查祖父结点
                    node = g_parent;
                    continue;
                }
            }

            // 无法满足性质5
            // case 5：叔叔结点是黑色，并且当前结点在左边，必然要进行双旋转
            if (rb_is_left(node, parent)) {
                rb_node *temp;

                // step 1：将父亲结点进行左旋
                _right_rotate(root, parent); // 此时父结点为当前结点的右子结点
                // step 2：将当前结点和父结点进行交换
                temp = parent;
                parent = node;
                node = temp;
            }

            // 此时父亲结点和当前结点均是红色，无法满足性质4和性质5
            // case 3：叔叔结点是黑色，并且当前结点在右边，只用单旋转
            // step 1：将父亲结点改成改成黑色，祖父结点改成红色，以便后面进行旋转后，
            // 红色的左子结点和祖父结点为黑色的父结点的子结点
            rb_set_black(parent);
            rb_set_red(g_parent);
            // step 2：左旋转
            _left_rotate(root, g_parent);  // 经过左旋转后，红色均分布在两边
        }
    }
}

void rb_add_node(rb_root *root, rb_node *node) 
{
	rb_node* temp = root->rb_node;
	rb_node* temp_parent = NULL;

	while (temp) {
		temp_parent = temp;
		if (node->Key < temp->Key) {
			temp = temp->rb_left;
		} else {
			temp = temp->rb_right;
		}
	}

	if (temp_parent != NULL) {
		if (node->Key < temp_parent->Key) {
			rb_set_left(temp_parent, node);
		}
		else {
			rb_set_right(temp_parent, node);
		}
	} else {
		root->rb_node = node;	// the rb_tree is empty
	}
}

rb_node *RBTree_NewNode(int Key, void *Value)
{
	rb_node *node;

	node = malloc(sizeof(rb_node));

	node->Key = Key;
	node->Value = Value;
	node->rb_color = RB_RED;
	node->rb_left = node->rb_right = node->rb_parent = NULL;

	return node;
}

void RBTree_ReleaseNode(rb_node *node)
{
	// NOTE: the node->Value is NOT free herein
	free(node);
}

void __rb_insert_node(rb_root *root, rb_node *node) 
{
	// the same with BST ops
	rb_add_node(root, node);
	
	rb_rebalance(root, node);
}

void rb_insert_node(rb_root *root, int Key, void* Value) 
{
	rb_node* node = RBTree_NewNode(Key, Value);

	__rb_insert_node(root, node);
}

