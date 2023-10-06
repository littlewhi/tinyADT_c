#include "../../queue/dynamic_memory_queue/dynamic_queue.h"
#include <stdio.h>

GENERIC_DYNAMIC_QUEUE_STRUCT( int, test1 );
GENERIC_DYNAMIC_QUEUE_METHOD( int, test1 );


int main( void )
{
    struct queue_test1 *t1 = GENERIC_DYNAMIC_QUEUE_OBJ( test1 );
    int i;

    printf( "The new queue is empty? %s\n", t1->is_empty( t1 ) ? "YES" : "NO" );

    for( i = 0; i < 100; i++ )
    {
        t1->push( t1, i );
    }

    for( i = 0; i < 100; i++ )
    {
        printf( "%d ", t1->get_front( t1 ) );
        t1->pop( t1 );
    }
    printf( "\n" );
    return 0;
}