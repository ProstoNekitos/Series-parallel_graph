#ifndef SPGRAPH_GR_H
#define SPGRAPH_GR_H

#include <SPGraph/SPGraph.h>

class SPGraph_gr : public SPGraph
{
    SPGraph();
    SPGraph(const T& src, const T& trm);

    SPGraph(const SPGraph& other);
    SPGraph(SPGraph&& other) noexcept;
    ~SPGraph();

    SPGraph& operator=(const SPGraph& other);
    SPGraph& operator=(SPGraph&& other) noexcept ;
public:
    SPGraph_gr();
};

#endif // SPGRAPH_GR_H
