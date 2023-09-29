#include "../../queue/static/static_queue.h"
#include <stdio.h>

GENERIC_STATIC_QUEUE_STRUCT( int, test1, 4 );
GENERIC_STATIC_QUEUE_METHOD( int, test1, 4 )


int main( void )
{
    struct queue_test1 qp;
    GENERIC_STATIC_QUEUE_OBJ( test1, &qp );

    printf( "Push 1 2 3 4 into queue\n" );
    qp.push( &qp, 1 );
    qp.push( &qp, 2 );
    qp.push( &qp, 3 );
    qp.push( &qp, 4 );
    printf( "Queue is %s\n", qp.is_full( &qp ) ? "full" : "not full" );
    printf( "The front of queue is %d\n", qp.get_front( &qp ) );
    printf( "The back of queue is %d\n", qp.get_tail( &qp ) );

    return 0;
}