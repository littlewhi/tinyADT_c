#include <assert.h>
#include <stdlib.h>

#define INITIAL_QUEUE_SIZE 64
typedef int dqueue_index_t;

#define GENERIC_DYNAMIC_QUEUE_STRUCT( element_type, suffix ) \
struct queue_##suffix { \
    element_type *_data; \
    dqueue_index_t _front; \
    dqueue_index_t _back; \
    dqueue_index_t _size; \
    int(*is_empty)( struct queue_##suffix *self ); \
    int (*is_full)( struct queue_##suffix *self ); \
    element_type(*get_front)( struct queue_##suffix *self ); \
    element_type(*get_back)( struct queue_##suffix *self ); \
    void (*push)( struct queue_##suffix *self, element_type e ); \
    void (*pop)( struct queue_##suffix *self ); \
}

#define GENERIC_DYNAMIC_QUEUE_METHOD( element_type, suffix ) \
int is_empty_##suffix( struct queue_##suffix *self ) \
{ \
    return self->_front == self->_back; \
} \
\
int is_full_##suffix( struct queue_##suffix *self ) \
{ \
    return ( self->_back + 1 ) % self->_size == self->_front; \
} \
\
element_type get_front_##suffix( struct queue_##suffix *self ) \
{ \
    if( !self->is_empty( self ) ) \
        return self->_data[self->_front]; \
    return ( element_type ) 0; \
} \
\
element_type get_back_##suffix( struct queue_##suffix *self ) \
{ \
    if( !self->is_empty( self ) ) \
        return self->_data[( self->_back - 1 + self->_size ) % self->_size]; \
    return ( element_type ) 0; \
} \
\
void push_##suffix( struct queue_##suffix *self, element_type e ) \
{ \
    element_type *tmp = NULL; \
    if( self->is_full( self ) ) \
    { \
        tmp = ( element_type * ) realloc( self->_data, sizeof( element_type ) * self->_size * 2 ); \
        if( !tmp ) \
            return; \
        self->_data = tmp; \
        self->_size <<= 1; \
    } \
    self->_data[self->_back++] = e; \
    self->_back %= self->_size; \
} \
\
void pop_##suffix( struct queue_##suffix *self ) \
{ \
    if( !self->is_empty( self ) ) \
    { \
        self->_front = ( self->_front + 1 ) % self->_size; \
    } \
} \
\
struct queue_##suffix *get_dynamic_queue_##suffix( void ) \
{ \
    struct queue_##suffix *ret = NULL; \
    \
    ret = (struct queue_##suffix *) malloc( sizeof( struct queue_##suffix) ); \
    if( !ret ) \
        return NULL; \
    \
    ret->_data = (element_type *) malloc( sizeof( element_type ) * INITIAL_QUEUE_SIZE ); \
    if( !ret->_data ) \
    { \
        free( ret ); \
        return NULL; \
    } \
    ret->_front = ret->_back = 0; \
    ret->_size = INITIAL_QUEUE_SIZE; \
    \
    ret->is_empty = is_empty_##suffix; \
    ret->is_full = is_full_##suffix; \
    ret->get_front = get_front_##suffix; \
    ret->get_back = get_back_##suffix; \
    ret->push = push_##suffix; \
    ret->pop = pop_##suffix; \
    return ret; \
} \
\
void destroy_dynamic_queue_##suffix( struct queue_##suffix *p ) \
{ \
    free( p->_data ); \
    free( p ); \
}

#define GENERIC_DYNAMIC_QUEUE_OBJ( suffix ) get_dynamic_queue_##suffix() 
#define DESTROY_DYNAMIC_QUEUE_OBJ( suffix, p ) destroy_dynamic_queue_##suffix( p )