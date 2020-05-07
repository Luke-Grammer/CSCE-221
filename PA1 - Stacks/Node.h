#ifndef NODE
#define NODE

//Simple templated node struct with a data member of type T and a pointer to the next node.
template<class T>
struct Node {
	T data;
	Node<T>* next;
};

#endif
