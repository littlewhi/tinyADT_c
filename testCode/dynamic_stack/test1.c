#include "../../stack/dynamic_memory_stack/dynamic_stack.h"
#include <stdio.h>

GENERIC_DYNAMIC_STACK_STRUCT( int, test );
GENERIC_DYNAMIC_STACK_METHOD( int, test );

int main( void )
{
    int i;
    struct stack_test *t = GENERIC_DYNAMIC_STACK_OBJ( test );

    printf( "The new stack is %s\n", t->is_empty( t ) ? "empty" : "not empty" );
    printf( "The size of the stack is %d\n", t->_size );
    for( i = 0; i < INITIAL_STACK_SIZE + 5; i++ )
    {
        t->push( t, i );
    }
    printf( "The size of the stack is %d\n", t->_size );
    printf( "The top of the stack is %d\n", t->top( t ) );

    DESTROY_DYNAMIC_STACK_OBJ( test, t );
    return 0;
}