#include <stdlib.h>
#include <string.h>

typedef int index_type;

#define GENERIC_STATIC_BST_STRUCT( element_type, suffix, bst_size ) \
struct bst_##suffix \
{ \
    element_type _nodes[bst_size]; \
    char _check_node[bst_size * 2]; \
    int _size; \
    index_type (*insert)( struct bst_##suffix *self, element_type e ); \
    index_type (*remove)( struct bst_##suffix *self, element_type e ); \
    void (*pre_traversal)( struct bst_##suffix *self, index_type i, void(*func_for_e)(element_type*) ); \
    void (*mid_traversal)( struct bst_##suffix *self, index_type i, void (*func_for_e)(element_type*) ); \
    void (*post_traversal)( struct bst_##suffix *self, index_type i, void (*func_for_e)(element_type*) ); \
    void (*bf_traversal)( struct bst_##suffix *self,  index_type i, void (*func_for_e)(element_type*) ); \
    index_type (*find)( struct bst_##suffix *self, element_type e ); \
    int (*_comparison)( void *, void * ); \
}

#define GENERIC_STATIC_BST_METHOD( element_type, suffix, bst_size ) \
index_type insert_##suffix( struct bst_##suffix *self, element_type e )\
{\
    int res; \
    index_type cur = 0; /* root */ \
    while( self->_check_node[cur] ) \
    { \
        res = self->_comparison( self->_nodes + cur, &e ); \
        if( res < 0 ) \
            cur = cur * 2 + 2; \
        else if( res > 0 ) \
            cur = cur * 2 + 1; \
        else \
            return -1; \
    } \
    self->_nodes[cur] = e; \
    self->_check_node[cur] = 1; \
    return cur; \
}\
\
index_type find_##suffix( struct bst_##suffix *self, element_type e ) \
{ \
    int res; \
    index_type cur = 0; \
    while( self->_check_node[cur] )\
    { \
        res = self->_comparison( self->_nodes + cur, &e ); \
        if( res < 0 ) \
            cur = cur * 2 + 2; \
        else if( res > 0 ) \
            cur = cur * 2 + 1; \
        else \
            return cur; \
    } \
    return -1; \
}\
\
void pre_traversal_##suffix( struct bst_##suffix *self, index_type i, void(* func_for_e)(element_type *) ) \
{ \
    int top = 0; \
    index_type tmp_stack[bst_size]; \
    \
    while( top || self->_check_node[i] ) \
    { \
        if( self->_check_node[i] ) \
        { \
            func_for_e( self->_nodes + i ); \
            tmp_stack[top++] = i; \
            i = i * 2 + 1; \
        } \
        else \
        { \
            i = tmp_stack[--top]; \
            i = i * 2 + 2; \
        } \
    } \
}\
\
void mid_traversal_##suffix( struct bst_##suffix *self, index_type i, void(* func_for_e)(element_type *) ) \
{ \
    int top = 0; \
    int tmp_stack[bst_size]; \
    \
    while( self->_check_node[i] || top ) \
    { \
        if( self->_check_node[i] ) \
        { \
            tmp_stack[top++] = i; \
            i = i * 2 + 1; \
        } \
        else \
        { \
            i = tmp_stack[--top]; \
            func_for_e( self->_nodes + i ); \
            i = i * 2 + 2; \
        } \
    } \
} \
\
void post_traversal_##suffix( struct bst_##suffix *self, index_type i, void(* func_for_e)(element_type *) ) \
{ \
    int top = 0; \
    index_type tmp_stack[bst_size]; \
    index_type prev = 0; \
    \
    while( top || self->_check_node[i] ) \
    { \
        if( self->_check_node[i] ) \
        { \
            tmp_stack[top++] = i; \
            i = i * 2 + 1; \
        } \
        else \
        { \
            i = tmp_stack[--top]; \
            if( !self->_check_node[i * 2 + 2] || i * 2 + 2 == prev ) \
            { \
                func_for_e( self->_nodes + i ); \
                prev = i; \
                i = bst_size * 2 - 1; \
            } \
            else \
            { \
                tmp_stack[top++] = i; \
                i = i * 2 + 2; \
            } \
        } \
    } \
} \
\
index_type remove_##suffix( struct bst_##suffix *self, element_type e ) \
{ \
    index_type cur = 0; \
    index_type node; \
    int res; \
    while( self->_check_node[cur] ) \
    { \
        res = self->_comparison( self->_nodes + cur, &e ); \
        if( res == 0 ) \
        { \
            if( !self->_check_node[cur * 2 + 1] && !self->_check_node[cur * 2 + 2] )/* no more son nodes*/ \
                self->_check_node[cur] = 0; \
            else if( self->_check_node[cur * 2 + 2] ) /* Only right son node */\
            { \
                node = cur * 2 + 2; \
                /* minimum value of right subtree */\
                while( self->_check_node[node * 2 + 1] ) \
                    node = node * 2 + 1; \
                self->_nodes[cur] = self->_nodes[node]; \
                self->_check_node[node] = 0; \
            } \
            else /* has left subtree or both */ \
            { \
                node = cur * 2 + 1; \
                /* maximum value of left subtree */\
                while( self->_check_node[node * 2 + 2] ) \
                    node = node * 2 + 2; \
                self->_nodes[cur] = self->_nodes[node]; \
                self->_check_node[node] = 0; \
            } \
            return cur; \
        } \
        else if( res > 0 ) \
            cur = cur * 2 + 1; \
        else \
            cur = cur * 2 + 2; \
    }\
    return -1; \
} \
\
struct bst_##suffix *get_static_bst_##suffix( int( *cmp )( void *a, void *b ) ) \
{ \
    struct bst_##suffix *ret = malloc( sizeof( struct bst_##suffix ) ); \
    \
    memset( ret->_check_node, 0, sizeof( char ) * bst_size * 2); \
    ret->_size = bst_size; \
    ret->_comparison = cmp; \
    ret->insert = insert_##suffix; \
    ret->find = find_##suffix; \
    ret->pre_traversal = pre_traversal_##suffix; \
    ret->mid_traversal = mid_traversal_##suffix; \
    ret->post_traversal = post_traversal_##suffix; \
    ret->remove = remove_##suffix; \
    \
    return ret; \
} \
\
void destroy_static_bst_##suffix( struct bst_##suffix *p ) \
{ \
    free( p ); \
}

#define GENERIC_STATIC_BST_OBJ( suffix, cmp ) get_static_bst_##suffix( cmp ) 
#define DESTROY_STATIC_BST_OBJ( p, suffix ) destroy_static_bst_##suffix( p )