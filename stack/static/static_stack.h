#include <assert.h>
#include <stdlib.h>

#define GENERIC_STATIC_STACK_STRUCT( element_type, suffix, stack_size ) \
    struct stack_##suffix{                                                \
        int     size;                                                   \
        int     index;\
        element_type data[stack_size];\
        int (*is_empty)( struct stack_##suffix *self );\
        int (*is_full)( struct stack_##suffix *self );\
        void (*push)( struct stack_##suffix *self, element_type e );\
        void (*pop)( struct stack_##suffix *self );   \
        element_type (*top)( struct stack_##suffix *self);\  
    }
                                                        
#define GENERIC_STATIC_STACK_METHOD( element_type, suffix, stack_size )\
int is_empty_##suffix( struct stack_##suffix *self )\
{\
    return self->index == -1;\
}\
\
int is_full_##suffix( struct stack_##suffix *self )\
{\
    return self->index + 1 == self->size;\
}\
\
void push_##suffix( struct stack_##suffix *self, element_type e )\
{\
    assert( !self->is_full( self ) );\
    self->data[++(self->index)] = e;\
}\
\
void pop_##suffix( struct stack_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    self->index -= 1;\
}\
\
element_type top_##suffix( struct stack_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    return self->data[(self->index)--];\
}\
\
struct stack_##suffix *get_object_##suffix( void ) \
{\
    struct stack_##suffix *ret = malloc( sizeof( struct stack_##suffix ) );\
    if( ret == NULL )\
        return NULL;\
    ret->size = stack_size;\
    ret->index = -1;\
    ret->is_empty = is_empty_##suffix;\
    ret->is_full = is_full_##suffix;\
    ret->push = push_##suffix;\
    ret->pop = pop_##suffix;\
    ret->top = top_##suffix;\
    return ret;\
}

#define GENERIC_STATIC_STACK_OBJECT get_object_##suffix()