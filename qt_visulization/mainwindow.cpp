#include "mainwindow.h"

bool compare(Shaape* const& left, Shaape* const& right)
{
    return left->getCentral().x == right->getCentral().x
            &&
           left->getCentral().y == right->getCentral().y;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    drawer = new drawWidget;
    drawer->setGraph(&graphs);
    this->setCentralWidget(drawer);

    statusBar = new QStatusBar;
    statusBar->setStyleSheet("color: red");
    this->setStatusBar(statusBar);

    menu = new QMenuBar;
    this->setMenuBar(menu);
    setMenu();

    ngd = new NewGraphDialog;

    setToolBar();

    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, right);
}

MainWindow::~MainWindow(){}

//UI SET
void MainWindow::setToolBar()
{
    right = new QDockWidget("Toolbar", this);
    rmain = new QWidget(this);
    QVBoxLayout* l = new QVBoxLayout;
    right->setWidget(rmain);
    rmain->setLayout(l);

    l->addWidget(setGraphBox(rmain));
    nodeBlock = setNodeBox(rmain);
    l->addWidget(nodeBlock);
    nodeBlock->hide();

    update();
}

void MainWindow::setMenu()
{
    QMenu* file = menu->addMenu("File");

    QAction* imp = new QAction("Import...");
    QAction* exp = new QAction("Export...");

    connect(imp, SIGNAL(triggered(bool)), this, SLOT(imp()));
    connect(exp, SIGNAL(triggered(bool)), this, SLOT(exp()));

    file->addAction(imp);
    file->addAction(exp);

    menu->addMenu(file);
}

QGroupBox* MainWindow::setGraphBox(QWidget* parent)
{
    QGroupBox* gb = new QGroupBox("Graph options", parent);
    QVBoxLayout* l = new QVBoxLayout;
    gb->setLayout(l);

    tree = new QTreeWidget(rmain);
    tree->setSelectionMode(QAbstractItemView::MultiSelection);
    QStringList colNames;
    colNames << "#" << "size" << "type";
    tree->setHeaderLabels(colNames);

    connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(nodeInfo()));

    QPushButton* add = new QPushButton("Add Graph", rmain);
    QPushButton* del = new QPushButton("Delete Graph", rmain);

    connect(del, SIGNAL(clicked(bool)), this, SLOT(graphDelete()));
    connect(add, SIGNAL(clicked(bool)), this, SLOT(graphAdd()));

    QPushButton* serM = new QPushButton("Series compostition", rmain);
    QPushButton* parM = new QPushButton("Parallel compostition", rmain);

    connect(serM, SIGNAL(clicked(bool)), this, SLOT(consequtiveMerge()));
    connect(parM, SIGNAL(clicked(bool)), this, SLOT(parallelMerge()));

    l->addWidget(tree);
    l->addWidget(add);
    l->addWidget(del);
    l->addWidget(serM);
    l->addWidget(parM);

    return gb;
}

QGroupBox* MainWindow::setNodeBox(QWidget* parent)
{
    QGroupBox* gb = new QGroupBox("Node options", parent);
    QVBoxLayout* l = new QVBoxLayout;
    gb->setLayout(l);

    infoNode = new NodeSelWidget;

    QPushButton* set = new QPushButton("Set", gb);
    QPushButton* del = new QPushButton("Delete", gb);

    connect(set, SIGNAL(clicked(bool)), this, SLOT(nodeSet()));
    connect(del, SIGNAL(clicked(bool)), this, SLOT(nodeDelete()));

    l->addWidget(infoNode);
    l->addWidget(set);
    l->addWidget(del);

    return gb;
}

//UPDATE FUNCTIONS
void MainWindow::update()
{
    fillQTree();
    drawer->drawGraphs();
}

