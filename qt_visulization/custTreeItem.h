#ifndef SPGRAPHQTREEITEM_H
#define SPGRAPHQTREEITEM_H

#include <QTreeWidgetItem>
#include <SPGraph/SPGraph.h>

template <class T>
class SPGraphQTreeItem : public QTreeWidgetItem
{
public:
    SPGraphQTreeItem(SPGraph<T>* gr, size_t i, std::vector<Node<T>*> n)
        : QTreeWidgetItem({ QString("%1").arg(i) }), graph(gr), nodes(n)
    {
        QVariant v;
        v.setValue(graph->size());
        this->setData(1, Qt::DisplayRole, v);
    }
    SPGraph<T>* graph;
    std::vector<Node<T>*> nodes;
};

#endif // SPGRAPHQTREEITEM_H
