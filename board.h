#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>

#include "griditem.h"

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GridItem *grid WRITE setGrid)

public:
    explicit Board(QObject *parent = nullptr, QGraphicsView *graph = nullptr );
    ~Board();
    void setGraphicsView(QGraphicsView *graph);
    void setGrid(GridItem *g);

private:
    QGraphicsView *graphics;
    QGraphicsScene *scene;
    GridItem *_grid;

signals:

};

#endif // BOARD_H
