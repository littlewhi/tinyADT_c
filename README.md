This is a ADT(abstract data structure) library in which now there are **Stack**, **Queue** and **Binary Search Tree**.
This library is inspired by the chapter 17th of the book "Pointers on C". I make a fusion of the micro usages in C and OOP to build a little library.
There are test codes for usages in case that I cannot explain well it.
1. **Stack**
    1. _Static Stack_
        This type _stack_ is completed by static way in which the data area is a array whose capacity is determined by usage of micro of `GENERIC_STATIC_STACK_STRUCT`.
        The micro `GENERIC_STATIC_STACK_STRUCT(element_type, suffix, stack_size)` is to define the structure of certain stack you want. The `element_type` is the type of what the stack can contain. The `suffix` is to combine the name of the stack structure--`struct stack_##suffix`. Important one is that the `suffix` is the key of keeping clean namespace. And the `stack_size` is the number of array's units.
        The micro `GENERIC_STATIC_STACK_METHOD(element_type, suffix, stack_size)` is to define the method that will be called to operate the stack. The arguments is the same as the before.
        The micro `GENERIC_STATIC_STACK_OBJ(suffix, p)` is get a specific stack which is declared from the those two micros. The argument `p` is the pointer which we will instantiate. The micro will not allocate any memory for the pointer due to the name 'static'.
2. **Queue**
    1. _Static Queue_
        This type _queue_ is completed by static way in which the data area is a array whose capacity is determined by usage of micro `GENERIC_STATIC_QUEUE_STRUCT`. And its full check and empty check use circular queue methods. Its interfaces are similar to static stack, so I don't think that it needs more bla bla.
3. **BST**
    1. _Static BST_
        Its interfaces look like the brothers of static queue and static stack. But I want to make sure some details for users.
        Because its data area is an array. So the argument `bst_size` in `GENERIC_STATIC_BST_STRUCT` will need more attention. You must calculate well the the most index of the nodes in the horizontal arrangement, or it will cause some undefined behaviors.