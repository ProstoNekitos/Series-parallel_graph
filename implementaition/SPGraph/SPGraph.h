#ifndef SPGRAPH_SPGRAPH_H
#define SPGRAPH_SPGRAPH_H

#include <cstddef>
#include <vector>
#include <algorithm>

#include "SPiterator.h"
#include "SPException.h"



template <class T>
class SPGraph {
    typedef bool (*comparator)(const T& left, const T& right);
public:
    SPGraph();
    SPGraph(const T& src, const T& trm);

    SPGraph(const SPGraph& other);
    SPGraph(SPGraph&& other) noexcept;
    ~SPGraph();

    SPGraph& operator=(const SPGraph& other);
    SPGraph& operator=(SPGraph&& other) noexcept ;

    void parallelComposition(const SPGraph &other);

    void seriesComposition(const SPGraph& other);
    void seriesComposition(const T& src, const T& term);

    ///////////////////////
    SPiterator<T> pop(const SPiterator<T>& it);
    void set(SPiterator<T>& it, const T& data);
    void setComparator(comparator c);


    Node<T>* depthFirstDecompose(Node<T>* start, std::vector<Node<T>*>& array) const;
    std::vector<Node<T>*> getDeepCopy() const;

    SPiterator<T> begin();
    SPiterator<T> end();

    size_t size();

private:
    void clear();

private:

    Node<T>* source;
    Node<T>* terminal;
    size_t capacity = 2;
    bool (*comp)(const T& l, const T& r) = nullptr;
};

//Constructors
template<class T>
SPGraph<T>::SPGraph() : SPGraph(T(), T()) {}

template<class T>
SPGraph<T>::SPGraph(const T &src, const T &trm) {
    source = new Node<T>(src);
    terminal = new Node<T>(trm);
    capacity = 2;

    source->childs.emplace_back(terminal);
    terminal->parents.emplace_back(source);
}

template<class T>
SPGraph<T>::SPGraph(const SPGraph &other) {
    std::vector<Node<T>*> array = other.getDeepCopy();
    source = array.front();
    terminal = array.back();
    capacity = array.size();
}

template<class T>
SPGraph<T>::SPGraph(SPGraph &&other) noexcept
: terminal(std::move(other.terminal)), source(std::move(other.source)), capacity(std::move(capacity)){}

template<class T>
SPGraph<T>::~SPGraph() {
    clear();
}
////////////////////

//Operators
template<class T>
SPGraph<T> &SPGraph<T>::operator=(const SPGraph &other) {
    clear();
    std::vector<Node<T>*> decomp = other.getDeepCopy();
    source = decomp.front();
    terminal = decomp.back();
    capacity = decomp.size();
    return *this;
}

template<class T>
SPGraph<T> &SPGraph<T>::operator=(SPGraph &&other) noexcept {
    clear();
    source = std::move(other.source);
    terminal = std::move(other.terminal);
    capacity = std::move(other.capacity);
    return *this;
}
////////////////////


//Composition operations
template<class T>
void SPGraph<T>::parallelComposition(const SPGraph &other){
    if( comp )
    {
        if( !comp(*this->source->data, *other.source->data) )
        {
            SPInvalidComposition<T> exc( "Graph sources are different", this, &other,
                    SPInvalidComposition<T>::opType::Parallel,
                    SPInvalidComposition<T>::nodeType::Source);
            throw( exc );
        }
        if( !comp(*this->terminal->data, *other.terminal->data) )
        {
            SPInvalidComposition<T> exc( "Graph terminals are different", this, &other,
                    SPInvalidComposition<T>::opType::Parallel,
                    SPInvalidComposition<T>::nodeType::Terminal);
            throw( exc );
        }
    }
    else
    {
        if( *this->source->data != *other.source->data )
        {
            SPInvalidComposition<T> exc( "Graph sources are different", this, &other,
                    SPInvalidComposition<T>::opType::Parallel,
                    SPInvalidComposition<T>::nodeType::Source);
            throw( exc );
        }
        if( *this->terminal->data != *other.terminal->data ) {
            SPInvalidComposition<T> exc("Graph sources are different", this, &other,
                                        SPInvalidComposition<T>::opType::Parallel,
                                        SPInvalidComposition<T>::nodeType::Terminal);
            throw (exc);
        }
    }


    std::vector<Node<T>*> otherDec = other.getDeepCopy();

    //changing parent on a new children
    for( auto& child : otherDec.front()->childs )
    {
        child->parents.clear();
        child->parents.push_back(source);
    }

    //merge sources children
    source->childs.insert(source->childs.end(), otherDec.front()->childs.begin(), otherDec.front()->childs.end());
    delete otherDec.front();

    //changing parent on the old terminal
    for( auto& parent : otherDec.back()->parents )
    {
        parent->childs.clear();
        parent->childs.push_back(terminal);
    }

    //add children to this source
    terminal->parents.insert(terminal->parents.end(), otherDec.back()->parents.begin(), otherDec.back()->parents.end());
    delete otherDec.back();

    capacity += otherDec.size() - 2; //except for src and term

}

template<class T>
void SPGraph<T>::seriesComposition(const SPGraph &other) {
    std::vector<Node<T>*> otherDecomp = other.getDeepCopy();

    //insert new parent for source childs
    for( auto& child : otherDecomp.front()->childs )
    {
        child->parents.clear();
        child->parents.push_back(terminal);
    }

    //insert childs
    terminal->childs.insert(terminal->childs.end(), otherDecomp.front()->childs.begin(), otherDecomp.front()->childs.end());
    capacity += otherDecomp.size() - 1; //except for source

    terminal = otherDecomp.back();
    delete otherDecomp.front();

}

