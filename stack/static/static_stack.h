#include <assert.h>

#define GENERIC_STATIC_STACK_STRUCT( element_type, suffix, stack_size )\
    struct stack_##suffix{\
        int     _size;\
        int     _index;\
        element_type _data[stack_size];\
        int (*is_empty)( struct stack_##suffix *self );\
        int (*is_full)( struct stack_##suffix *self );\
        void (*push)( struct stack_##suffix *self, element_type e );\
        void (*pop)( struct stack_##suffix *self );\
        element_type (*top)( struct stack_##suffix *self);\
    }
                                                        
#define GENERIC_STATIC_STACK_METHOD( element_type, suffix, stack_size )\
int is_empty_##suffix( struct stack_##suffix *self )\
{\
    return self->_index == -1;\
}\
\
int is_full_##suffix( struct stack_##suffix *self )\
{\
    return self->_index + 1 == self->_size;\
}\
\
void push_##suffix( struct stack_##suffix *self, element_type e )\
{\
    assert( !self->is_full( self ) );\
    self->_data[++(self->_index)] = e;\
}\
\
void pop_##suffix( struct stack_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    self->_index -= 1;\
}\
\
element_type top_##suffix( struct stack_##suffix *self )\
{\
    assert( !self->is_empty( self ) );\
    return self->_data[(self->_index)--];\
}\
\
void get_object_##suffix( struct stack_##suffix *p ) \
{\
    if( p == NULL )\
        return; \
    p->_size = stack_size;\
    p->_index = -1;\
    p->is_empty = is_empty_##suffix;\
    p->is_full = is_full_##suffix;\
    p->push = push_##suffix;\
    p->pop = pop_##suffix;\
    p->top = top_##suffix;\
}\

#define GENERIC_STATIC_STACK_OBJ( suffix, p ) get_object_##suffix( p )