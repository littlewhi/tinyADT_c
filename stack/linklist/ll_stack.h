#include <stdlib.h>
#include <assert.h>

#define GENERIC_LL_STACK_STRUCT( element_type, suffix ) \
struct stack_node_##suffix \
{ \
    element_type data; \
    struct stack_node_##suffix *next; \
}; \
struct stack_##suffix \
{ \
    struct stack_node_##suffix *_top; \
    int _size; \
    \
    int (*is_empty)( struct stack_##suffix *self ); \
    void (*push)( struct stack_##suffix *self, element_type e ); \
    void (*pop)( struct stack_##suffix *self ); \
    element_type (*top)( struct stack_##suffix *self ); \
}

#define GENERIC_LL_STACK_METHOD( element_type, suffix ) \
int is_empty_##suffix( struct stack_##suffix *self ) \
{ \
    return self->_top == NULL; \
} \
\
void push_##suffix( struct stack_##suffix *self, element_type e ) \
{ \
    struct stack_node_##suffix *tmp = (struct stack_node_##suffix *) malloc( sizeof( struct stack_node_##suffix ) ); \
    if( !tmp ) \
        return; \
    tmp->data = e; \
    tmp->next = self->_top; \
    self->_top = tmp; \
} \
element_type top_##suffix( struct stack_##suffix *self ) \
{ \
    assert( self->_top ); \
    return self->_top->data; \
} \
\
void pop_##suffix( struct stack_##suffix *self ) \
{ \
    struct stack_node_##suffix *tmp = NULL; \
    assert( self->_top ); \
    tmp = self->_top; \
    self->_top = tmp->next; \
    free( tmp ); \
} \
\
struct stack_##suffix *get_stack_obj_##suffix( void ) \
{ \
    struct stack_##suffix *ret = NULL; \
    ret = (struct stack_##suffix *) malloc( sizeof( struct stack_##suffix ) ); \
    if( !ret ) \
        return NULL; \
    \
    ret->_size = 0; \
    ret->_top = NULL; \
    \
    ret->is_empty = is_empty_##suffix; \
    ret->push = push_##suffix; \
    ret->top = top_##suffix; \
    ret->pop = pop_##suffix; \
    return ret; \
} \
\
void destroy_stack_obj_##suffix( struct stack_##suffix *p ) \
{ \
    struct stack_node_##suffix *tmp = NULL; \
    assert( p ); \
    if( !p->_top ) \
    { \
        free( p ); \
        return; \
    } \
    while( p->_top ) \
    { \
       tmp = p->_top; \
       p->_top = tmp->next; \
       free( tmp ); \
    } \
    free( p ); \
} 

#define GENERIC_LL_STACK_OBJ( suffix ) get_stack_obj_##suffix()
#define DESTROY_LL_STACK_OBJ( p, suffix ) destroy_stack_obj_##suffix( p )