template<class T>
void SPGraph<T>::seriesComposition(const T& src, const T& term) {
    seriesComposition(SPGraph(src, term));
}
///////////////////

//Data change
template<class T>
void SPGraph<T>::clear() {
    std::vector<Node<T>*> nodes;
    depthFirstDecompose(source, nodes);
    for( auto n : nodes )
        delete n;
}

template<class T>
SPiterator<T> SPGraph<T>::pop(const SPiterator<T>& it) {
    if( size() < 3 )
        throw SPException<T>("2-node graph", this);

    //Handling src & sink
    if( it == begin() )
    {
        if( source->childs.size() > 1 )
            throw SPException<T>("Multiple childs", this);
        else
        {
            Node<T>* oldSource = source;
            source = source->childs.front();
            delete oldSource;

            std::vector<Node<T> *> decompose;
            this->depthFirstDecompose(this->source, decompose);

            return SPiterator<T>(source, decompose);
        }
    }

    if( it == end() )
    {
        if( terminal->parents.size() > 1 )
            throw SPException<T>("Multiple parents", this);
        else
        {
            Node<T>* oldTerminal = terminal;
            terminal = terminal->parents.front();
            delete oldTerminal;

            std::vector<Node<T> *> decompose;
            this->depthFirstDecompose(this->source, decompose);

            return SPiterator<T>(terminal, decompose);
        }
    }

    //Parents of it to children of it
    for( auto* p : it.node->parents )
    {
        p->childs.erase(std::remove(p->childs.begin(), p->childs.end(), it.node), p->childs.end()); //remove this node from parents child array
        p->childs.insert(p->childs.end(), it.node->childs.begin(), it.node->childs.end());
    }
    //children of it to parents of it
    for( auto* ch : it.node->childs )
    {
        ch->parents.erase(std::remove(ch->parents.begin(), ch->parents.end(), it.node), ch->parents.end()); //remove this node from childs parrent array
        ch->parents.insert( ch->parents.end(), it.node->parents.begin(), it.node->parents.end() );
    }

    std::vector<Node<T> *> decompose;
    this->depthFirstDecompose(this->source, decompose);

    //returns iterator to first child of deleted node
    SPiterator<T> firstCh(*it.node->childs.begin(), decompose);
    delete it.node;

    return firstCh;
}

template<class T>
void SPGraph<T>::set(SPiterator<T> &it, const T &data) {
    it.node->data = data;
}

template<class T>
void SPGraph<T>::setComparator(SPGraph::comparator c) {
    comp = c;
}
////////////////////

//Data representation
template<class T>
Node<T> *SPGraph<T>::depthFirstDecompose(Node<T> *start, std::vector<Node<T> *>& array) const {
    if( std::find(array.begin(), array.end(), start) == array.end() )
        array.push_back(start);
    for (auto& node : start->childs)
    {
        depthFirstDecompose(node, array);
    }
    return start;
}

template<class T>
std::vector<Node<T> *> SPGraph<T>::getDeepCopy() const {
    std::vector<Node<T> *> decompose;
    this->depthFirstDecompose(this->source, decompose);

    std::vector<Node<T> *> copyDecompose;

    size_t srcPos = std::find(decompose.begin(), decompose.end(), this->source) - decompose.begin();
    size_t termPos = std::find(decompose.begin(), decompose.end(), this->terminal) - decompose.begin();

    //Copying deep copy other's decompose
    for (size_t i = 0; i < decompose.size(); ++i) {
        copyDecompose.emplace_back(new Node<T>(*decompose[i]->data));
    }

    //Making connections
    //На английском сложно, напишу так
    /*В каждом массиве порядок элементов один и тот же,
     * значит для каждого i-ой ноды мы можем узнать индексы её родителей и детей в том же массиве
     * убейте меня*/

    for (size_t i = 0; i < decompose.size(); ++i) {
        for (auto& parent : decompose[i]->parents) {
            size_t parentIndex = std::find(decompose.begin(), decompose.end(), parent) - decompose.begin();
            copyDecompose[i]->parents.emplace_back(copyDecompose[parentIndex]);
        }

        for (auto& child : decompose[i]->childs) {
            size_t childIndex = std::find(decompose.begin(), decompose.end(), child) - decompose.begin();
            copyDecompose[i]->childs.emplace_back(copyDecompose[childIndex]);
        }
    }

    //make src first, terminal last
    std::swap(copyDecompose[srcPos], copyDecompose.front());
    std::swap(copyDecompose[termPos], copyDecompose.back());

    return copyDecompose;
}
//////////////////////

//Basics
template<class T>
SPiterator<T> SPGraph<T>::begin() {
    std::vector<Node<T> *> decompose;
    this->depthFirstDecompose(this->source, decompose);

    return SPiterator<T>(source, decompose);
}

template<class T>
SPiterator<T> SPGraph<T>::end() {
    std::vector<Node<T> *> decompose;
    this->depthFirstDecompose(this->source, decompose);

    return SPiterator(terminal, decompose);
}

template<class T>
size_t SPGraph<T>::size() {
    return capacity;
}
///////////////
#endif //SPGRAPH_SPGRAPH_H
