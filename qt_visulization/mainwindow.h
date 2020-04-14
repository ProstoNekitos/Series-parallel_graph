#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDockWidget>
#include <QStatusBar>
#include <QMenuBar>
#include <QAction>

#include <QFileDialog>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>

#include <QFile>
#include <QTextStream>

#include "shapes/TextInEllipse.h"
#include "shapes/Helix.h"

#include "custTreeItem.h" //kill me
#include "drawWidget.h"
#include "nodeSelWidget.h"
#include "newGraphDialog.h"

#include <typeinfo>
#include <algorithm>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void setToolBar();
    void setMenu();

    QGroupBox* setGraphBox(QWidget* parent);
    QGroupBox* setNodeBox(QWidget* parent);

    ~MainWindow();
private:
    void update();
    void fillQTree();

private:
    QDockWidget* right;
    QWidget* rmain;

    QStatusBar* statusBar;
    QMenuBar* menu;

    QTreeWidget* tree;
    NewGraphDialog* ngd;
    Shaape* current;
    NodeSelWidget* infoNode;
    QGroupBox* nodeBlock;
    drawWidget* drawer;

    std::vector<SPGraph<Shaape*>*> graphs;

private:
    void exportShape(QTextStream& out, Shaape* sh);
    Node<Shaape*>* parseToNode(QTextStream& in, std::vector< std::pair< std::vector<size_t>, std::vector<size_t> > >& con);

    void makeConnections(std::vector<Node<Shaape*>*>& data, std::vector< std::pair< std::vector<size_t>, std::vector<size_t> > >& con);

public slots:
    void parallelMerge();
    void consequtiveMerge();

    void graphDelete();
    void graphAdd();

    void nodeDelete();
    void nodeSet();
    void nodeInfo();

    void imp();
    void exp();
};

#endif // MAINWINDOW_H
