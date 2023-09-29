#include "../../BST/static/static_bst.h"
#include <stdio.h>

GENERIC_STATIC_BST_STRUCT( int, test1, 10 );
GENERIC_STATIC_BST_METHOD( int, test1, 10 );

static int cmp_for_t1( void *a, void *b )
{
    return *(int *)a - *(int *)b;
}

void construct_a_bt( int *arr, int num,  struct bst_test1 *t1 )
{
    int i;
    for( i = 0; i < num; i++ )
    {
        t1->insert( t1, arr[i] );
    }
}

void traversal_func( int *e )
{
    printf( "%d ", *e );
}

int main( void )
{
    int arr[] = { 3, 2, 5, 1, 4, 6 };
    struct bst_test1 *t1 = malloc( sizeof( struct bst_test1 ));
    GENERIC_STATIC_BST_OBJ( test1, t1, cmp_for_t1 );
    
    printf( "Construct a binary tree :\n" );
    printf( "   3\n" );
    printf( " 2   5\n" );
    printf( "1 x 4 6\n" ); 
    construct_a_bt( arr, sizeof( arr) / sizeof( arr[0] ), t1 );
    printf( "\n" );
    printf( "Preorder traversal : \n" );
    t1->pre_traversal( t1, 0, traversal_func );
    printf( "\n" );
    printf( "Middle-order traversal : \n" );
    t1->mid_traversal( t1, 0, traversal_func );
    printf( "\n" );
    printf( "Postorder traversal : \n" );
    t1->post_traversal( t1, 0, traversal_func );
    printf( "\n" );
    printf( "Breadth first traversal : \n" );
    t1->bf_traversal( t1, 0, traversal_func );
    printf( "\n" );
    printf( "delete 3 in the tree \n" );
    t1->remove( t1, 3 );
    t1->mid_traversal( t1, 0, traversal_func );
    printf( "\n" );

    free( t1 );
}