void MainWindow::fillQTree()
{
    tree->clear();
    for( size_t i = 0; i < graphs.size(); ++i )
    {
        std::vector<Node<Shaape*>*> dec;
        graphs[i]->depthFirstDecompose(graphs[i]->begin().node, dec);

        SPGraphQTreeItem<Shaape*>* it = new SPGraphQTreeItem<Shaape*>(graphs[i], i, dec);

        for( size_t j = 0; j < dec.size(); ++j )
        {
            QTreeWidgetItem* ch = new QTreeWidgetItem(it);
            ch->setData(2, Qt::DisplayRole, QVariant( typeid(**dec[j]->data).name() ));
            QVariant v;
            v.setValue(j);
            ch->setData(0, Qt::DisplayRole, v);
            it->addChild( ch );
        }

        tree->addTopLevelItem(it);
    }
}

/*
 * Helix (H)
 * Mx My
 * Rad
 *
 * Tie (I)
 * ShiftX ShiftY
 * Text
 * Rad
 * Hrad
 *
 * Text (T)
 * text
 *
 * Ellipse (E)
 * vrad
 * hrad
 *
 * Circle (C)
 * Rad
 *
 * Shape (for all)
 * centX centY
 * colorR colorG colorB
 * rotation
 * scale
*/
void MainWindow::exportShape(QTextStream &out, Shaape *sh)
{
    /*Deriv info
            Tie
            / \
       hel el txt
         \ /
          crcl
     a little bit fucked up structure
     defenetly need exporter/importer class*/

    TextInEllipse* tie = dynamic_cast<TextInEllipse*>(sh);
    if( tie )
    {
        out << "I\n";
        out << QString("%1 %2\n")
               .arg(tie->getShift().x).arg(tie->getShift().y);
        out << QString::fromStdString(tie->getText() + '\n');
        out << QString("%1\n").arg(tie->getRad());
        out << QString("%1\n").arg(tie->getHorizontalRadius());
    }
    else
    {
        Text* t = dynamic_cast<Text*>(sh);
        if( t )
        {
            out <<  "T\n";
            out << QString::fromStdString(t->getText() + '\n');
        }

        Ellipse* e = dynamic_cast<Ellipse*>(sh);
        if( e )
        {
            out << QString("E\n");
            out << QString("%1\n").arg(e->getRad()); //circle
            out << QString("%1\n").arg(e->getHorizontalRadius()); //ellipse
        }
        else
        {
            Circle* c = dynamic_cast<Circle*>(sh);
            if( c && !dynamic_cast<Helix*>(sh) )
            {
                out << "C\n";
                out << QString("%1\n").arg(c->getRad());
            }
        }
    }

    Helix* h = dynamic_cast<Helix*>(sh);
    if( h ) //without circle
    {
        out << "H\n";
        out << QString("%1 %2\n")
               .arg(h->getM().x).arg(h->getM().y);
        out << QString("%1\n").arg(h->getRad());
    }

    //Shape info
    out << QString("%1 %2\n")
           .arg(sh->getCentral().x).arg(sh->getCentral().y);
    out << QString("%1 %2 %3\n")
           .arg(sh->getColor().r).arg(sh->getColor().g).arg(sh->getColor().b);
    out << QString("%1\n").arg(sh->getRotation());
    out << QString("%1\n").arg(sh->getScale());
}

