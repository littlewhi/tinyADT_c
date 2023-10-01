#include <stdlib.h>
#include <assert.h>

typedef int size_suffix;

#define INITIAL_SIZE 64

#define GENERIC_DYNAMIC_STACK_STRUCT( element_type, suffix ) \
struct stack_##suffix{ \
    element_type *_data; \
    size_suffix _size; \
    size_suffix _top; \
    int (*is_empty)( struct stack_##suffix *self ); \
    int (*is_full)( struct stack_##suffix *self ); \
    void (*push)( struct stack_##suffix *self, element_type e ); \
    void (*pop)( struct stack_##suffix *self ); \
    element_type (*top)( struct stack_##suffix *self ); \
}

#define GENERIC_DYNAMIC_STACK_METHOD( element_type, suffix ) \
int is_empty_##suffix( struct stack_##suffix *self ) \
{ \
    return self->_top == 0; \
} \
\
int is_full_##suffix( struct stack_##suffix *self ) \
{ \
    return self->_top == self->_size; \
} \
\
void push_##suffix( struct stack_##suffix *self, element_type e ) \
{ \
    if( self->is_full( self ) ) \
    { \
        void *tmp = realloc( self->_data, self->_size * 2 * sizeof( element_type ) ); \
        assert( tmp ); \
        self->_size = self->_size * 2; \
        self->_data = tmp; \
    } \
    self->_data[(self->_top)++] = e; \
} \
\
void pop_##suffix( struct stack_##suffix *self ) \
{ \
    assert( !self->is_empty( self ) ); \
    self->_top -= 1; \
} \
\
element_type top_##suffix( struct stack_##suffix *self ) \
{ \
    assert( !self->is_empty( self ) ); \
    return self->_data[self->_top - 1]; \
} \
\
struct stack_##suffix *get_stack_object_##suffix( void ) \
{ \
    struct stack_##suffix *ret; \
    \
    ret = (struct stack_##suffix *) malloc( sizeof( struct stack_##suffix ) ); \
    assert( ret ); \
    ret->_data = ( element_type *) malloc( sizeof( element_type ) * INITIAL_SIZE ); \
    assert( ret->_data ); \
    ret->_size = INITIAL_SIZE; \
    ret->_top = 0; \
    ret->is_empty = is_empty_##suffix; \
    ret->is_full = is_full_##suffix; \
    ret->push = push_##suffix; \
    ret->pop = pop_##suffix; \
    ret->top = top_##suffix; \
    \
    return ret; \
} \
void destroy_stack_object_##suffix( struct stack_##suffix *p ) \
{ \
    free( p ); \
}

#define GENERIC_DYNAMIC_STACK_OBJ( suffix ) get_stack_object_##suffix()
#define DESTROY_DYNAMIC_STACK_OBJ( suffix, p ) destroy_stack_object_##suffix( p )