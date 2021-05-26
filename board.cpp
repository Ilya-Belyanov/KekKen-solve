#include "board.h"

Board::Board(QObject *parent, QGraphicsView *graph) :
    QObject(parent),
    graphics(new QGraphicsView),
    scene(new QGraphicsScene)
{
    if(graph)
        setGraphicsView(graph);
}

void Board::setGraphicsView(QGraphicsView *graph)
{
    graphics = graph;
    graphics->showFullScreen();
    scene->setBackgroundBrush(Qt::black);
    graphics->setScene(scene);
    scene->addItem(composeI);
    graphics->show();
}
