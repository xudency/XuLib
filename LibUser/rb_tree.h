#ifndef _RB_TREE_DEF_H
#define _RB_TREE_DEF_H

typedef enum {
	RB_RED = 0,
	RB_BLACK = 1
} RBColor;

typedef struct RBTreeNode {
	RBColor rb_color;
	int Key;	// Read Black Tree organization by Key
	void *Value;
	struct RBTreeNode *rb_left;
	struct RBTreeNode *rb_right;
	struct RBTreeNode *rb_parent;
} rb_node;

typedef struct RBTreeRoot {
	struct RBTreeNode *rb_node;
} rb_root;


#define rb_parent(r)       ((struct rb_node *)((r)->rb_parent))
#define rb_left_child(r)   ((struct rb_node *)((r)->rb_left))
#define rb_right_child(r)  ((struct rb_node *)((r)->rb_right))
#define rb_color(r)        ((r)->rb_color)
#define rb_is_red(r)       ((r)->rb_color & RB_RED)
#define rb_is_black(r)     ((r)->rb_color & RB_BLACK)
#define rb_set_red(r)      ((r)->rb_color = RB_RED)
#define rb_set_black(r)    ((r)->rb_color = RB_BLACK)

static inline void rb_set_parent(rb_node* node, rb_node* p) 
{
	node->rb_parent = p;
}

static inline void rb_set_left(rb_node* node, rb_node* child) 
{
	node->rb_left = child;
	rb_set_parent(child, node);
}

static inline void rb_set_right(rb_node* node, rb_node* child) 
{
	node->rb_right = child;
	rb_set_parent(child, node);
}

static inline bool rb_is_left(rb_node* node, rb_node* p) 
{
	return p->rb_left == node;
}

static inline bool rb_is_right(rb_node* node, rb_node* p) 
{
	return p->rb_right == node;
}

#endif

