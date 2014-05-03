#ifndef CIRCULAR_LINKED_LIST_H
#define CIRCULAR_LINKED_LIST_H

template <class T>
class CircularLinkedList
{
private:
    struct Node
    {
        T data;
        Node *link;
    };
    typedef struct Node Node;
    Node *nodePointer;
    
    int mySize;

public:
    CircularLinkedList();
    
    void add(T);
    void addAfter(T target, T newData);
    const T look();
    void next();
    
    int size();

    ~CircularLinkedList();

};

template <class T>
inline CircularLinkedList<T>::CircularLinkedList() : nodePointer(nullptr) {}

template <class T>
inline void CircularLinkedList<T>::add(T newData)
{
    Node *newNode = new Node;
    newNode->data = newData;

    if(!nodePointer)  // Empty list situation
    {
        newNode->link = newNode;  // Link to itself
        nodePointer = newNode;
    }
    else
    {
        newNode->link = nodePointer;
        while(newNode->link->link != nodePointer)
            newNode->link = newNode->link->link;
        newNode->link->link = newNode;
        newNode->link = nodePointer;
    }
    
    mySize++;
}

template <class T>
inline void CircularLinkedList<T>::addAfter(T target, T newData)
{
    Node *newNode = new Node;
    newNode->data = newData;

    Node *falseNodePointer = nodePointer;

    while(falseNodePointer->data != target)
        falseNodePointer = falseNodePointer->link;
    
    newNode->link = falseNodePointer->link;
    falseNodePointer->link = newNode;
    
    mySize++;
}

template <class T>
inline const T CircularLinkedList<T>::look()
{
    return nodePointer->data;
}

template <class T>
inline void CircularLinkedList<T>::next()
{
    nodePointer = nodePointer->link;
}

template <class T>
inline int CircularLinkedList<T>::size()
{
    return mySize;
}

template <class T>
inline CircularLinkedList<T>::~CircularLinkedList()
{
    if(!nodePointer) return;
    
    Node *tmpNode = nodePointer->link;
    Node *suicidalNode;
    Node *safeNode;
    while(tmpNode != nodePointer)
    {
        suicidalNode = tmpNode;
        safeNode = tmpNode->link;
        delete suicidalNode;
        tmpNode = safeNode;
    }
    delete nodePointer;
}

#endif  // CIRCULAR_LINKED_LIST_H
