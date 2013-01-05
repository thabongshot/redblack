#ifndef _RBTREE_H_
#define _RBTREE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __RBTNode
{
	struct __RBTNode* parent;
	struct __RBTNode* left;
	struct __RBTNode* right;

	enum { RED, BLACK } color;

	int key;
	void* data;

} RBTNode;

extern RBTNode* nil;

void		RBT_DestroyTree( RBTNode* tree );

RBTNode*	RBT_CreateNode( int key, void* data );
void		RBT_DestroyNode( RBTNode* node );

RBTNode*	RBT_SearchNode( RBTNode* tree, int key );
RBTNode*	RBT_SearchMinNode( RBTNode* tree );
void		RBT_InsertNode( RBTNode** tree, RBTNode* newnode );
void		RBT_InsertNodeHelper( RBTNode** tree, RBTNode* newnode );
RBTNode*	RBT_RemoveNode( RBTNode** root, int key );
void		RBT_RebuildAfterInsert( RBTNode** tree, RBTNode* newnode );
void		RBT_RebuildAfterRemove( RBTNode** root, RBTNode* x );

void		RBT_RotateLeft( RBTNode** root, RBTNode* parent );
void		RBT_RotateRight( RBTNode** root, RBTNode* parent );


#endif
