#include "../../stack/static/static_stack.h"
#include <stdio.h>

GENERIC_STATIC_STACK_STRUCT( int, test1, 10 );
GENERIC_STATIC_STACK_METHOD( int, test1, 10 );

int main( void )
{
    struct stack_test1 *st1 = NULL;

    st1 = GENERIC_STATIC_STACK_OBJECT( test1 );

    printf( "It is empty?\n" );
    printf( "%s\n", st1->is_empty( st1 ) ? "YES" : "NO" );
    printf( "Push 12, 13, 20 in the stack.\n" );
    st1->push( st1, 12 );
    st1->push( st1, 13 );
    st1->push( st1, 20 );
    printf( "The top of the stack is %d\n", st1->top( st1 ) );
    printf( "Pop a element from the stack\n" );
    printf( "The top of the stack is %d\n", st1->top( st1 ) );

    return 0;
}