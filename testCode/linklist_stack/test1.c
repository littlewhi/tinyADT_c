#include "../../stack/linklist/ll_stack.h"
#include <stdio.h>

GENERIC_LL_STACK_STRUCT( int, test1 );
GENERIC_LL_STACK_METHOD( int, test1 );

int main( void )
{
    struct stack_test1 *t = GENERIC_LL_STACK_OBJ( test1 );
    t->push( t, 1 );
    t->push( t, 2 );
    printf( "%d\n", t->top( t ) );
    t->pop( t );
    printf( "%d\n", t->top( t ) );
    t->pop( t );
    if( t->is_empty( t ) )
        printf( "Empty stack now.\n" );

    DESTROY_LL_STACK_OBJ( t, test1 );
    return 0;
}