//we assume that next line to read is type
Node<Shaape *> *MainWindow::parseToNode(QTextStream &in, std::vector< std::pair< std::vector<size_t>, std::vector<size_t> > >& con)
{
    QString line = in.readLine();
    Shaape* shape;
    switch ( line[0].toLatin1() ) {
    case 'H'://helix
    {
        Helix* h = new Helix;
        line = in.readLine();
        h->setM(Point{line.split(' ')[0].toFloat(), line.split(' ')[1].toFloat()});
        h->setRad(in.readLine().toFloat());
        shape = h;
        break;
    }
    case 'I'://TextInEllipse
    {
        TextInEllipse* tie = new TextInEllipse;
        line = in.readLine();
        tie->setShift(Point{line.split(' ')[0].toFloat(), line.split(' ')[1].toFloat()});
        tie->setText(in.readLine().toStdString());
        tie->setRad(in.readLine().toFloat());
        tie->setHorizontalRadius(in.readLine().toFloat());
        shape = tie;
        break;
    }
    case 'T'://Text
    {
        Text* t = new Text(in.readLine().toStdString());
        shape = t;
        break;
    }
    case 'E': //Ellipse
    {
        Ellipse* e = new Ellipse;
        e->setRad(in.readLine().toFloat());
        e->setHorizontalRadius(in.readLine().toFloat());
        shape = e;
        break;
    }
    case 'C': //Circle
    {
        Circle* c = new Circle;
        c->setRad(in.readLine().toFloat());
        shape = c;
        break;
    }
    default:
        break;
    }

    line = in.readLine(); //cent
    shape->move(Point{line.split(' ')[0].toFloat(), line.split(' ')[1].toFloat  ()});

    line = in.readLine(); //color
    shape->paint(Colour{line.split(' ')[0].toShort(), line.split(' ')[1].toShort(), line.split(' ')[2].toShort()});

    shape->rotate(in.readLine().toFloat()); //rotation
    shape->zoom(in.readLine().toFloat());

    std::vector<size_t> parents;
    line = in.readLine();
    if( line.size() > 0 )
        for( QString a : line.split(' ') )
        {
            if( a.size() > 0 )
                parents.push_back(a.toInt());
        }

    std::vector<size_t> childs;
    line = in.readLine();
    for( QString a : line.split(' ') )
    {
        if( a.size() > 0 )
            childs.push_back(a.toInt());
    }
    con.emplace_back(std::make_pair(parents, childs));
    return new Node<Shaape*>(shape);
}

void MainWindow::makeConnections(std::vector<Node<Shaape *> *> &data, std::vector<std::pair<std::vector<size_t>, std::vector<size_t> > > &con)
{
    for( size_t i = 0; i < data.size(); ++i ) //for every node
    {
        for( size_t j = 0; j < con[i].first.size(); ++j ) //for every p connection for this node
        {
            size_t indToAdd = con[i].first[j];
            data[i]->parents.push_back(data[indToAdd]);
        }
        for( size_t j = 0; j < con[i].second.size(); ++j ) //for every c connection for this node
        {
            size_t indToAdd = con[i].second[j];
            data[i]->childs.push_back(data[indToAdd]);
        }
    }
}

//SLOTS
void MainWindow::graphAdd()
{
    int code =  ngd->exec();
    if( code == QDialog::Accepted )
    {
        ngd->res->comp = compare;
        graphs.emplace_back(std::move(ngd->res));
        update();
    }
}

void MainWindow::graphDelete()
{
    QList<QTreeWidgetItem*> sel = tree->selectedItems();
    for( auto& a : sel )
    {
        if( !a->childCount() )
        {
            statusBar->showMessage("Wrong choice", 1500);
            return;
        }
        auto b = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(a)->graph;
        auto find = std::find(graphs.begin(), graphs.end(), b);
        if( find != graphs.end() )
        {
            delete *find;
            graphs.erase(find);
        }
    }
    update();
}

void MainWindow::nodeSet()
{
    QList<QTreeWidgetItem*> sel = tree->selectedItems();
    if( sel.size() > 2 ) return;
    infoNode->change();
    update();
}

void MainWindow::nodeInfo()
{
    QList<QTreeWidgetItem*> sel = tree->selectedItems();
    if( sel.size() > 2 || sel.empty() || sel[0]->childCount()  )
    {
        nodeBlock->hide();
        return;
    }

    nodeBlock->show();
    std::vector< Node<Shaape*>* > parent = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[0]->parent())->nodes;
    auto b = sel[0]->data(0, Qt::DisplayRole).value<size_t>();
    current = *parent[b]->data;
    infoNode->display(current);
}

