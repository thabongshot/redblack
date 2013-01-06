#include "rbtree.h"


RBTNode* RBT_CreateNode( int key, void* data )
{
	RBTNode* newnode = (RBTNode*)malloc( sizeof(RBTNode) );
	newnode->parent  = NULL;
	newnode->left	 = NULL;
	newnode->right	 = NULL;

	newnode->key	 = key;
	newnode->data	 = data;
	newnode->color	 = BLACK;

	return newnode;
}

void RBT_DestroyNode( RBTNode* node )
{
	free(node);
}

void RBT_InitNil()
{
	nil = RBT_CreateNode( -1, NULL);
	nil->color = BLACK;
}

void RBT_DestroyTree( RBTNode* tree )
{
	if( tree->right != nil ){
		RBT_DestroyTree( tree->right );
	}

	if( tree->left != nil ){
		RBT_DestroyTree( tree->left );
	}

	tree->left = nil;
	tree->right = nil;

	RBT_DestroyNode( tree );
}

RBTNode* RBT_SearchNode( RBTNode* tree, int key )
{
	if( tree == nil ){
		return NULL;
	}

	if( tree->key > key ){
		return RBT_SearchNode( tree->left, key );
	} else if ( tree->key < key ){
		return RBT_SearchNode( tree->right, key );
	} else {
		return tree;
	}
}

RBTNode* RBT_SearchMinNode( RBTNode* tree )
{
	if( tree == nil ){
		return nil;
	}

	if( tree->left == nil ){
		return tree;
	} else {
		return RBT_SearchMinNode( tree->left );
	}
}

void RBT_InsertNode( RBTNode** tree, RBTNode* newnode )
{
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
	RBT_InsertNodeHelper( tree, newnode );
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);

	newnode->color = RED;
	newnode->left = nil;
	newnode->right = nil;

printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
	RBT_RebuildAfterInsert( tree, newnode );
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
}


void RBT_InsertNodeHelper( RBTNode** tree, RBTNode* newnode)
{
    if ( (*tree) == NULL )
        (*tree) = newnode;

    if ( (*tree)->key < newnode->key ) 
    {
        if ( (*tree)->right == nil )
        {
            (*tree)->right  = newnode;
            newnode->parent = (*tree);
        }
        else
            RBT_InsertNodeHelper(&(*tree)->right, newnode);

    } 
    else if ( (*tree)->key > newnode->key ) 
    {
        if ( (*tree)->left == nil )
        {
            (*tree)->left   = newnode;
            newnode->parent = (*tree);
        }
        else
            RBT_InsertNodeHelper(&(*tree)->left, newnode);
    }
}

void RBT_RotateRight( RBTNode** root, RBTNode* parent )
{
    RBTNode* leftchild =  parent->left;

    parent->left = leftchild->right;

    if ( leftchild->right != nil )
        leftchild->right->parent = parent;

    leftchild->parent = parent->parent;

    if ( parent->parent == NULL )
        (*root) = leftchild;
    else
    {
        if ( parent == parent->parent->left )
            parent->parent->left = leftchild;
        else
            parent->parent->right = leftchild;
    }

    leftchild->right  = parent;
    parent->parent = leftchild;
}

void RBT_RotateLeft( RBTNode** root, RBTNode* parent )
{
    RBTNode* rightchild = parent->right;
    
    parent->right = rightchild->left;

    if ( rightchild->left != nil )
        rightchild->left->parent = parent;

    rightchild->parent = parent->parent;

    if ( parent->parent == NULL )
        (*root) = rightchild;
    else
    {
        if ( parent == parent->parent->left )
            parent->parent->left = rightchild;
        else
            parent->parent->right = rightchild;        
    }

    rightchild->left   = parent;
    parent->parent = rightchild;
}


