#ifndef SPGRAPH_SPITERATOR_H
#define SPGRAPH_SPITERATOR_H

#include <vector>
#include <iostream>

#include "SPException.h"

template <class T>
class Node
{
public:
    Node();
    explicit Node(const T& d);
    ~Node();

    Node(Node& other);
    Node(Node&& other) noexcept;

    Node& operator=(const Node& other);
    Node& operator=(Node&& other) noexcept;

    T* data = nullptr;
    std::vector<Node*> parents;
    std::vector<Node*> childs;
};

template<class T>
Node<T>::Node()
{
    data = nullptr;
}

template <class T>
Node<T>::Node(const T &d)
{
    data = new T(d);
}

template<class T>
Node<T>::~Node()
{
    delete data;
};

template<class T>
Node<T>::Node(Node &other)
{
    data = other.data;
    parents = other.parents;
    childs = other.childs;
}

template<class T>
Node<T>::Node(Node &&other) noexcept
{
    data = std::move(other.data);
    parents = std::move(other.parents);
    childs = std::move(other.childs);
}

template<class T>
Node<T> &Node<T>::operator=(const Node &other) {
    data = other.data;
    childs = other.childs;
    parents = other.parents;
    return *this;
}

template<class T>
Node<T> &Node<T>::operator=(Node &&other) noexcept{
    data(std::move(other.data));
    childs(std::move(other.childs));
    parents(std::move(other.parents));
    return *this;
}

//ITERATOR

template <class T>
class SPiterator
{
public:
    SPiterator(const SPiterator& other);
    explicit SPiterator(const Node<T>* n, std::vector<Node<T>*> dec);
    SPiterator(SPiterator&& other) noexcept ;
    ~SPiterator() = default;

    SPiterator& operator=(const SPiterator& other);
    SPiterator& operator=(SPiterator&& other) noexcept;
    bool operator==(const SPiterator& other) const;

    SPiterator& operator++(); //prefix
    const SPiterator operator++(int); //postfix
    T operator*() const;

    std::vector<Node<T>*> decomposition;
    Node<T>* node;
    size_t it = 0;
};


template<class T>
SPiterator<T>::SPiterator(const SPiterator &other) {
    node = other.node;
    decomposition = other.decomposition;
}

template<class T>
SPiterator<T>::SPiterator(SPiterator &&other) noexcept {
    node = std::move(other.node);
    decomposition = std::move(other.decomposition);
}

template<class T>
SPiterator<T>::SPiterator(const Node<T> *n, std::vector<Node<T>*> dec) {
    node = const_cast<Node<T>*>(n);
    decomposition = dec;
}

template<class T>
SPiterator<T> &SPiterator<T>::operator=(const SPiterator &other) {
    this->node = other.node;
    return *this;
}

template<class T>
SPiterator<T> &SPiterator<T>::operator=(SPiterator &&other) noexcept {
    this->node(std::move(other.node));
    return *this;
}

template<class T>
SPiterator<T> &SPiterator<T>::operator++() {
    ++it;
    return *this;
}

template<class T>
const SPiterator<T> SPiterator<T>::operator++(int) {
    SPiterator<T> copy(*this);
    ++it;
    return copy;
}

template<class T>
T SPiterator<T>::operator*() const {
    if( it > decomposition.size() - 1 )
        throw SPinvalidIt<T>("Iterator is out of bounds", this);
    return *decomposition[it]->data;
}

template<class T>
bool SPiterator<T>::operator==(const SPiterator &other) const {
    return other.node == this->node;
}

#endif //SPGRAPH_SPITERATOR_H