void MainWindow::nodeDelete()
{
    QList<QTreeWidgetItem*> sel = tree->selectedItems();
    if( sel.size() > 2 || sel.empty() || sel[0]->childCount()  )
    {
        nodeBlock->hide();
        return;
    }

    std::vector< Node<Shaape*>* > parent = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[0]->parent())->nodes;
    auto b = sel[0]->data(0, Qt::DisplayRole).value<size_t>();
    current = *parent[b]->data;

    SPiterator<Shaape*> it(parent[b], parent);
    try{
        dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[0]->parent())->graph->pop(it);
    } catch ( SPException<Shaape*>& exc )
    {
        statusBar->showMessage(exc.what(), 1500);
    }
    update();
}

void MainWindow::parallelMerge()
{
    QList<QTreeWidgetItem*> sel = tree->selectedItems();
    if( sel.size() > 2 ) return;
    if( sel.empty() )
    {
        statusBar->showMessage("No graphs selected\n", 1500);
        return;
    }
    auto a = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[0])->graph;
    auto b = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[1])->graph;
    try{
        a->parallelComposition(*b);
    } catch ( SPInvalidComposition<Shaape*> e )
    {
        statusBar->showMessage(QString::fromStdString(e.what()), 1500);
    }
    update();
}

void MainWindow::consequtiveMerge()
{
    QList<QTreeWidgetItem*> sel = tree->selectedItems();
    if( sel.size() > 2 ) return;
    if( sel.empty() )
    {
        statusBar->showMessage("No graphs selected\n", 1500);
        return;
    }

    SPGraph<Shaape*>* a = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[0])->graph;
    SPGraph<Shaape*>* b = dynamic_cast<SPGraphQTreeItem<Shaape*>*>(sel[1])->graph;

    try{
        a->seriesComposition(*b);
    } catch (SPInvalidComposition<Shaape*> e)
    {
        statusBar->showMessage(QString::fromStdString(e.what()), 1500);
    }
    update();
}

void MainWindow::imp()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile qf(fileName);

    if( !qf.open(QIODevice::ReadOnly) )
    {
        statusBar->showMessage("Cannot open file", 1500);
        return;
    }

    QTextStream in(&qf);

    std::vector< Node<Shaape*>* > data;
    std::vector< std::pair< std::vector<size_t>, std::vector<size_t> > > connections;
    while( !in.atEnd() ) //parse file
    {
        QString line = in.readLine();
        for( size_t i = 0; i < line.toULong(); ++i ) //parse graph
        {
            data.emplace_back(parseToNode(in, connections));
        }
        makeConnections(data, connections);
        SPGraph<Shaape*>* gr = new SPGraph<Shaape*>(data.front(), data.back(), data.size());
        gr->comp = compare;
        graphs.emplace_back( gr );
        data.clear();
        connections.clear();
    }
    update();
}

void MainWindow::exp()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile qf(fileName);

    if( !qf.open(QIODevice::WriteOnly) )
    {
        statusBar->showMessage("Cannot save file", 1500);
        return;
    }

    QTextStream out(&qf);

    for( auto& a : graphs )
    {
        out << a->size() << '\n';
        std::vector<Node<Shaape*>*> data;
        a->depthFirstDecompose(a->begin().node, data);
        for( size_t i = 0; i < data.size(); ++i )
        {
            // Shape info
            exportShape(out, *data[i]->data);

            //Parents
            for(auto& n : data[i]->parents)
                out << QString::number( std::distance(data.begin(), std::find( data.begin(), data.end(), n )) ) << " ";
            out << "\n";

            //Childs
            for(auto& n : data[i]->childs)
                out << QString::number( std::distance(data.begin(), std::find( data.begin(), data.end(), n )) ) << " ";
            out << "\n";

        }
    }
}
