#ifndef LIST_H
#define LIST_H

#include <iostream>

template<typename type>
struct Node{
    type value;
    Node* next;
    Node* prevous;
};

template<typename type>
class List
{
private:
    int size;
    Node<type> *head;
    Node<type> *tail;

public:
    List();
    List(const List &list);
    ~List();
    bool Empty();
    void Append(type _value);
    void Delete(Node<type> *node);
    Node<type>* Head();
    Node<type>* Tail();
    int Size();

    List<type> &operator=(const List<type> &right);
};

template<typename type>
List<type>::List(){
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename type>
List<type>::List(const List &list){
    head = nullptr;
    tail = nullptr;
    size = 0;
    Node<type> *node = list.head;
    while (node != nullptr){
        Append(node->value);
        node = node->next;
    }
}
template<typename type>
List<type> &List<type>::operator=(const List<type> &right){
    Delete(head);
    Node<type> *node = right.head;
    while (node != nullptr){
        Append(node->value);
        node = node->next;
    }
    return *this;
}

template<typename type>
List<type>::~List(){
    Node<type> *node = tail;
    while (node != nullptr){
        Node<type> *sup_node = node;
        node = node->prevous;
        if (sup_node){
            delete sup_node;
        }
    }
}

template<typename type>
bool List<type>::Empty(){
    return head == nullptr;
}

template<typename type>
int List<type>::Size(){
    return size;
}

template<typename type>
Node<type> *List<type>::Head(){
    return head;
}

template<typename type>
Node<type> *List<type>::Tail(){
    return tail;
}

template<typename type>
void List<type>::Append(type _value){
    Node<type> *node = new Node<type>;
    node->value = _value;
    if (size == 0){
        head = node;
        tail = node;

        node->next    = nullptr;
        node->prevous = nullptr;
        size++;
    }
    else{
        node->next = nullptr;
        node->prevous = tail;
        tail->next = node;
        tail = node;
        size++;
    }
}

template<typename type>
void List<type>::Delete(Node<type> *node)
{
    if (!node){
        return;
    }
    Node<type> *sup_node = head;
    while (sup_node != nullptr){
        if (sup_node == node){
            break;
        }
        sup_node = sup_node->next;
    }
    if (sup_node == nullptr) return;
    else{
        if (node->prevous)
            node->prevous->next = node->next;

        if (node->next){
            node->next->prevous = node->prevous;
        }
        if (node == head){
            head = node->next;
        }
        if (node == tail){
            tail = node->prevous;
        }
        delete node;
        size--;
    }
}


#endif // LIST_H