void RBT_RebuildAfterInsert( RBTNode** root, RBTNode* x )
{
    while ( x != (*root) && x->parent->color == RED ) 
    {
       if ( x->parent == x->parent->parent->left ) 
       {
           RBTNode* Uncle = x->parent->parent->right;
           if ( Uncle->color == RED ) 
           {
               x->parent->color         = BLACK;
               Uncle->color                   = BLACK;
               x->parent->parent->color = RED;

               x = x->parent->parent;
           }
           else 
           {
               if ( x == x->parent->right ) 
               {
                   x = x->parent;
                   RBT_RotateLeft( root, x );
               }
               
               x->parent->color         = BLACK;
               x->parent->parent->color = RED;

               RBT_RotateRight( root, x->parent->parent );
           }
       }
       else 
       {
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
            RBTNode* Uncle = x->parent->parent->left;
           if ( Uncle->color == RED ) 
           {
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
               x->parent->color         = BLACK;
               Uncle->color                   = BLACK;
               x->parent->parent->color = RED;

               x = x->parent->parent;
           }
           else 
           {
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
               if ( x == x->parent->left ) 
               {
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);
                   x = x->parent;
                   RBT_RotateRight( root, x );
               }
               
               x->parent->color         = BLACK;
               x->parent->parent->color = RED;
               RBT_RotateLeft( root, x->parent->parent );
           }
       }
    }
printf("[DEBUG] %d:%s\n", __LINE__,__FUNCTION__);

    (*root)->color = BLACK;
}

RBTNode* RBT_RemoveNode( RBTNode** root, int key )
{
	RBTNode* removed = NULL;
	RBTNode* successor = NULL;
	RBTNode* target = RBT_SearchNode( (*root), key );

	if( target == NULL ){
		return NULL;
	}

	if( target->left == nil || target->right == nil ){
		removed = target;
	} else {
		removed = RBT_SearchMinNode( target->right );
		target->data = removed->data;
	}

	if( removed->left != nil ){
		successor = removed->left;
	}else {
		successor = removed->right;
	}

	successor->parent = removed->parent;

	if( removed->parent == NULL ){
		(*root) = successor;
	} else {
		if( removed == removed->parent->left ){
			removed->parent->left = successor;
		} else {
			removed->parent->right = successor;
		}
	}
	
	if( removed->color == BLACK ){
		RBT_RebuildAfterRemove( root, successor );
	}

	return removed;
}

void RBT_RebuildAfterRemove( RBTNode** root, RBTNode* successor )
{
    RBTNode* sibling = NULL;

    while ( successor->parent != NULL && successor->color == BLACK)
    {
        if ( successor == successor->parent->left )
        {
            sibling = successor->parent->right;

            if ( sibling->color == RED )
            {
                sibling->color = BLACK;
                successor->parent->color = RED;
                RBT_RotateLeft( root, successor->parent );
            }
            else
            {
                if ( sibling->left->color == BLACK && 
                     sibling->right->color == BLACK )
                {
                    sibling->color = RED;
                    successor      = successor->parent;
                }
                else 
                {
                    if ( sibling->left->color == RED )
                    {
                        sibling->left->color = BLACK;
                        sibling->color       = RED;

                        RBT_RotateRight( root, sibling );
                        sibling = successor->parent->right;
                    }

                    sibling->color           = successor->parent->color;
                    successor->parent->color = BLACK;
                    sibling->right->color    = BLACK;
                    RBT_RotateLeft( root, successor->parent );
                    successor = (*root);
                }
            }            
        } 
        else
        {
            sibling = successor->parent->left;

            if ( sibling->color == RED )
            {
                sibling->color           = BLACK;
                successor->parent->color = RED;
                RBT_RotateRight( root, successor->parent );
            }
            else
            {
                if ( sibling->right->color == BLACK && 
                     sibling->left->color  == BLACK )
                {
                    sibling->color = RED;
                    successor      = successor->parent;
                }
                else 
                {
                    if ( sibling->right->color == RED )
                    {
                        sibling->right->color = BLACK;
                        sibling->color        = RED;

                        RBT_RotateLeft( root, sibling );
                        sibling = successor->parent->left;
                    }

                    sibling->color           = successor->parent->color;
                    successor->parent->color = BLACK;
                    sibling->left->color     = BLACK;
                    RBT_RotateRight( root, successor->parent );
                    successor = (*root);
                }
            }
        }
    }

    successor->color = BLACK;
}
