#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "rb_tree.h"

/* * �Ժ�����Ľڵ�(x)��������ת * * ����ʾ��ͼ(�Խڵ�x��������)�� */  

_left_rotate(struct RBTreeRoot *root, struct RBTreeNode *node) 
{
    struct RBTreeNode *right = node->rb_right, *parent = rb_parent(node);

    // ��һ������ly���ӵ�x���ҽ����
    rb_set_right(node, right->rb_left);

    // �ڶ�������x����Ϊy�����ӽ��
    rb_set_left(right, node);

    // ����������y����Ϊpx���ӽ��
    if (parent) {
        if (rb_is_left(node, parent)) {
            rb_set_left(right, parent);
        }
        else {
            rb_set_right(right, parent);
        }
    }
    else {
        root->rb_node = right; // �����
    }
}

/* �Ժ�����Ľڵ�(y)��������ת * * ����ʾ��ͼ(�Խڵ�y��������) */

_right_rotate(struct RBTreeRoot *root, struct RBTreeNode *node) 
{
    struct RBTreeNode *left = node->rb_left, *parent = rb_parent(node);

    // ��һ������rx����Ϊy�����ӽ��
    rb_set_left(node, left->rb_right);

    // �ڶ�������y����Ϊx�����ӽ��
    rb_set_right(left, node);

    // ����������x����Ϊpy���ӽ��
    if (parent) {
        if (rb_is_left(node, parent)) {
            rb_set_left(parent, left);
        }
        else {
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
rb_rebalance(struct RBTreeNode * node) 
{
    struct RBTreeNode *parent, *g_parent;

    // ��������4
    while ((parent = rb_parent(node)) && rb_is_red(parent)) {
    	g_parent = rb_parent(parent);

        if (rb_is_left(parent, g_parent)) 
	{
            {
                // case 1���������Ǻ�ɫ
                // �Ĵ������������Ч��
                struct RBTreeNode *uncle = g_parent->rb_right;
                // �޷���������4
                if (uncle && rb_is_red(uncle)) {
                    // step1�������׺����������óɺ�ɫ
                    rb_set_blacks(2, parent, uncle);
                    // step2�����游���óɺ�ɫ����Ϊ֮ǰ��ȻΪ��ɫ����Ȼ�޷���������4��
                    rb_set_red(g_parent);
                    // step3���ݹ����游���
                    node = g_parent;
                    continue;
                }
            }

            // �޷���������5
            // case 2���������Ǻ�ɫ�����ҵ�ǰ������ұߣ���ȻҪ����˫��ת
            if (rb_is_right(node, parent)) {
                struct RBTreeNode *temp;

                // step 1�������׽���������
                _left_rotate(_root, parent); // ��ʱ�����Ϊ��ǰ�������ӽ��
                // step 2������ǰ���͸������н���
                temp = parent;
                parent = node;
                node = temp;
            }

            // ��ʱ���׽��͵�ǰ�����Ǻ�ɫ���޷���������4������5
            // case 3���������Ǻ�ɫ�����ҵ�ǰ�������ߣ�ֻ�õ���ת
            // step 1�������׽��ĳɸĳɺ�ɫ���游���ĳɺ�ɫ���Ա���������ת��
            // ��ɫ�����ӽ����游���Ϊ��ɫ�ĸ������ӽ��
            rb_set_black(parent);
            rb_set_red(g_parent);
            // step 2������ת
            _right_rotate(_root, g_parent);  // ��������ת�󣬺�ɫ���ֲ�������
        }
	
        else 
	{  // ˳���෴����
            {
                // case 4���������Ǻ�ɫ
                // �Ĵ������������Ч��
                struct RBTreeNode *uncle = g_parent->rb_left;
                // �޷���������4
                if (uncle && rb_is_red(uncle)) {
                    // step1�������׺����������óɺ�ɫ
                    rb_set_blacks(2, parent, uncle);
                    // step2�����游���óɺ�ɫ����Ϊ֮ǰ��ȻΪ��ɫ����Ȼ�޷���������4��
                    rb_set_red(g_parent);
                    // step3���ݹ����游���
                    node = g_parent;
                    continue;
                }
            }

            // �޷���������5
            // case 5���������Ǻ�ɫ�����ҵ�ǰ�������ߣ���ȻҪ����˫��ת
            if (rb_is_left(node, parent)) {
                struct RBTreeNode *temp;

                // step 1�������׽���������
                _right_rotate(_root, parent); // ��ʱ�����Ϊ��ǰ�������ӽ��
                // step 2������ǰ���͸������н���
                temp = parent;
                parent = node;
                node = temp;
            }

            // ��ʱ���׽��͵�ǰ�����Ǻ�ɫ���޷���������4������5
            // case 3���������Ǻ�ɫ�����ҵ�ǰ������ұߣ�ֻ�õ���ת
            // step 1�������׽��ĳɸĳɺ�ɫ���游���ĳɺ�ɫ���Ա���������ת��
            // ��ɫ�����ӽ����游���Ϊ��ɫ�ĸ������ӽ��
            rb_set_black(parent);
            rb_set_red(g_parent);
            // step 2������ת
            _left_rotate(_root, g_parent);  // ��������ת�󣬺�ɫ���ֲ�������
        }
    }
}

rb_node* rb_add_node(rb_root *root, rb_node *node) 
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

	return node;
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

void rb_insert_node(int Key, void* Value) 
{
	rb_node* node = RBTree_NewNode(Key, Value);

	__rb_insert_node(node);
}

void __rb_insert_node(rb_node *node) 
{
	// the same with BST ops
	rb_add_node(node);
	
	rb_rebalance(node);
}

