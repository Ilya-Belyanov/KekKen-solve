#include "board.h"

Board::Board(QObject *parent, QGraphicsView *graph) :
    QObject(parent),
    graphics(new QGraphicsView),
    scene(new QGraphicsScene)
{
    _grid = new GridItem();
    scene->setBackgroundBrush(QColor("#1d1f21"));
    scene->addItem(_grid);
    _grid->setPos(0, 0);
    if(graph)
        setGraphicsView(graph);
}

Board::~Board()
{
    delete graphics;
    delete scene;
}

void Board::setGraphicsView(QGraphicsView *graph)
{
    delete graphics;
    graphics = graph;
    graphics->showFullScreen();
    graphics->setScene(scene);
    graphics->show();
}

void Board::setGrid(GridItem *g)
{
    delete _grid;
    _grid = g;
    scene->addItem(_grid);
    _grid->setPos(0, 0);
}
