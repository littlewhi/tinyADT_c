#include <assert.h>
#include <stdlib.h>

#define GENERIC_STATIC_QUEUE_STRUCT( element_type, suffix, queue_size )\
struct queue_##suffix{\
    int _front, _tail;\
    int _size;\
    element_type _data[queue_size + 1];\
    int (*is_empty)( struct queue_##suffix *self );\
    int (*is_full)( struct queue_##suffix *self );\
    element_type (*get_front)( struct queue_##suffix *self );\
    element_type (*get_tail)( struct queue_##suffix *self );\
    void (*push)( struct queue_##suffix *self, element_type e);\
    void (*pop)( struct queue_##suffix *self );\
}

#define GENERIC_STATIC_QUEUE_METHOD( element_type, suffix, queue_size )\
int is_full_##suffix( struct queue_##suffix *self )\
{\
    return ( self->_tail + 1 ) % self->_size == self->_front;\
}\
\
int is_empty_##suffix( struct queue_##suffix *self )\
{\
    return self->_front == self->_tail;\
}\
\
element_type get_front_##suffix( struct queue_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    return self->_data[self->_front];\
}\
\
element_type get_tail_##suffix( struct queue_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    return self->_data[( self->_tail - 1 + self->_size ) % self->_size];\
}\
\
void push_##suffix( struct queue_##suffix *self, element_type e)\
{\
    assert( !self->is_full( self ) );\
    self->_data[self->_tail] = e;\
    self->_tail += 1;\
}\
\
void pop_##suffix( struct queue_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    self->_front = ( self->_front + 1 ) % self->_size;\
}\
\
struct queue_##suffix *get_static_queue_##suffix( void )\
{\
    struct queue_##suffix *ret = (struct queue_##suffix *)malloc( sizeof( struct queue_##suffix ) );\
    ret->_size = queue_size + 1;\
    ret->_front = 0;\
    ret->_tail = 0;\
    ret->is_empty = is_empty_##suffix;\
    ret->is_full = is_full_##suffix;\
    ret->get_front = get_front_##suffix;\
    ret->get_tail = get_tail_##suffix;\
    ret->push = push_##suffix;\
    ret->pop = pop_##suffix;\
    return ret;\
}\
\
void destroy_static_queue_##suffix( struct queue_##suffix *p )\
{\
    free( p );\
}

#define GENERIC_STATIC_QUEUE_OBJ( suffix ) get_static_queue_##suffix()
#define DESTROY_STATIC_QUEUE_OBJ( p, suffix ) destroy_static_queue_##suffix( p )