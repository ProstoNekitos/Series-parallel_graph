#ifndef SPGRAPH__H
#define SPGRAPH__H

#include <SPGraph/SPGraph.h>

template <class T>
class SPGraph_ : SPGraph<T>
{
public:
    SPGraph_(const T& src, const T& trm);
    size_t width;
};

#endif // SPGRAPH__H
